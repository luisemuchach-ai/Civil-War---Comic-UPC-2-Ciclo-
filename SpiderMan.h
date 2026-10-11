#pragma once
#include "Personaje.h"

// ============================================================
// HIJA de Personaje: SpiderMan es-un Personaje (HERENCIA)
// Usa esc->ponerCeldaPixel igual que IronMan (COMPOSICION).
// Sus 2 frames estan en NUMEROS (no en letras).
// Cada frame mide 9 de ancho x 8 pixeles de alto (4 en consola).
// Trepa: su moverConTecla atraviesa paredes, solo lo frenan
// sus topes (techo de la casa y maximo gris del Nivel 2).
// ============================================================
class SpiderMan : public Personaje
{
private:

    static const int Ancho_Frame = 9;
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    short frame0[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1,  0,  0,  0, -1, -1, -1},
        {-1, -1,  0, 15, 12, 15,  0, -1, -1},
        {-1, -1,  0, 15, 12, 15,  0, -1, -1},
        { 0, 12, 12,  0, 12,  0, 12, 12,  0},
        {-1,  0, 12, 12,  0, 12, 12,  0, -1},
        {-1, -1,  0, 0, 12, 0,  0, -1, -1},
        {-1, -1,  0,  9,  0,  9,  0, -1, -1},
        {-1,  0,  9,  0, -1,  0,  9,  0, -1}
    };

    short frame1[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1,  0,  0,  0, -1, -1, -1},
        {-1, -1,  0, 15, 12, 15,  0, -1, -1},
        {-1, -1,  0, 15, 12, 15,  0, -1, -1},
        {-1,  0, 12,  0, 12,  0, 12,  0, -1},
        { 0, 12, -1, 12,  0, 12, -1, 12,  0},
        {-1,  0, -1,  0, 12,  0, -1,  0, -1},
        {-1, -1,  9,  0, -1,  0,  9, -1, -1},
        {-1,  0,  0, -1, -1, -1,  0,  0, -1}
    };

    void dibujarSprite(short sprite[Alto_Pixeles][Ancho_Frame])
    {
        for (int filaConsola = 0;filaConsola < Alto_Console; filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0;columna < Ancho_Frame; columna++)
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

    SpiderMan(
        Escenario* escenario,
        int posX,
        int posY)

        : Personaje(
            escenario,
            posX,
            posY,
            Alto_Console,
            Ancho_Frame)
    {
        frame = 0;
        vivo = true;
    }

    ~SpiderMan()
    {
    }

    void dibujar() override
    {
        if (vivo == false)
            return;

        if (frame == 0)
        {
            dibujarSprite(frame0);
        }
        else
        {
            dibujarSprite(frame1);
        }
    }

    // Mueve con A/D (lados) y W/S (subir/bajar). Devuelve true si se movio.
    // Igual que IronMan en el Nivel 1: por ejes, con topes y animacion.
    // Diferencia: SpiderMan trepa y SI PUEDE IR ENCIMA (atraviesa
    // paredes y gris sin chocar); solo lo frenan los topes:
    // arriba la fila 10 (techo de la casa) y abajo la fila 24
    // (ocupa hasta la 27: camina encima de los 8; a los 0 no entra).
    bool moverConTecla(char tecla)
    {
        if (vivo == false)
        {
            return false;
        }

        int destinoX = x;
        int destinoY = y;

        if (tecla == 'a' || tecla == 'A')
        {
            destinoX = x - 1;
        }
        if (tecla == 'd' || tecla == 'D')
        {
            destinoX = x + 1;
        }
        if (tecla == 'w' || tecla == 'W')
        {
            destinoY = y - 1;
        }
        if (tecla == 's' || tecla == 'S')
        {
            destinoY = y + 1;
        }

        bool seMovio = false;

        // Eje X: no salir de pantalla (las paredes las atraviesa).
        if (destinoX != x)
        {
            bool dentro = (destinoX >= 0) && (destinoX <= ANCHO - ancho);
            if (dentro)
            {
                borrar();
                x = destinoX;
                seMovio = true;
            }
        }

        // Eje Y: entre el techo (10) y el piso gris (24).
        if (destinoY != y)
        {
            bool dentro = (destinoY >= 10) && (destinoY <= 24);
            if (dentro)
            {
                if (seMovio == false)
                {
                    borrar();
                }
                y = destinoY;
                seMovio = true;
            }
        }

        if (seMovio)
        {
            if (frame == 0)
            {
                frame = 1;
            }
            else
            {
                frame = 0;
            }
            dibujar();
        }
        return seMovio;
    }
};
