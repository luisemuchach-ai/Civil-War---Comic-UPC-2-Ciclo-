#pragma once
#include "Enemigo.h"

class DronStark : public Enemigo
{
private:

    static const int Ancho_Frame = 9;
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    int direccion;
    int limiteIzquierdo;
    int limiteDerecho;

    short frame0[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1,  0, -1,  0, -1, -1, -1},
        {-1, -1, -1, -1,  0, -1, -1, -1, -1},
        {-1, -1,  0,  0,  0,  0,  0, -1, -1},
        {-1,  0, 12, 12,  0, 12, 12,  0, -1},
        { 0, 12, 12,  0,  9,  0, 12, 12,  0},
        { 0, 12, 12,  0,  9,  0, 12, 12,  0},
        {-1,  0, 12, 12,  0, 12, 12,  0, -1},
        {-1, -1,  0,  0,  0,  0,  0, -1, -1}
    };

    short frame1[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, -1,  0, -1, -1, -1, -1},
        {-1, -1, -1,  0, -1,  0, -1, -1, -1},
        {-1, -1,  0,  0,  0,  0,  0, -1, -1},
        {-1,  0, 12, 12,  0, 12, 12,  0, -1},
        { 0, 12, 12,  0,  9,  0, 12, 12,  0},
        { 0, 12, 12,  0,  9,  0, 12, 12,  0},
        {-1,  0, 12, 12,  0, 12, 12,  0, -1},
        {-1, -1,  0,  0,  0,  0,  0, -1, -1}
    };

    void dibujarSprite(
        short sprite[Alto_Pixeles][Ancho_Frame])
    {
        for (int filaConsola = 0; filaConsola < Alto_Console;filaConsola++)
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
    DronStark(
        Escenario* escenario,
        int posX,
        int posY)

        : Enemigo(
            escenario,
            posX,
            posY,
            Alto_Console,
            Ancho_Frame)
    {
        vivo = true;

        direccion = 1;

        limiteIzquierdo = 47;
        limiteDerecho = 67;

        frame = 0;
    }


    ~DronStark(){}
   
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

    void moverHorizontal()
    {
        if (vivo == false)
            return;

        borrar();

        x = x + direccion;

        if (x <= limiteIzquierdo)
        {
            x = limiteIzquierdo; direccion = 1;
        }

        if (x >= limiteDerecho)
        {
            x = limiteDerecho; direccion = -1;
        }

        // cambia el frame para animar el dron
        if (frame == 0)
            frame = 1;
        else
            frame = 0;

        dibujar();
    }
    
};