#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace System;
using namespace std;

// Medidas de la pantalla
const int ANCHO = 120;
const int ALTO = 30;

// ============================================================
// CLASE PADRE ABSTRACTA
// No tiene ningun mapa de nivel adentro.
// Solo guarda el mapa ACTUAL y las herramientas comunes:
// dibujar letras, borrar zonas, pintar colores, HUD y dialogos.
// El mapa del Nivel 1 esta en la hija Nivel1.h
// ============================================================
class Escenario
{
protected:
    int filas;                    // 30
    int columnas;                 // 120
    short mapaActual[30][120];    // lo que se ve en pantalla ahora

public:
    // Constructor: empieza con todo negro (0) y sin nivel cargado.
    Escenario() {
        filas = 30;
        columnas = 120;
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                mapaActual[i][j] = 0;
            }
        }
    }

    virtual ~Escenario() {}

    // Metodo ABSTRACTO (= 0): el padre dice QUE se hace,
    // cada hija dice COMO. Nivel1 carga SU mapa (sin numero,
    // porque un nivel solo sabe cargarse a si mismo).
    virtual void CargarEscenario() = 0;

    // Metodo ABSTRACTO: cada nivel decide que es pared (sus rocas).
    virtual bool EsSolido(int x, int y) = 0;

    // Arma el texto "[O][O][ ]" segun vidas llenas y maximas.
    // Se usa en el cuadro del jugador y en el de los enemigos.
    string textoBarraVidas(int vidas, int vidasMax) {
        string barra = "";
        for (int i = 0; i < vidasMax; i++) {
            if (i < vidas) {
                barra = barra + "[O]";
            }
            else {
                barra = barra + "[ ]";
            }
        }
        return barra;
    }

    // ¿Esta palabra es una tecla del HUD?
    bool esTeclaHUD(string palabra) {
        if (palabra == "A/D:") return true;
        if (palabra == "W/S:") return true;
        if (palabra == "ESPACIO:") return true;
        if (palabra == "ESC:") return true;
        return false;
    }

    // Escribe una linea del HUD con las teclas en gris oscuro y
    // lo demas en blanco. Respeta los espacios, asi no deforma el cuadro.
    void escribirLineaHUD(string linea) {
        string palabra = "";
        for (int i = 0; i <= (int)linea.length(); i++) {
            bool fin = (i == (int)linea.length());
            char letra = ' ';
            if (fin == false) {
                letra = linea[i];
            }
            if (letra == ' ') {
                if (palabra != "") {
                    if (esTeclaHUD(palabra)) {
                        Console::ForegroundColor = ConsoleColor::DarkGray;
                    }
                    else {
                        Console::ForegroundColor = ConsoleColor::White;
                    }
                    cout << palabra;
                    palabra = "";
                }
                if (fin == false) {
                    Console::ForegroundColor = ConsoleColor::White;
                    cout << " ";
                }
            }
            else {
                palabra = palabra + letra;
            }
        }
    }

    // Cuadro de arriba a la izquierda, en DOS partes separadas
    // por UNA sola linea de "=". Arriba las indicaciones del nivel
    // (filas 1 a 5) y abajo la vida del personaje controlado
    // (filas 5 a 8). Empieza en la fila 1 y termina en la 8 para
    // que la telaraña (que llega a la 9) nunca lo borre.
    // Version configurable (la usan los 3 niveles).
    void mostrarHUD(int vidas, string linea1, string linea2, string linea3, string nombre)
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;

        int anchoHUD = 55;
        int inicioX = 2;

        // Cuadro 1: indicaciones.
        Console::SetCursorPosition(inicioX, 1);
        for (int c = 0; c < anchoHUD; c++) {
            cout << "=";
        }

        string lineas[3] = { linea1, linea2, linea3 };
        for (int f = 0; f < 3; f++) {
            Console::SetCursorPosition(inicioX, 2 + f);
            cout << "|";
            escribirLineaHUD(lineas[f]);
            Console::ForegroundColor = ConsoleColor::White;
            int falta = anchoHUD - 2 - (int)lineas[f].length();
            for (int c = 0; c < falta; c++) {
                cout << " ";
            }
            cout << "|";
        }

        // Una sola linea separa las indicaciones de las vidas.
        Console::SetCursorPosition(inicioX, 5);
        for (int c = 0; c < anchoHUD; c++) {
            cout << "=";
        }

        // Cuadro 2: a quien es y debajo sus vidas.
        string linea4 = " Vida del personaje controlado:";
        string linea5 = " " + nombre + ": " + textoBarraVidas(vidas, 3);

        string lineasVida[2] = { linea4, linea5 };
        for (int f = 0; f < 2; f++) {
            Console::SetCursorPosition(inicioX, 6 + f);
            cout << "|";
            cout << lineasVida[f];
            int falta = anchoHUD - 2 - (int)lineasVida[f].length();
            for (int c = 0; c < falta; c++) {
                cout << " ";
            }
            cout << "|";
        }

        Console::SetCursorPosition(inicioX, 8);
        for (int c = 0; c < anchoHUD; c++) {
            cout << "=";
        }
    }

    // CUADRO DE ENEMIGOS ARRIBA A LA DERECHA (espejo del HUD de la
    // izquierda). Mismo ancho (55) y mismos bordes (= y |).
    // La izquierda es x=2 y la derecha es x=63 (120 - 55 - 2).
    // Se repinta fijo cada vez que cambian las vidas (no se mueve).

    // Una linea del cuadro derecho ("| texto |").
    void dibujarLineaEnemiga(string linea, int fila) {
        int inicioX = 63;
        Console::SetCursorPosition(inicioX, fila);
        cout << "|";
        cout << linea;
        int falta = 55 - 2 - (int)linea.length();
        for (int c = 0; c < falta; c++) {
            cout << " ";
        }
        cout << "|";
    }

    // Borde superior/inferior del cuadro derecho ("=" x 55).
    void dibujarBordeDerecho(int fila) {
        Console::SetCursorPosition(63, fila);
        for (int c = 0; c < 55; c++) {
            cout << "=";
        }
    }

    // Cuadro derecho con UN enemigo (Nivel 3).
    // Arriba dice a quienes son y debajo sus vidas.
    void mostrarHUDEnemigo(string titulo, string nombre, int vidas, int vidasMax) {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        dibujarBordeDerecho(1);
        dibujarLineaEnemiga(" " + titulo, 2);
        dibujarLineaEnemiga(" " + nombre + ": " +
            textoBarraVidas(vidas, vidasMax), 3);
        dibujarBordeDerecho(4);
    }

    // Cuadro derecho con DOS enemigos (Nivel 1 y 2).
    // Arriba dice a quienes son y debajo sus vidas.
    void mostrarHUDEnemigos(string titulo, string nombre1, int vidas1,
        string nombre2, int vidas2, int vidasMax) {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        dibujarBordeDerecho(1);
        dibujarLineaEnemiga(" " + titulo, 2);
        dibujarLineaEnemiga(" " + nombre1 + ": " +
            textoBarraVidas(vidas1, vidasMax), 3);
        dibujarLineaEnemiga(" " + nombre2 + ": " +
            textoBarraVidas(vidas2, vidasMax), 4);
        dibujarBordeDerecho(5);
    }

    // Copia CUALQUIER mapa (por ejemplo el GameOver que vive en Juego)
    // al mapa actual. Asi el padre no necesita conocer niveles.
    void CargarMapa(short nuevoMapa[30][120])
    {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                mapaActual[i][j] = nuevoMapa[i][j];
            }
        }
    }

    // Pinta UNA letra en (x, y) con un color de personaje,
    // conservando el color de fondo del mapa.
    void ponerCaracter(int x, int y, char caracter, int valor)
    {
        if (x < 0 || x >= columnas) {
            return;
        }
        if (y < 0 || y >= filas) {
            return;
        }
        ColorEscenario(mapaActual[y][x]);
        ColorPersonaje(valor);
        Console::SetCursorPosition(x, y);
        cout << caracter;
    }

    void ponerCeldaPixel(int x, int y, int colorArriba, int colorAbajo)
    {
        if (x < 0 || x >= columnas) return;
        if (y < 0 || y >= filas) return;
        if (colorArriba < 0 && colorAbajo < 0) return;

        if (colorArriba < 0) colorArriba = mapaActual[y][x];
        if (colorAbajo < 0) colorAbajo = mapaActual[y][x];

        Console::ForegroundColor = (ConsoleColor)((colorArriba >= 0 && colorArriba <= 15) ? colorArriba : 15);
        ColorEscenario(colorAbajo);
        Console::SetCursorPosition(x, y);
        cout << (char)223;   // bloque de medio pixel (2 colores por casilla)
    }

    // Borra un rectangulo y deja ver el mapa que habia debajo.
    void restaurarZona(int x, int y, int ancho, int alto)
    {
        for (int fila = y; fila < y + alto; fila++) {
            if (fila < 0 || fila >= filas) {
                continue;
            }
            for (int col = x; col < x + ancho; col++) {
                if (col < 0 || col >= columnas) {
                    continue;
                }
                ColorEscenario(mapaActual[fila][col]);
                Console::SetCursorPosition(col, fila);
                cout << " ";
            }
        }
    }

    void ColorPersonaje(short valor)
    {
        if (valor == 0) { Console::ForegroundColor = ConsoleColor::Black; }
        else if (valor == 1) { Console::ForegroundColor = ConsoleColor::DarkBlue; }
        else if (valor == 3) { Console::ForegroundColor = ConsoleColor::DarkCyan; }
        else if (valor == 4) { Console::ForegroundColor = ConsoleColor::DarkRed; }
        else if (valor == 5) { Console::ForegroundColor = ConsoleColor::DarkMagenta; }
        else if (valor == 6) { Console::ForegroundColor = ConsoleColor::DarkYellow; }
        else if (valor == 7) { Console::ForegroundColor = ConsoleColor::Gray; }
        else if (valor == 8) { Console::ForegroundColor = ConsoleColor::DarkGray; }
        else if (valor == 12) { Console::ForegroundColor = ConsoleColor::Red; }
        else if (valor == 14) { Console::ForegroundColor = ConsoleColor::Yellow; }
        else if (valor == 15) { Console::ForegroundColor = ConsoleColor::White; }
        else { Console::ForegroundColor = ConsoleColor::White; }
    }

    void ColorEscenario(short valor)
    {
        if (valor == 0) { Console::BackgroundColor = ConsoleColor::Black; }
        else if (valor == 1) { Console::BackgroundColor = ConsoleColor::DarkBlue; }
        else if (valor == 2) { Console::BackgroundColor = ConsoleColor::DarkGreen; }
        else if (valor == 3) { Console::BackgroundColor = ConsoleColor::DarkCyan; }
        else if (valor == 4) { Console::BackgroundColor = ConsoleColor::DarkRed; }
        else if (valor == 5) { Console::BackgroundColor = ConsoleColor::DarkMagenta; }
        else if (valor == 6) { Console::BackgroundColor = ConsoleColor::DarkYellow; }
        else if (valor == 7) { Console::BackgroundColor = ConsoleColor::Gray; }
        else if (valor == 8) { Console::BackgroundColor = ConsoleColor::DarkGray; }
        else if (valor == 9) { Console::BackgroundColor = ConsoleColor::Blue; }
        else if (valor == 10) { Console::BackgroundColor = ConsoleColor::Green; }
        else if (valor == 11) { Console::BackgroundColor = ConsoleColor::Cyan; }
        else if (valor == 12) { Console::BackgroundColor = ConsoleColor::Red; }
        else if (valor == 13) { Console::BackgroundColor = ConsoleColor::Magenta; }
        else if (valor == 14) { Console::BackgroundColor = ConsoleColor::Yellow; }
        else if (valor == 15) { Console::BackgroundColor = ConsoleColor::White; }
        else { Console::BackgroundColor = ConsoleColor::White; }
    }

    void DibujarCelda(int fila, int columna)
    {
        Console::SetCursorPosition(columna, fila);
        ColorEscenario(mapaActual[fila][columna]);
        cout << " ";
    }

    void DibujarMapa()
    {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                DibujarCelda(i, j);
            }
        }
    }

    // ¿(x, y) esta fuera de la pantalla?
    bool HayColision(int x, int y) {
        if (x < 0 || x >= columnas) return true;
        if (y < 0 || y >= filas) return true;
        return false;
    }

    // ¿Hay pared en el rectangulo (x, y, ancho, alto)?
    bool HaySolidoEnZona(int x, int y, int ancho, int alto) {
        for (int fila = y; fila < y + alto; fila++) {
            for (int col = x; col < x + ancho; col++) {
                if (EsSolido(col, fila)) {
                    return true;
                }
            }
        }
        return false;
    }

    // ¿El personaje cabe en (x, y) sin chocar roca?
    bool PuedeEstarEn(int x, int y, int ancho, int alto) {
        if (HaySolidoEnZona(x, y, ancho, alto)) return false;
        return true;
    }

    // ¿La bala choco con pared?
    bool BalaChocaMuro(int xBala, int yBala) {
        return EsSolido(xBala, yBala);
    }

    // ¿La bala (xBala, yBala) toco al personaje (x, y, ancho, alto)?
    bool colisionDisparo(int x, int y, int xBala, int yBala, int alto, int ancho) {
        bool tocaX = (xBala + 1 >= x) && (xBala - 1 < x + ancho);
        bool tocaY = (yBala >= y) && (yBala < y + alto);
        if (tocaX && tocaY) return true;
        return false;
    }

    // Cuadro de dialogo al centro (34 + 51 + 35 = 120).
    // SOLO avanza con ENTER.
    // La ultima linea siempre avisa que hay que presionar ENTER.
    void dialogo(String^ personaje, String^ texto)
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;

        int anchoDialogo = 51;
        int inicioX = 34;
        int inicioY = 10;

        Console::SetCursorPosition(inicioX, inicioY);
        for (int c = 0; c < anchoDialogo; c++) cout << "=";

        for (int f = 0; f < 3; f++) {
            Console::SetCursorPosition(inicioX, inicioY + 1 + f);
            cout << "|";
            for (int c = 0; c < anchoDialogo - 2; c++) cout << " ";
            cout << "|";
        }

        Console::SetCursorPosition(inicioX + 1, inicioY + 1);
        Console::Write(personaje);
        Console::SetCursorPosition(inicioX + 1, inicioY + 2);
        Console::Write(texto);

        Console::ForegroundColor = ConsoleColor::Gray;
        Console::SetCursorPosition(inicioX + 1, inicioY + 3);
        Console::Write("Presiona ENTER para continuar");

        Console::ForegroundColor = ConsoleColor::White;
        Console::SetCursorPosition(inicioX, inicioY + 4);
        for (int c = 0; c < anchoDialogo; c++) cout << "=";

        while (true) {
            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 13) break;
            }
        }
    }
};
