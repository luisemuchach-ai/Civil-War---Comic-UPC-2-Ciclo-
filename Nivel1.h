#pragma once
#include "Escenario.h"
#include "Obstaculo.h"
#include "IronMan.h"
#include "SpiderMan.h"
#include "HeroeRebelde1.h"
#include "HeroeRebelde2.h"
#include "Disparo.h"

// ============================================================
// NIVEL 1 : hereda de Escenario y TIENE TODO lo de este nivel.
// - Su mapa y sus rocas (lo que antes estaba en Escenario).
// - Sus personajes, balas, dialogos y su forma de jugar.
// Juego SOLO lo invoca: nivel1.jugar(). No guarda nada del nivel.
// Cada nivel tiene su propio jugar() con continuar (true/false).
// ============================================================

// Rocas del Nivel 1 como objetos (solo gris dentro de ellas bloquea).
// Cada una guarda su propio x, y, alto y ancho como Personaje.

class Nivel1 : public Escenario
{
private:
    short mapaNivel1[30][120] = {
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,3,8,8,8,8,8,8,8,8,3,3,3,3,3,3,8,8,8,8,8,8,8,3,8,8},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,12,12,12,3,3,3,3,3,3,3,8,8,3,3,3,3,3,8,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,8,8,8,8,8,8,8,0,0,0,0,0,0,0},
     {8,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,0,7,7,7,7,7,7,7,7,7,0,14,14,12,12,12,3,3,3,3,8,8,8,8,8,3,3,8,8,8,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3},
     {8,8,8,8,3,3,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,0,7,7,7,7,7,7,0,0,0,0,14,14,14,12,12,3,3,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,12,3,3,3,3,3,3,0,7,7,7,7,7,7,7,7,7,7,7,0,3,3,3,3,3},
     {8,8,8,8,8,8,8,3,3,3,3,8,8,8,8,8,8,8,8,8,8,3,3,3,8,8,8,3,3,3,3,3,3,3,12,0,7,7,7,7,7,7,0,8,8,14,14,14,14,14,12,3,3,3,8,8,8,8,8,8,8,8,8,8,3,3,12,3,3,3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,12,12,3,3,3,3,3,3,0,7,7,7,7,7,7,7,7,7,7,7,0,3,3,3,3,3},
     {8,8,8,8,8,8,8,3,3,3,3,3,3,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,14,0,0,0,0,7,7,7,0,8,8,14,14,14,14,14,12,12,3,3,3,8,8,8,8,8,8,8,8,3,3,12,12,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,12,12,3,3,3,3,3,0,7,7,7,7,7,7,7,7,7,7,7,0,0,3,3,3,3},
     {8,8,8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,12,3,3,3,3,3,3,12,14,14,14,8,8,0,7,7,7,0,8,8,8,14,14,14,14,12,12,3,3,3,3,3,3,8,8,8,3,3,3,12,12,14,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,14,12,12,3,3,3,0,7,0,0,0,0,7,7,7,7,7,7,7,0,3,0,0,0},
     {8,8,8,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,12,12,12,12,3,3,3,3,3,12,14,0,0,0,0,7,7,7,0,8,8,8,8,14,14,14,12,12,3,3,3,3,3,3,3,3,3,3,3,3,12,14,14,14,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,12,14,14,14,14,12,0,0,0,0,7,0,14,14,0,7,7,0,0,0,7,7,0,3,0,14,14},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,14,14,14,14,12,12,3,3,3,3,3,12,0,7,7,7,7,7,7,0,0,0,0,0,0,14,14,12,3,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,14,14,12,3,3,3,3,3,3,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,0,13,13,13,13,13,13,0,7,0,14,14,0,7,7,0,8,0,7,7,0,3,0,14,14},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,14,14,12,12,3,3,3,3,3,3,0,7,7,7,7,7,7,7,7,7,7,7,0,14,12,12,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,14,14,14,14,12,3,3,3,3,12,12,12,12,3,3,3,3,3,3,3,3,3,3,3,3,12,12,14,0,0,13,13,13,13,13,13,0,7,0,0,0,0,7,7,0,0,0,7,7,0,3,0,0,0},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,14,14,14,12,12,3,3,3,3,3,0,7,0,0,0,0,7,7,7,7,7,7,0,12,12,3,3,3,3,3,3,3,3,3,3,3,3,12,14,14,14,14,0,0,0,0,0,0,3,12,12,14,14,12,3,12,12,3,3,3,3,3,3,3,3,3,3,12,14,0,13,13,0,0,0,0,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,3,3,3},
     {0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,6,6,6,6,6,6,6,6,0,14,14,14,12,12,12,12,3,3,3,0,7,0,14,14,0,7,7,7,7,7,7,0,0,12,3,3,3,3,3,3,3,3,3,3,3,12,12,14,14,14,0,0,9,9,9,9,0,12,12,14,14,14,12,12,12,12,12,3,3,3,3,3,3,3,3,12,12,14,0,13,13,0,14,14,0,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,3,3,3},
     {8,8,8,8,8,8,8,8,0,3,3,3,3,3,3,0,6,0,0,0,0,6,0,0,0,14,14,14,14,12,12,3,3,3,3,0,7,0,0,0,0,7,0,0,0,7,7,7,0,3,3,3,3,3,3,3,3,3,3,3,3,12,14,14,14,14,0,9,9,9,9,9,0,12,14,14,14,14,14,14,14,12,12,12,3,3,3,3,3,3,12,12,14,14,0,13,13,0,14,14,0,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,0,0,0},
     {0,8,8,0,0,0,8,8,0,3,3,3,3,3,3,0,6,0,8,8,0,6,0,14,0,0,14,14,14,14,12,12,3,3,3,0,7,7,7,7,7,7,0,14,0,7,7,7,0,3,3,3,3,3,3,3,3,3,3,3,12,12,12,14,14,14,0,9,0,0,0,9,0,0,0,14,14,14,14,14,14,14,12,12,3,3,12,3,3,3,12,12,14,0,0,13,13,0,0,0,0,13,0,7,0,0,0,0,0,0,7,0,0,0,7,0,3,0,8,8},
     {0,8,8,0,14,0,8,8,0,3,3,3,3,3,3,0,6,0,8,8,0,6,0,14,14,0,14,14,14,14,14,12,12,3,3,0,7,7,7,7,7,7,0,0,0,7,7,7,0,3,3,3,3,3,3,3,3,3,3,3,3,12,14,14,14,0,0,9,0,14,0,9,0,11,0,0,14,14,14,0,0,0,0,0,0,12,14,12,3,3,12,12,14,0,13,13,13,13,13,13,13,13,0,7,0,14,14,14,14,0,7,0,8,0,7,0,3,0,0,0},
     {0,8,8,0,0,0,8,8,0,0,0,0,0,0,0,0,6,0,0,0,0,6,0,0,0,0,0,0,14,14,14,12,12,3,3,0,7,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0,3,3,3,3,3,3,12,12,14,14,0,9,9,0,0,0,9,0,11,11,0,14,14,14,0,11,11,11,11,11,0,14,12,12,3,3,12,14,14,13,13,13,13,13,13,13,13,0,7,0,0,0,0,0,0,7,0,0,0,7,0,3,3,3,3},
     {8,8,8,8,8,8,8,8,0,2,2,2,2,2,2,0,6,6,6,6,6,6,6,6,6,6,6,0,0,14,14,12,12,3,3,0,7,0,8,8,0,7,7,7,7,7,7,7,0,10,10,10,10,10,0,3,3,3,3,3,3,3,12,12,14,0,9,9,9,9,9,9,0,11,11,0,0,0,0,0,11,11,11,11,11,0,0,14,12,3,3,12,12,14,13,0,0,0,13,13,13,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,3,3,3},
     {0,8,8,0,0,0,8,8,0,2,0,0,0,2,2,0,6,0,0,0,0,6,0,0,0,0,6,6,0,14,14,12,12,3,3,0,7,0,0,0,0,7,7,7,7,7,7,7,0,10,0,0,0,10,0,0,3,3,3,3,3,3,3,12,14,0,9,9,9,9,9,9,0,11,11,11,11,11,11,11,11,11,11,11,11,11,0,14,14,12,3,3,12,12,13,0,8,0,13,13,13,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,0,0,0},
     {0,8,8,0,8,0,8,8,0,2,0,8,0,2,2,0,6,0,8,8,0,6,0,8,8,0,6,6,0,14,14,12,3,3,3,0,7,7,7,7,7,7,0,0,0,0,0,0,0,10,0,8,0,10,10,0,3,3,3,3,3,3,3,12,12,0,9,0,0,0,9,9,0,11,11,0,0,0,0,0,11,0,0,0,0,11,0,0,12,3,3,3,3,12,13,0,8,0,13,13,13,13,0,7,7,7,7,7,7,7,7,7,7,7,7,0,3,0,8,8},
     {0,8,8,0,0,0,8,8,0,2,0,0,0,2,2,0,6,0,8,8,0,6,0,8,8,0,6,6,0,12,12,12,3,3,3,0,7,7,7,7,7,0,0,8,8,8,8,8,0,10,0,0,0,10,10,0,3,3,3,3,3,3,3,3,12,0,9,0,8,0,9,9,0,11,11,0,8,8,8,0,11,0,8,8,0,11,11,0,3,3,3,3,3,0,13,0,0,0,13,13,13,13,0,7,7,7,0,0,0,0,0,0,7,7,7,0,3,0,0,0},
     {8,8,8,8,8,8,8,8,0,2,2,2,2,2,2,0,6,0,0,0,0,6,0,0,0,0,6,6,0,12,3,3,3,3,3,0,7,0,0,0,0,0,8,8,8,8,8,8,0,10,10,10,10,10,10,0,3,3,3,3,3,3,3,3,3,0,9,0,0,0,9,9,0,11,11,0,0,0,0,0,11,0,0,0,0,11,11,0,3,3,3,3,3,0,13,13,13,13,13,13,13,13,0,7,7,0,0,6,6,6,6,0,0,0,7,0,3,3,3,3},
     {8,8,8,8,8,8,8,8,0,2,2,2,2,2,2,0,6,6,6,6,6,6,6,6,6,6,6,6,0,3,3,3,3,3,3,0,7,0,8,8,8,8,8,8,8,8,8,8,0,10,10,10,10,10,10,0,3,3,3,3,3,3,3,3,3,0,9,9,9,9,9,9,0,11,11,11,11,11,11,11,11,11,11,11,11,11,11,0,3,3,3,3,3,0,13,13,13,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,3,3,0,0},
     {0,0,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,0,0,6,6,6,6,6,0,0,0,0,6},
     {6,0,0,0,0,0,0,6,6,6,0,6,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,6,6,6,6,6,6,6,6,6,6,6,0,6,0,0,6,6,6,6,6,6,6},
     {6,6,6,6,6,0,6,6,6,6,6,0,6,6,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,6,6,6,6,0,0,0,0,6,6,6,6,0,6,6,0,0,6,6,0,0,0,6},
     {6,6,6,6,0,6,6,6,6,6,6,0,6,6,6,6,0,0,15,15,8,8,8,15,15,15,8,8,8,8,15,15,15,8,8,8,15,15,15,8,8,8,15,15,15,8,8,8,15,15,15,8,8,8,15,15,15,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,15,15,15,8,8,8,15,15,15,8,8,8,15,15,15,8,8,8,15,15,0,6,6,6,6,0,6,6,6,6,6,0,0,6,6,6,6,6,6,6,6,6,6,0,6,6,6},
     {0,0,6,0,6,6,6,0,6,6,6,6,0,6,6,0,6,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,6,6,6,6,0,0,0,0,0,6,6,6,6,0,0,0,0,0,6,6,6,6,0,6,6,6},
     {6,6,6,6,6,6,6,6,0,6,6,6,6,6,0,6,6,6,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}
    };

    // Todo lo de consola de ESTE nivel vive aqui (no en Juego).
    IronMan iron;            // jugador
    SpiderMan spider;        // amigo que entra y sale
    HeroeRebelde1 enem1;     // Antorcha Humana (1 frame en numeros)
    HeroeRebelde2 enem2;     // Daredevil (3 frames: 2 armas -> 1 arma -> 0 armas)
    Obstaculo roca1;         // roca grande (38, 21, 4 alto x 10 ancho)
    Obstaculo roca2;         // roca chata (60, 28, 1 alto x 11 ancho)
    Disparo balaIron;        // "=D" rapida a la derecha
    Disparo balaE1;          // "*" lenta a la izquierda (Antorcha)
    Disparo balaE2;          // "=-=" lenta a la izquierda (Daredevil)

    // HUD propio del Nivel 1 (usa el cuadro de Escenario
    // para verse tal cual como los demas niveles).
    // Izquierda el jugador, derecha las vidas de los 2 enemigos.
    void mostrarHUDNivel1() {
        mostrarHUD(iron.getVidas(),
            " OBJETIVO: Derrota a Antorcha y Daredevil",
            " A/D: MOVER  W/S: VOLAR ESPACIO: DISPARAR ESC: SALIR",
            " EVITA: (*) Antorcha y (=-=) Daredevil",
            "Iron Man");
        mostrarHUDEnemigos("Vida de los heroes rebeldes:",
            "Antorcha", enem1.getVidas(),
            "Daredevil", enem2.getVidas(), 3);
    }

    // Intenta que un enemigo dispare (1 de 20 por turno).
    // Si dispara, avisa al dueno con alDisparar() para que
    // Daredevil cambie su frame de armas (0 -> 1 -> 2 -> 0).
    void enemigoIntentaDisparar(Enemigo* dueno, Disparo* bala) {
        if (dueno->estaVivo() == false) {
            return;
        }
        if (bala->estaActiva() == true) {
            return;
        }
        int dado = rand() % 20;
        if (dado == 1) {
            int bx = dueno->getX() - 1;
            int by = dueno->getY() + 1;
            // La bala de Daredevil ocupa 3 casillas, sale 2 atras.
            if (bala->esDisparoDaredevil() == true) {
                bx = dueno->getX() - 3;
            }
            bala->disparar(bx, by, -1);
            dueno->alDisparar();
        }
    }

    // Mueve UNA bala enemiga y revisa si golpeo a IronMan.
    // Si es la bala "=-=" de Daredevil, revisa sus 3 casillas.
    void moverBalaEnemiga(Disparo* bala) {
        if (bala->estaActiva() == false) {
            return;
        }
        bala->borrar();
        int pasos = bala->getVelocidad();
        for (int i = 0; i < pasos; i++) {
            bool pudo = bala->avanzarUnPaso();
            if (pudo == false) {
                break;
            }
            bool golpe = iron.colisionaConBala(bala->getX(), bala->getY());
            // La bala de Daredevil es ancha: prueba x, x+1 y x+2.
            if (golpe == false && bala->esDisparoDaredevil() == true) {
                bool golpe2 = iron.colisionaConBala(bala->getX() + 1, bala->getY());
                bool golpe3 = iron.colisionaConBala(bala->getX() + 2, bala->getY());
                if (golpe2 == true || golpe3 == true) {
                    golpe = true;
                }
            }
            if (golpe == true) {
                bala->desactivar();
                bala->borrar();
                iron.recibirDano();
                mostrarHUDNivel1();
                break;
            }
        }
        if (bala->estaActiva() == true) {
            bala->dibujar();
        }
    }

    // Mueve la bala de IronMan y revisa si golpeo a algun enemigo.
    void moverBalaIron() {
        if (balaIron.estaActiva() == false) {
            return;
        }
        balaIron.borrar();
        int pasos = balaIron.getVelocidad();
        for (int i = 0; i < pasos; i++) {
            bool pudo = balaIron.avanzarUnPaso();
            if (pudo == false) {
                break;
            }
            if (enem1.estaVivo()) {
                bool golpe1 = enem1.colisionaConBala(balaIron.getX(), balaIron.getY());
                if (golpe1 == true) {
                    balaIron.desactivar();
                    enem1.recibirDano();
                    if (enem1.estaVivo() == false) {
                        balaE1.desactivarConBorrado();
                    }
                    mostrarHUDNivel1();
                    break;
                }
            }
            if (enem2.estaVivo()) {
                bool golpe2 = enem2.colisionaConBala(balaIron.getX(), balaIron.getY());
                if (golpe2 == true) {
                    balaIron.desactivar();
                    enem2.recibirDano();
                    if (enem2.estaVivo() == false) {
                        balaE2.desactivarConBorrado();
                    }
                    mostrarHUDNivel1();
                    break;
                }
            }
        }
        if (balaIron.estaActiva() == true) {
            balaIron.dibujar();
        }
    }

