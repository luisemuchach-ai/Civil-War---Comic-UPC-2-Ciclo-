#pragma once
#include "Enemigo.h"

// HIJA de Enemigo: HeroeRebelde1 es la Antorcha Humana.
// Hereda vidas y movimientoAleatorio del padre.
// Solo cambia el dibujo (POLIMORFISMO), igual que SpiderMan:
// un sprite en NUMEROS de 9 de ancho x 8 pixeles de alto (4 en consola).
class HeroeRebelde1 : public Enemigo
{
private:
    static const int Ancho_Frame = 9;  //const   → el valor no cambia y static → es compartido por todos los objetos de la clase.
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    // 6 = fuego, 12 = rojo, 15 = blanco, 4 = rojo oscuro, -1 = vacio.
    short spriteAntorcha[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1,  14, 12, 12, 12,  14, -1, -1},
        {-1, -1, 12, 12, 12, 12, 12, -1, -1},
        {-1,  14, 12, 15, 12, 15, 12,  14, -1},
        {-1,  14,  14, 12, 12, 12,  14,  14, -1},
        {-1,  14, 12, 12, 12, 12, 12,  14, -1},
        {-1,  14,  4, 12, 12, 12,  4,  14, -1},
        {-1,  14,  14, 12, 12, 12,  14, -1, -1},
        {-1, -1,  14,  4,  14,  4,  14, -1, -1}
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
    HeroeRebelde1(Escenario* escenario)
        : Enemigo(escenario, 100, 24, Alto_Console, Ancho_Frame) {
        // Empieza escondido, aparece tras el dialogo.
        vivo = false;
    }

    ~HeroeRebelde1() {}

    void dibujar() override {
        if (vivo == false) {
            return;
        }

        // Antorcha solo tiene 1 frame, no usa el frame del padre.
        dibujarSprite(spriteAntorcha);
    }
};
