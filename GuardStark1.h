#pragma once
#include "Enemigo.h"

class GuardStark : public Enemigo
{
private:
    static const int Ancho_Frame = 10;
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    int limiteIzquierdo;
    int limiteDerecho;
    int limiteSuperior;
    int limiteInferior;


    short frame0[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, -1, -1,  0,  0,  0,  0, -1},
        {-1, -1, -1, -1,  0, 12, 12, 12, 12,  0},
        {-1, -1, -1, -1,  0,  0,  8,  0, 12,  0},
        {-1, -1,  6, -1,  0,  8,  8,  8, 12,  0},
        {-1,  6,  6,  0, 12,  12, 12, 12,  0, -1},
        { 6, -1,  6,  0, 12, 14, 12,  0, 12,  0},
        {-1,  6,  6, -1,  0, 12,  0, 12,  0, -1},
        {-1, -1,  6, -1,  0,  0, -1,  0,  0, -1}
    };

    short frame1[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, -1, -1,  0,  0,  0,  0, -1},
        {-1, -1, -1, -1,  0, 12, 12, 12, 12,  0},
        {-1, -1, -1, -1,  0,  0,  8,  0,  12,  0},
        {-1, -1,  6, -1,  0,  8,  8,  8, 12,  0},
        {-1,  6,  6,  0, 12, 12, 12, 12,  0, -1},
        { 6, -1,  6,  0, 12, 14, 12,  0, 12,  0},
        {-1,  6,  6, -1, 12,  0, 12, -1,  0, -1},
        {-1, -1,  6,  0,  0, -1, -1,  0,  0, -1}
    };


    void dibujarSprite(short sprite[Alto_Pixeles][Ancho_Frame])
    {
        for (int filaConsola = 0;
            filaConsola < Alto_Console;
            filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0; columna < Ancho_Frame; columna++)
            {
                int colorArriba = sprite[filaArriba][columna];
                int colorAbajo  = sprite[filaAbajo][columna];

                if (colorArriba == -1 && colorAbajo == -1)
                {
                    continue;
                }

                esc->ponerCeldaPixel(
                    x + columna,
                    y + filaConsola,
                    colorArriba,
                    colorAbajo
                );
            }
        }
    }

public:

    GuardStark(Escenario* escenario)
        : Enemigo(
            escenario,
            96,
            22,
            Alto_Console,
            Ancho_Frame)
    {
        vivo = true;
        limiteIzquierdo = 93;
        limiteDerecho = 100;

        limiteSuperior = 18;
        limiteInferior = 22;

        frame = 0;
    }


    ~GuardStark(){}

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

    void moverZona()
    {
        if (vivo == false)
            return;

        borrar();

        int movimiento = rand() % 4;

        if (movimiento == 0)
            x--;

        if (movimiento == 1)
            x++;

        if (movimiento == 2)
            y--;

        if (movimiento == 3)
            y++;

        if (x < limiteIzquierdo)
            x = limiteIzquierdo;

        if (x > limiteDerecho)
            x = limiteDerecho;

        if (y < limiteSuperior)
            y = limiteSuperior;

        if (y > limiteInferior)
            y = limiteInferior;


        if (frame == 0)
            frame = 1;
        else
            frame = 0;

        dibujar();
    }
};