public:
    // Los personajes usan THIS como escenario (el mismo mapa Nivel1).
    Nivel1()
        : iron(this),
        spider(this, 6, 23),
        enem1(this),
        enem2(this),
        roca1(38, 21, 4, 10),
        roca2(60, 28, 1, 11),
        balaIron(this, false, 4),
        balaE1(this, true, 2),
        balaE2(this, true, 2, 12, false, true) {
    }
    ~Nivel1() {}

    // Carga SOLO su mapa (no conoce GameOver ni otros niveles).
    void CargarEscenario() override {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                mapaActual[i][j] = mapaNivel1[i][j];
            }
        }
    }

    bool EsGrisDeRoca(int x, int y) {
        if (mapaActual[y][x] != 8) {
            return false;
        }
        if (roca1.contiene(x, y)) {
            return true;
        }
        if (roca2.contiene(x, y)) {
            return true;
        }
        return false;
    }

    bool EsBordeNegroDeRoca(int x, int y) {
        if (mapaActual[y][x] != 0) {
            return false;
        }
        int dx[4] = { 1, -1, 0, 0 };
        int dy[4] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; i++) {
            int vx = x + dx[i];
            int vy = y + dy[i];
            if (vx < 0 || vx >= columnas) {
                continue;
            }
            if (vy < 0 || vy >= filas) {
                continue;
            }
            if (mapaActual[vy][vx] != 8) {
                continue;
            }
            bool cercaRoca1 = roca1.estaCerca(x, y);
            bool grisRoca1 = roca1.contiene(vx, vy);
            if (grisRoca1 && cercaRoca1) {
                return true;
            }
            bool cercaRoca2 = roca2.estaCerca(x, y);
            bool grisRoca2 = roca2.contiene(vx, vy);
            if (grisRoca2 && cercaRoca2) {
                return true;
            }
        }
        return false;
    }

    bool EsSolido(int x, int y) override {
        // Igual que Nivel 2 y 3: primero los bordes.
        // Sin esto se leeria fuera del mapa cuando un
        // enemigo patrulla hasta el borde de la pantalla.
        if (x < 0 || x >= columnas) {
            return true;
        }
        if (y < 0 || y >= filas) {
            return true;
        }
        if (EsGrisDeRoca(x, y)) {
            return true;
        }
        if (EsBordeNegroDeRoca(x, y)) {
            return true;
        }
        return false;
    }

    // Juega TODO el Nivel 1. Devuelve:
    // 0 = gano (pasaria a Nivel 2), 1 = perdio (Juego muestra GameOver), 2 = ESC.
    // continuar = false empieza de cero; = true sigue donde quedo con ESC.
    int jugar(bool continuar = false) {
        Console::Clear();
        Console::CursorVisible = false;

        // 1. Pinta el mapa.
        CargarEscenario();
        DibujarMapa();

        if (continuar == false) {
            // Empieza de cero: reinicia posiciones, vidas y balas.
            iron.revivir(25, 23);
            spider.revivir(6, 23);
            balaIron.desactivar();
            balaE1.desactivar();
            balaE2.desactivar();
            iron.dibujar();
            spider.dibujar();

            // 2. Dialogo inicial.
            dialogo("SPIDERMAN:", "Tony, esto se esta saliendo de control.");
            dialogo("IRONMAN:", "Solo intento detenerlos antes de que empeore.");
            dialogo("SPIDERMAN:", "Pero siguen siendo nuestros amigos.");
            dialogo("IRONMAN:", "Entonces ayudame a terminar esto rapido.");
            DibujarMapa();
            iron.dibujar();

            // 3. SpiderMan se retira a la izquierda (no desaparece).
            spider.dibujar();
            while (spider.getX() > 0) {
                spider.mover(-1, 0);
                Sleep(80);
            }
            spider.borrar();
            spider.setPos(-1, 23);

            // 4. Aparecen los 2 enemigos de ESTE nivel.
            enem1.revivir(100, 24);
            enem2.revivir(90, 23);
            // Daredevil empieza con sus 2 armas (fase 0).
            enem2.reiniciarArmas();
            enem1.dibujar();
            enem2.dibujar();
            mostrarHUDNivel1();
        }
        else {
            // Continua donde quedo con ESC: redibuja a cada uno
            // en su sitio (posiciones y vidas no se tocaron).
            iron.dibujar();
            spider.dibujar();
            enem1.dibujar();
            enem2.dibujar();
            if (balaIron.estaActiva()) {
                balaIron.dibujar();
            }
            if (balaE1.estaActiva()) {
                balaE1.dibujar();
            }
            if (balaE2.estaActiva()) {
                balaE2.dibujar();
            }
            mostrarHUDNivel1();
        }

        // 5. Bucle del nivel.
        while (true) {
            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 27) {
                    Console::CursorVisible = true;
                    return 2;
                }
                if (iron.estaVivo()) {
                    iron.moverConTecla(tecla);
                    if (tecla == ' ') {
                        if (balaIron.estaActiva() == false) {
                            int bx = iron.getX() + iron.getAncho();
                            int by = iron.getY() + 1;
                            balaIron.disparar(bx, by, 1);
                        }
                    }
                }
            }

            enem1.movimientoAleatorio();
            enem2.movimientoAleatorio();

            enemigoIntentaDisparar(&enem1, &balaE1);
            enemigoIntentaDisparar(&enem2, &balaE2);
            moverBalaEnemiga(&balaE1);
            moverBalaEnemiga(&balaE2);

            if (iron.estaVivo() == false) {
                Console::CursorVisible = true;
                return 1;
            }

            moverBalaIron();

            bool gano = (enem1.estaVivo() == false) && (enem2.estaVivo() == false);
            if (gano) {
                spider.borrar();
                int sx = spider.getX();
                if (sx < 6) {
                    int dado = rand() % 5;
                    if (dado == 1) {
                        sx = sx + 1;
                    }
                }
                spider.setPos(sx, 23);
                if (spider.getX() >= 0) {
                    spider.dibujar();
                }
                if (spider.getX() == 6) {
                    dialogo("SPIDERMAN:", "Tony... esto fue demasiado.");
                    dialogo("IRONMAN:", "Hice lo necesario para detenerlos.");
                    dialogo("SPIDERMAN:", "Eran nuestros amigos, no enemigos.");
                    dialogo("IRONMAN:", "Peter, no conoces toda la situacion.");
                    dialogo("SPIDERMAN:", "Entonces explicamela.");
                    dialogo("IRONMAN:", "No aqui. Regresemos a la torre.");
                    dialogo("SPIDERMAN:", "Esta bien... pero esto no termina aqui.");
                    Console::CursorVisible = true;
                    Console::SetCursorPosition(0, ALTO - 1);
                    return 0;
                }
            }

            Sleep(50);
        }
    }
};
