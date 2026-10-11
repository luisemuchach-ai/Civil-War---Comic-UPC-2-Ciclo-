#pragma once
#include "Personaje.h"
#include <cstdlib>

// ============================================================
// CLASE INTERMEDIA: Enemigo hereda de Personaje (HERENCIA)
// Guarda lo que los 2 enemigos tienen en comun:
// 3 vidas y el mismo movimiento aleatorio.
// HeroeRebelde1 y HeroeRebelde2 heredan de aqui.
// ============================================================
class Enemigo : public Personaje
{
public:
    Enemigo(Escenario* escenario, int posX, int posY, int altoP, int anchoP)
        : Personaje(escenario, posX, posY, altoP, anchoP) {
    }

    virtual ~Enemigo() {}

    // Se llama cada vez que este enemigo dispara.
    // Por defecto no hace nada. Daredevil lo usa para
    // cambiar su frame de armas (2 armas -> 1 arma -> 0 armas).
    virtual void alDisparar() {
    }

    virtual void reiniciarArmas() {
    }

    // Se mueve solo: arriba/abajo al azar y luego izquierda/derecha.
    // Solo avanza si no hay roca (usa mover del padre).
    void movimientoAleatorio() {
        if (vivo == false) {
            return;
        }

        // Paso 1: intenta subir o bajar (o quedarse).
        int dadoY = rand() % 3; // 0, 1 o 2
        if (dadoY == 0) {
            int subir = y - 1;
            if (subir < 21) {
                subir = 21; // no subir al HUD
            }
            // Mueve solo en Y (X queda igual).
            if (subir != y) {
                // Revisa si cabe y mueve a mano para no animar 2 veces.
                // (Usamos mover con dy para mantenerlo simple).
                mover(0, subir - y);
            }
        }
        else if (dadoY == 1) {
            int bajar = y + 1;
            int limiteAbajo = ALTO - alto;
            if (bajar > limiteAbajo) {
                bajar = limiteAbajo;
            }
            if (bajar != y) {
                mover(0, bajar - y);
            }
        }
        // Si dadoY == 2 no se mueve en Y.

        // Paso 2: intenta ir a los lados (o quedarse).
        int dadoX = rand() % 3; // 0, 1 o 2
        if (dadoX == 0) {
            mover(-1, 0);
        }
        else if (dadoX == 1) {
            mover(1, 0);
        }
        // Si dadoX == 2 se queda quieto.
    }
};
