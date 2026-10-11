#pragma once
#include "Personaje.h"

// ============================================================
// HIJA de Personaje: IronMan es-un Personaje (HERENCIA)
// Usa esc->ponerCeldaPixel igual que SpiderMan (COMPOSICION).
// Sus 2 frames estan en NUMEROS (no en letras).
// Cada frame mide 9 de ancho x 8 pixeles de alto (4 en consola).
// ============================================================
class IronMan : public Personaje
{
private:
    static const int Ancho_Frame = 9;  //const   → el valor no cambia y static → es compartido por todos los objetos de la clase.
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    // Vidas con las que empieza (y con las que revive).
    int vidasMaximas;

    // R = 12 (rojo), Y = 14 (dorado), W = 15 (blanco), C = 11 (cian), -1 = vacio.
    short frame0[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1, 12, 12, 14, 14, 14, 12, 12, -1},
        {-1, 12, 14, 15, 14, 15, 14, 12, -1},
        {12, 12, 12, 12, 12, 12, 12, 12, 12},
        {12, 12, 12, 14, 11, 14, 12, 12, 12},
        {14, 12, -1, 12, 14, 12, -1, 12, 14},
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1, -1, 12, 12, -1, 12, 12, -1, -1}
    };

    short frame1[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1, 12, 12, 14, 14, 14, 12, 12, -1},
        {-1, 12, 14, 15, 14, 15, 14, 12, -1},
        {12, 12, 12, 12, 12, 12, 12, 12, 12},
        {12, 12, 12, 14, 11, 14, 12, 12, 12},
        {14, 12, -1, 12, 14, 12, -1, 12, 14},
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1, 12, 12, -1, -1, -1, 12, 12, -1}
    };

    // Frame de DERROTADO: mismo tamaño 9 x 8, pero SIN CASCO
    // (igual que el Nivel 3 original). 0 = pelo negro,
    // 14 = cara, la armadura roja (12) queda intacta abajo.
    // Se usa solo al final del Nivel 3.
    short frameDerrotado[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1,  0,  0,  0,  0,  0, -1, -1},
        {-1,  0, 14, 14, 14, 14, 14,  0, -1},
        {-1, 14, 14,  0, 14,  0, 14, 14, -1},
        {12, 12, 12, 12, 12, 12, 12, 12, 12},
        {12, 12, 12, 14, 11, 14, 12, 12, 12},
        {14, 12, -1, 12, 14, 12, -1, 12, 14},
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1, 12, 12, -1, -1, -1, 12, 12, -1}
    };

    void dibujarSpriteEn(short sprite[Alto_Pixeles][Ancho_Frame], int posX, int posY)
    {
        for (int filaConsola = 0; filaConsola < Alto_Console; filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0; columna < Ancho_Frame; columna++)
            {
                int colorArriba = sprite[filaArriba][columna];
                int colorAbajo = sprite[filaAbajo][columna];

                if (colorArriba == -1 && colorAbajo == -1)
                {
                    continue;
                }

                esc->ponerCeldaPixel(posX + columna, posY + filaConsola, colorArriba, colorAbajo);
            }
        }
    }

    void dibujarSprite(short sprite[Alto_Pixeles][Ancho_Frame])
    {
        dibujarSpriteEn(sprite, x, y);
    }

public:
    // Empieza en (25, 23) y mide 4 de alto x 9 de ancho.
    // vidasIniciales = 3 en Nivel 1, = 6 como jefe final del Nivel 3.
    IronMan(Escenario* escenario, int vidasIniciales = 3)
        : Personaje(escenario, 25, 23, Alto_Console, Ancho_Frame) {
        vidas = vidasIniciales;
        vidasMaximas = vidasIniciales;
    }

    ~IronMan() {}

    // POLIMORFISMO: al revivir recupera SUS vidas maximas
    // (3 en Nivel 1, 6 como jefe del Nivel 3), no siempre 3.
    void revivir(int nuevoX, int nuevoY) override {
        x = nuevoX;
        y = nuevoY;
        vivo = true;
        vidas = vidasMaximas;
    }

    // POLIMORFISMO: mismo metodo dibujar(), otro dibujo.
    void dibujar() override {
        if (vivo == false) {
            return;
        }

        if (frame == 0) {
            dibujarSprite(frame0);
        }
        else {
            dibujarSprite(frame1);
        }
    }

    // Dibuja el frame de derrotado en (px, py) aunque vivo == false.
    // Nivel3 lo llama una vez al ganar para dejar el cuerpo en el suelo.
    void dibujarDerrotado(int px, int py) {
        dibujarSpriteEn(frameDerrotado, px, py);
    }

    // Mueve con A/D (lados) y W/S (volar). Devuelve true si se movio.
    // Se mueve por ejes: primero X y luego Y, para resbalar en rocas.
    bool moverConTecla(char tecla) {
        if (vivo == false) {
            return false;
        }

        int destinoX = x;
        int destinoY = y;

        if (tecla == 'a' || tecla == 'A') {
            destinoX = x - 1;
        }
        if (tecla == 'd' || tecla == 'D') {
            destinoX = x + 1;
        }
        if (tecla == 'w' || tecla == 'W') {
            destinoY = y - 1;
        }
        if (tecla == 's' || tecla == 'S') {
            destinoY = y + 1;
        }

        bool seMovio = false;

        // Eje X: no salir de pantalla y no chocar roca.
        if (destinoX != x) {
            bool dentro = (destinoX >= 0) && (destinoX <= ANCHO - ancho);
            if (dentro && esc->PuedeEstarEn(destinoX, y, ancho, alto)) {
                borrar();
                x = destinoX;
                seMovio = true;
            }
        }

        // Eje Y: solo vuela entre la fila 21 y el piso.
        if (destinoY != y) {
            bool dentro = (destinoY >= 21) && (destinoY <= ALTO - alto);
            if (dentro && esc->PuedeEstarEn(x, destinoY, ancho, alto)) {
                if (seMovio == false) {
                    borrar();
                }
                y = destinoY;
                seMovio = true;
            }
        }

        if (seMovio) {
            if (frame == 0) {
                frame = 1;
            }
            else {
                frame = 0;
            }
            dibujar();
        }
        return seMovio;
    }
};
