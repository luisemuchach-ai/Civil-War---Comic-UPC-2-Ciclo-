#pragma once
#include "Escenario.h"
#include "CapitanAmerica.h"
#include "IronMan.h"
#include "SpiderMan.h"

// ============================================================
// PARTE FINAL (BOCETO) : es automatica, no se juega.
// - Es la base para la animacion del Capitan entregandose:
//   por ahora muestra la carcel, al Capitan adentro y los
//   dialogos que explican que paso con el.
// - Juego la invoca solo al terminar el Nivel 3.
// jugar() devuelve 0 y Juego sigue con la pregunta y creditos.
// ============================================================
class ParteFinal : public Escenario
{
private:
    CapitanAmerica capi;   // detenido dentro de la celda
    IronMan ironman;       // afuera, lo vino a buscar
    SpiderMan spider;      // afuera, lo acompaña

public:
    // Los personajes usan THIS como escenario (el mismo mapa final).
    ParteFinal()
        : capi(this),
        ironman(this),
        spider(this, 38, 22) {
    }
    ~ParteFinal() {}

    // BOCETO de carcel: todo negro, con una celda de rejas (8).
    // El Capitan queda adentro (x 53 a 67) y los otros afuera.
    // Mas adelante aqui ira la animacion de la entrega.
    void CargarEscenario() override {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                mapaActual[i][j] = 0;
            }
        }
        // Rejas verticales de la celda.
        for (int f = 17; f <= 26; f++) {
            mapaActual[f][52] = 8;
            mapaActual[f][56] = 8;
            mapaActual[f][60] = 8;
            mapaActual[f][64] = 8;
            mapaActual[f][68] = 8;
        }
        // Techo y piso de la celda.
        for (int c = 52; c <= 68; c++) {
            mapaActual[17][c] = 8;
            mapaActual[26][c] = 8;
        }
        // Piso gris fuera de la celda.
        for (int c = 0; c < columnas; c++) {
            if (mapaActual[26][c] == 0) {
                mapaActual[26][c] = 8;
            }
        }
    }

    bool EsSolido(int x, int y) override {
        // Nadie se mueve en este nivel (es automatico).
        return HayColision(x, y);
    }

    // Muestra la escena final y los dialogos que explican
    // que paso con el Capitan despues de entregarse.
    int jugar() {
        Console::Clear();
        Console::CursorVisible = false;

        CargarEscenario();
        DibujarMapa();

        capi.setPos(57, 21);
        ironman.setPos(76, 22);
        spider.setPos(38, 22);

        capi.dibujar();
        ironman.dibujar();
        spider.dibujar();

        dialogo("IRONMAN:", "Se acabo, Cap. Tienes que venir conmigo.");
        dialogo("CAPITAN AMERICA:", "Lo se, Tony. No opondre resistencia.");
        dialogo("CAPITAN AMERICA:", "Si pelear destruye lo que protejo... me entrego.");
        dialogo("SPIDERMAN:", "Capitan... perdon por todo esto.");
        dialogo("CAPITAN AMERICA:", "Tranquilo, Peter. Tu elige tu camino.");

        Console::CursorVisible = true;
        Console::SetCursorPosition(0, ALTO - 1);
        return 0;
    }

    // Pregunta con quien se identifica (sale donde estaba el dialogo,
    // un poco mas arriba de la celda para no chocar con ella).
    // Todo centrado dentro del cuadro. Devuelve 1, 2 o 3.
    // W/S para mover, ENTER para elegir. Sin cursor de texto.
    // (Por ahora solo se muestra; servira para finales distintos).
    int preguntarIdentidad() {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::CursorVisible = false;

        // Borra el cuadro del dialogo anterior (filas 10 a 14).
        restaurarZona(34, 10, 51, 5);

        int anchoCuadro = 51;
        int inicioX = 34;
        int inicioY = 7;

        string titulo = "CON QUIEN TE SIENTES IDENTIFICADO?";
        string opciones[3] = { "1) IRON MAN", "2) CAPITAN AMERICA", "3) SPIDER-MAN" };

        int seleccion = 1;

        while (true) {
            Console::SetCursorPosition(inicioX, inicioY);
            for (int c = 0; c < anchoCuadro; c++) cout << "=";

            // Titulo centrado.
            int espaciosTitulo = (anchoCuadro - 2 - (int)titulo.length()) / 2;
            Console::SetCursorPosition(inicioX, inicioY + 1);
            cout << "|";
            for (int c = 0; c < espaciosTitulo; c++) cout << " ";
            cout << titulo;
            for (int c = 0; c < anchoCuadro - 2 - espaciosTitulo - (int)titulo.length(); c++) cout << " ";
            cout << "|";

            // Opciones centradas (">> " y "   " miden 3 para no moverse).
            for (int i = 0; i < 3; i++) {
                string marca = "   ";
                if (i + 1 == seleccion) {
                    marca = ">> ";
                }
                string renglon = marca + opciones[i];
                int espacios = (anchoCuadro - 2 - (int)renglon.length()) / 2;
                Console::SetCursorPosition(inicioX, inicioY + 2 + i);
                cout << "|";
                for (int c = 0; c < espacios; c++) cout << " ";
                if (i + 1 == seleccion) {
                    Console::ForegroundColor = ConsoleColor::Yellow;
                }
                cout << renglon;
                Console::ForegroundColor = ConsoleColor::White;
                for (int c = 0; c < anchoCuadro - 2 - espacios - (int)renglon.length(); c++) cout << " ";
                cout << "|";
            }

            Console::SetCursorPosition(inicioX, inicioY + 5);
            for (int c = 0; c < anchoCuadro; c++) cout << "=";

            string ayuda = "W: SUBIR   S: BAJAR   ENTER: ELEGIR";
            int xAyuda = inicioX + (anchoCuadro - (int)ayuda.length()) / 2;
            Console::SetCursorPosition(inicioX, inicioY + 6);
            for (int c = 0; c < anchoCuadro; c++) cout << " ";
            Console::SetCursorPosition(xAyuda, inicioY + 6);
            cout << ayuda;

            while (_kbhit() == false) {
                Sleep(20);
            }
            char tecla = _getch();

            if (tecla == 'w' || tecla == 'W') {
                seleccion = seleccion - 1;
                if (seleccion < 1) seleccion = 3;
            }
            else if (tecla == 's' || tecla == 'S') {
                seleccion = seleccion + 1;
                if (seleccion > 3) seleccion = 1;
            }
            else if (tecla == 13) {
                return seleccion;
            }
        }
    }

    // Pantalla final: creditos y cierre del juego.
    void mostrarCreditos() {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::Clear();
        Console::CursorVisible = false;

        // Titulo en arte ASCII. Las filas miden distinto, asi que
        // se busca la mas larga y TODAS salen desde la misma x:
        // asi el dibujo queda alineado y centrado en bloque.
        string arte[4] = {
            "  ____   ____   ____   ____    _   _____    ___    ____ ",
            " / ___| |  _ \\ | ___| |  _ \\  | | |_   _|  / _ \\  / ___|",
            "| |___  | |/ / | __|  | | | | | |   | |   | | | | \\___ \\",
            " \\____| |_|\\_\\ |____| |____/  |_|   |_|    \\___/  |____/ "
        };

        int anchoArte = 0;
        for (int i = 0; i < 4; i++) {
            int largo = (int)arte[i].length();
            if (largo > anchoArte) {
                anchoArte = largo;
            }
        }

        Console::ForegroundColor = ConsoleColor::Yellow;
        int xArte = (ANCHO - anchoArte) / 2;
        for (int i = 0; i < 4; i++) {
            Console::SetCursorPosition(xArte, 8 + i);
            cout << arte[i];
        }

        string nombres[3] = {
            "- Diego Aliaga (U202613674)",
            "- Andre Ponce (U20251P260)",
            "- Luis Mucha (U202611001)"
        };

        int anchoNombres = 0;
        for (int i = 0; i < 3; i++) {
            int largo = (int)nombres[i].length();
            if (largo > anchoNombres) {
                anchoNombres = largo;
            }
        }

        Console::ForegroundColor = ConsoleColor::White;
        int xNombres = (ANCHO - anchoNombres) / 2;
        for (int i = 0; i < 3; i++) {
            Console::SetCursorPosition(xNombres, 13 + i);
            cout << nombres[i];
        }

        Console::ForegroundColor = ConsoleColor::Gray;
        string salir = "Presiona ENTER para salir";
        Console::SetCursorPosition((ANCHO - (int)salir.length()) / 2, 18);
        cout << salir;

        while (true) {
            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 13) {
                    break;
                }
            }
        }
        Console::ResetColor();
        Console::CursorVisible = true;
        Console::SetCursorPosition(0, ALTO - 1);
    }
};
