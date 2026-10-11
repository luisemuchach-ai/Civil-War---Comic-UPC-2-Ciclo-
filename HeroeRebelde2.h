#pragma once
#include "Enemigo.h"

// HIJA de Enemigo: HeroeRebelde2 es Daredevil.
// Hereda vidas y movimientoAleatorio del padre.
// Solo cambia el dibujo (POLIMORFISMO), igual que SpiderMan:
// sprites en NUMEROS de 9 de ancho x 8 pixeles de alto (4 en consola).
//
// Tiene 3 frames que van EN ESTE ORDEN:
//   fase 0 = con 2 armas (cuando NO dispara)
//   fase 1 = con 1 arma  (cuando dispara 1 vez)
//   fase 2 = sin armas   (cuando dispara 2 veces)
// Luego se repite: vuelve a la fase 0.
class HeroeRebelde2 : public Enemigo
{
private:
    static const int Ancho_Frame = 9;  //const   → el valor no cambia y static → es compartido por todos los objetos de la clase.
    static const int Alto_Pixeles = 8;
    static const int Alto_Console = 4;

    // Fase actual de las armas: 0, 1 o 2.
    // No usa el frame del padre, porque ese solo cambia entre 0 y 1.
    int faseArmas;

    // 12 = rojo, 4 = rojo oscuro, 14 = dorado, 7 = gris, 0 = negro, -1 = vacio.
    short frameDosArmas[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, 12,  4, 12, -1, -1, -1},
        {-1, -1,  4,  4,  4,  4,  4, -1, -1},
        {-1, -1,  4, 12, 14, 12,  4, -1, -1},
        {-1, -1, -1, 14, 14, 14, -1, -1, -1},
        {-1, -1,  4,  4, 12,  4,  4, -1,  0},
        {-1,  7, 12,  4,  4,  4, 12,  7, -1},
        { 0, -1,  0,  4,  4,  4,  0, -1, -1},
        {-1, -1, -1, 12, -1, 12, -1, -1, -1}
    };

    short frameUnaArma[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, 12,  4, 12, -1, -1, -1},
        {-1, -1,  4,  4,  4,  4,  4, -1, -1},
        {-1, -1,  4, 12, 14, 12,  4, -1, -1},
        {-1, -1, -1, 14, 14, 14, -1, -1, -1},
        {-1, -1,  4,  4, 12,  4,  4, -1,  0},
        {-1, -1, 12,  4,  4,  4, 12,  7, -1},
        {-1, -1, -1,  4,  4,  4,  0, -1, -1},
        {-1, -1, -1, 12, -1, 12, -1, -1, -1}
    };

    short frameSinArmas[Alto_Pixeles][Ancho_Frame] =
    {
        {-1, -1, -1, 12,  4, 12, -1, -1, -1},
        {-1, -1,  4,  4,  4,  4,  4, -1, -1},
        {-1, -1,  4, 12, 14, 12,  4, -1, -1},
        {-1, -1, -1, 14, 14, 14, -1, -1, -1},
        {-1, -1,  4,  4, 12,  4,  4, -1, -1},
        {-1, -1, 12,  4,  4,  4, 12, -1, -1},
        {-1, -1, -1,  4,  4,  4, -1, -1, -1},
        {-1, -1, -1, 12, -1, 12, -1, -1, -1}
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
    HeroeRebelde2(Escenario* escenario)
        : Enemigo(escenario, 90, 23, Alto_Console, Ancho_Frame) {
        // Empieza escondido, aparece tras el dialogo.
        vivo = false;
        // Empieza con las 2 armas (sin disparar).
        faseArmas = 0;
    }

    ~HeroeRebelde2() {}

    void dibujar() override {
        if (vivo == false) {
            return;
        }

        if (faseArmas == 0) {
            dibujarSprite(frameDosArmas);
        }
        else if (faseArmas == 1) {
            dibujarSprite(frameUnaArma);
        }
        else {
            dibujarSprite(frameSinArmas);
        }
    }

    // POLIMORFISMO: Nivel1 llama a dueno->alDisparar() cada vez
    // que este enemigo dispara. Aqui avanzamos 0 -> 1 -> 2 -> 0.
    void alDisparar() override {
        if (vivo == false) {
            return;
        }

        borrar();
        faseArmas = faseArmas + 1;
        if (faseArmas > 2) {
            faseArmas = 0;
        }
        dibujar();
    }

    // Vuelve a tener las 2 armas (se usa al empezar el nivel).
    void reiniciarArmas() override {
        faseArmas = 0;
    }
};
