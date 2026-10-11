#pragma once
#include "Personaje.h"

// ============================================================
// HIJA de Personaje: CapitanAmerica es-un Personaje (HERENCIA)
// Usa esc->ponerCeldaPixel igual que IronMan y SpiderMan
// (COMPOSICION: todos dibujan sobre el mismo Escenario).
// Sus 2 frames estan en NUMEROS (no en letras ASCII).
// Cada frame mide 9 de ancho x 8 pixeles de alto (4 en consola).
// 9 = azul, 15 = blanco, 12 = rojo, 14 = piel, -1 = vacio.
// ============================================================
class CapitanAmerica : public Personaje
{
private:
    static const int Ancho_Frame = 9;
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    // Frame 0: piernas juntas (reposo).
    short frame0[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1,  9,  9,  9,  9,  9, -1, -1},
        {-1,  9,  9,  15,  15,  15,  9,  9, -1},
        {-1,  9, 14, 0, 14, 0, 14,  9, -1},
        { 9,  9,  9,  9, 15,  9,  9,  9,  9},
        { 9,  9,  9, 12, 15, 12,  9,  9,  9},
        {14,  9, -1,  9, 12,  9, -1,  9, 14},
        {-1, -1,  9,  9,  9,  9,  9, -1, -1},
        {-1, -1, 12, 12, -1, 12, 12, -1, -1}
    };

    // Frame 1: piernas abiertas (paso). Solo cambia la ultima fila.
    short frame1[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1,  9,  9,  9,  9,  9, -1, -1},
        {-1,  9,  9,  15,  15,  15,  9,  9, -1},
        {-1,  9, 14, 0, 14, 0, 14,  9, -1},
        { 9,  9,  9,  9, 15,  9,  9,  9,  9},
        { 9,  9,  9, 12, 15, 12,  9,  9,  9},
        {14,  9, -1,  9, 12,  9, -1,  9, 14},
        {-1, -1,  9,  9,  9,  9,  9, -1, -1},
        {-1, 12, 12, -1, -1, -1, 12, 12, -1}
    };

    void dibujarSprite(short sprite[Alto_Pixeles][Ancho_Frame])
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

                esc->ponerCeldaPixel(x + columna, y + filaConsola, colorArriba, colorAbajo);
            }
        }
    }

public:
    // Empieza en (25, 23) y mide 4 de alto x 9 de ancho (igual que IronMan).
    CapitanAmerica(Escenario* escenario)
        : Personaje(escenario, 25, 23, Alto_Console, Ancho_Frame) {
    }

    ~CapitanAmerica() {}

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

    // Mueve con A/D (lados) y W/S (arriba/abajo). Devuelve true si se movio.
    // Igual que IronMan en el Nivel 1: por ejes, con topes de pista
    // (fila 21 hasta el piso) y animacion de frames.
    // Pasa por encima del gris: los edificios (7) son fondo
    // (EsSolido solo frena en el borde) y el tope de abajo
    // lo da el piso, igual que IronMan.
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

        // Eje X: no salir de pantalla y no chocar borde.
        if (destinoX != x) {
            bool dentro = (destinoX >= 0) && (destinoX <= ANCHO - ancho);
            if (dentro && esc->PuedeEstarEn(destinoX, y, ancho, alto)) {
                borrar();
                x = destinoX;
                seMovio = true;
            }
        }

        // Eje Y: solo se mueve entre la fila 21 y el piso (igual que IronMan).
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
