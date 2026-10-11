#pragma once
#include "Escenario.h"

class Telarana
{
private:

    Escenario* esc;

    int x,y;
    int dirX,dirY;
    bool activa;
    bool reboto;
    int velocidad = 2;

    static const int Ancho_Frame = 9;
    static const int Alto_Pixeles = 6;
    static const int Alto_Console = 3;

    short SpiderWeb[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, -1, -1, -1, 15, -1, -1},
        {-1, -1, -1, -1, -1, 15, -1, 15, -1},
        {15, -1, -1, -1, 15, -1, 15, -1, 15},
        {-1, 15, 15, 15, -1, 15, 15, 15, 15},
        {15, -1, -1, -1, 15, -1, 15, -1, 15},
        {-1, -1, -1, -1, -1, 15, -1, 15, -1}
    };

    void dibujarSpiderWeb()
    {
        int inicioY = y - 1;

        for (int filaConsola = 0;
            filaConsola < Alto_Console;
            filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0;
                columna < Ancho_Frame;
                columna++)
            {
                int columnaSprite;

                // Disparo hacia la derecha:
                if (dirX >= 0) { columnaSprite = columna; }
                
                // Disparo hacia la izquierda:
                else
                {
                    columnaSprite =
                        Ancho_Frame - 1 - columna;
                }

                int colorArriba = SpiderWeb[filaArriba][columnaSprite];
                int colorAbajo  = SpiderWeb[filaAbajo][columnaSprite];

                if (colorArriba == -1 && colorAbajo == -1)
                {
                    continue;
                }
                int dibujarX;

                // x representa el frente de la telaraña.
                if (dirX >= 0)
                {
                    dibujarX =x - (Ancho_Frame - 1) + columna;
                }
                else
                {
                    dibujarX = x + columna;
                }

                esc->ponerCeldaPixel(
                    dibujarX,
                    inicioY + filaConsola,
                    colorArriba,
                    colorAbajo
                );
            }
        }
    }


public:

    Telarana(Escenario* escenario)
    {
        esc = escenario;
        x = 0; y = 0;
        dirX = 0; dirY = 0;

        velocidad = 10;   

        activa = false;
        reboto = false;
    }


    ~Telarana() {}

    void marcarRebote() { reboto = true; }
    bool estaActiva()   { return activa; }
    int getX()          { return x; }
    int getY()          { return y; }
    int getDirX()       { return dirX; }
    int getDirY()       { return dirY; }
    bool yaReboto()     { return reboto; }
    int getVelocidad() { return velocidad; }
    
    void lanzar(
        int inicioX,
        int inicioY,
        int dx,
        int dy)
    {
        x = inicioX;
        y = inicioY;

        dirX = dx;
        dirY = dy;

        activa = true;
        reboto = false;

        dibujar();
    }

    void rebotarHorizontal()
    {
        dirX = -dirX;
        reboto = true;
    }


    void rebotarVertical()
    {
        dirY = -dirY;
        reboto = true;
    }

    void avanzar()
    {
        x += dirX;
        y += dirY;
    }

    void desactivar()
    {
        activa = false;
    }

    void desactivarConBorrado()
    {
        if (activa)
        {
            borrar();
        }
        activa = false;
    }

    void borrar()
    {
        int inicioX;

        if (dirX >= 0)
        {
            inicioX = x - (Ancho_Frame - 1);
        }
        else
        {
            inicioX = x;
        }

        int inicioY = y - 1;
        esc->restaurarZona(
            inicioX,
            inicioY,
            Ancho_Frame,
            Alto_Console
        );
    }

    void dibujar()
    {
        if (activa == false)
        {
            return;
        }
        dibujarSpiderWeb();
    }

    void setDirY(int nuevaDirY)
    {
        dirY = nuevaDirY;
    }
};
