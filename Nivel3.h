#pragma once
#include "Escenario.h"
#include "CapitanAmerica.h"
#include "IronMan.h"
#include "SpiderMan.h"
#include "Disparo.h"

// ============================================================
// NIVEL 3 : hereda de Escenario y TIENE TODO lo de este nivel.
// - Su mapa (ciudad destruida, escombros = 7).
// - Capitan America (jugador), Iron Man (jefe con 6 vidas),
//   SpiderMan (aparece al final) y dos Disparos:
//   escudo (circulo de pixeles) y balaIron ("*").
// - El escudo NO es otra clase: es un Disparo configurado
//   como escudo (ver constructor). El bumeran (ida y vuelta)
//   se controla aqui con 3 variables simples.
// Juego SOLO lo invoca: nivel3.jugar().
// jugar() devuelve: 0 = gano, 1 = perdio, 2 = ESC.
// ============================================================
class Nivel3 : public Escenario
{
private:
    short mapaNivel3[30][120] = {
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,15,15,15,3,3,3,3,3,3,3,8,8},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,15,15,15,3,3,3,3,3,8,8,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,0,0,3,3,3,8,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,0,8,3,8,8,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,3,8,3,3,12,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,3,3,8,8,3,3,3,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,8,8,3,3,14,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,12,3,3,8,8,6,3,3,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,8,8,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,12,14,12,0,0,8,12,3,3,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,8,3,8,3,3,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,8,8,8,12,12,3,3,3,6,0},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,0,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,12,14,12,3,3,12,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,0,0,0,0,3,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,6,12,3,6,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,0,8,6,8,0,3,0,3,12,12},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,0,8,6,8,0,8,8,8,0,3,3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,3,3,3,3,0,0,0,0,0,0,0,3,3,0,3,12,14,12,12,3,3,3,3,3,3,3,6,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,0,8,3,14,12},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,8,0,3,3,0,0,0,5,5,5,6,5,0,5,0,5,0,0,3,3,3,0,8,6,8,0,8,0,0,3,3,0,0,12,0,12,14,12,3,3,3,3,3,3,8,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,8,8,3,3,3},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,8,0,3,3,0,5,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,3,0,12,14,5,3,0,3,3,3,3,3,3,3,8,8,0,0,3,3,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,0,4,0,8,8,8,0,8,0,0},
     {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,0,8,0,8,0,12,0,3,3,0,5,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,3,0,4,0,4,0,4,3,3,3,3,3,0,8,0,8,6,8,3,3,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,8,0,0,4,4,4,4,4,8,0},
     {3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,12,0,0,3,3,3,3,3,3,12,3,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,14,0,3,3,0,5,0,5,0,5,0,5,12,5,5,5,6,0,3,3,3,0,8,8,8,12,8,0,0,3,3,0,0,0,0,0,5,0,3,3,3,3,0,8,8,8,4,4,0,3,8,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,8,4,0,6,4,0,0,0,4,3,3},
     {3,3,3,8,8,3,3,3,3,0,0,3,3,3,12,14,8,0,3,3,3,3,3,12,14,12,3,3,3,3,3,3,3,3,3,0,8,8,8,8,8,8,8,0,3,3,0,5,5,5,5,5,5,5,14,5,5,5,5,0,3,3,3,0,8,8,12,14,12,8,0,3,3,0,0,6,0,0,5,5,3,3,3,3,0,8,8,8,4,0,6,0,8,0,3,3,3,3,3,3,8,3,3,3,3,3,3,3,0,8,0,0,0,4,0,6,0,4,3,3},
     {3,3,3,8,3,3,6,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,3,3,3,3,3,3,3,0,8,6,8,0,8,0,8,0,3,3,0,5,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,3,0,0,0,0,12,5,5,3,3,3,3,0,8,0,8,0,12,12,4,0,0,3,3,3,3,3,3,8,3,3,3,3,3,3,3,0,8,4,12,14,4,0,0,0,8,3,3},
     {3,3,6,3,3,3,12,3,3,3,3,3,3,3,0,3,3,3,3,3,3,3,3,0,5,0,5,0,3,3,0,3,3,3,3,0,8,8,8,8,8,8,8,0,3,3,0,5,5,5,0,5,6,5,6,5,0,5,0,0,3,3,3,0,8,0,8,8,8,0,0,3,3,0,14,0,0,12,4,5,3,3,3,3,0,8,8,8,4,14,14,0,0,0,3,3,3,3,3,8,3,6,3,3,3,3,3,3,0,8,4,4,4,4,12,12,14,4,3,3},
     {3,0,12,3,3,3,14,12,3,3,3,0,0,12,8,3,3,3,3,3,3,0,0,5,5,5,5,5,0,3,5,0,3,3,3,0,8,8,8,8,8,8,8,0,3,3,0,5,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,3,0,4,0,0,0,4,4,5,5,0,3,0,8,4,8,4,12,14,0,0,0,3,3,3,3,3,3,3,12,3,3,3,3,3,3,0,8,8,8,8,4,0,4,0,8,0,0},
     {3,0,12,3,3,3,0,0,3,3,3,12,12,12,4,3,3,3,3,3,3,0,5,5,5,5,5,5,5,3,5,5,3,3,3,0,8,6,8,6,8,0,8,0,3,3,0,5,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,3,0,5,14,14,14,12,0,4,5,0,3,0,8,0,12,12,0,0,12,12,0,3,3,12,3,3,12,12,14,12,3,3,3,3,3,0,8,8,8,8,8,8,8,8,8,8,0},
     {3,12,14,12,0,3,8,0,3,0,8,0,3,0,4,8,8,0,3,3,3,0,5,0,5,0,5,0,5,3,5,0,0,3,3,0,8,12,8,8,8,8,8,0,3,3,0,5,6,5,0,5,0,5,5,5,5,5,6,0,3,3,3,0,8,0,8,0,8,8,0,3,3,0,4,5,12,14,14,12,5,0,0,3,0,8,4,12,12,12,8,12,12,0,3,3,14,12,12,14,3,0,3,0,3,3,3,3,0,8,8,8,8,8,8,8,8,8,8,0},
     {3,0,0,0,8,0,8,0,3,0,8,8,0,8,8,8,8,0,3,3,3,0,5,5,5,5,5,5,5,0,5,5,5,0,3,0,12,14,8,8,8,8,8,0,3,3,0,6,5,5,5,5,5,5,5,5,5,5,5,0,3,3,3,0,8,8,8,8,8,8,0,3,7,7,7,7,7,7,4,4,5,5,0,3,0,8,4,4,8,8,4,4,8,7,3,0,0,8,0,0,0,8,0,0,3,3,3,3,0,8,8,8,8,8,0,8,0,8,0,0},
     {3,0,8,0,8,0,8,0,3,0,8,8,8,8,8,8,8,0,3,7,7,7,7,7,5,5,5,5,5,5,5,5,5,0,3,0,8,7,7,6,8,12,8,0,3,3,0,12,5,12,12,5,5,5,7,7,7,7,7,0,3,3,3,0,8,8,8,8,8,8,0,3,7,7,8,8,8,7,5,5,5,5,0,3,0,8,0,8,0,8,0,8,7,7,7,7,8,0,8,0,8,8,8,0,3,3,3,3,0,8,8,8,8,8,8,8,8,8,8,0},
     {3,0,8,8,8,8,8,0,3,0,8,8,8,6,8,6,8,0,7,7,7,7,7,7,7,7,7,5,5,5,5,0,5,0,3,7,7,8,7,7,12,14,8,0,3,3,12,14,12,12,14,12,5,5,7,7,7,7,7,7,7,7,3,0,8,0,8,8,8,6,0,3,7,7,7,7,7,7,7,7,7,0,7,7,0,8,8,8,8,8,8,7,7,7,7,7,7,8,8,8,8,8,8,7,7,7,7,3,0,8,8,8,8,8,8,8,8,8,8,0},
     {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,8,0,0,0,0,0,0,8,8,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,8,8,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,8,8,0,0,8,8,8,8,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,8,8,8,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,8,8,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,8,8,0,0,0,0,8,8,0,0,0,0,0,0,0,0,0,0,0,0,0},
     {14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0,14,14,14,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    int caidoX;   // donde queda el cuerpo de Iron Man al perder
    int caidoY;

    CapitanAmerica capi;   // jugador (pixel-art 9 x 4)
    IronMan ironman;       // jefe final (pixel-art 9 x 4, 6 vidas)
    SpiderMan spider;      // aparece al final (pixel-art 9 x 4)

    // El escudo y la bala son el MISMO tipo: Disparo.
    // escudo = Disparo con esEscudo = true (circulo 6 x 3).
    // balaIron = Disparo enemigo normal ("*").
    Disparo escudo;
    Disparo balaIron;

    // Estado del bumeran (el Disparo solo avanza, el Nivel decide).
    int escudoXInicio;     // desde donde se lanzo (ahi regresa)
    int escudoAlcance;     // distancia maxima de ida
    bool escudoVolviendo;  // false = ida, true = regreso
    bool escudoYaGolpeo;   // ya daño en esta pasada (ida o vuelta)

    // HUD propio del Nivel 3 (usa el cuadro de Escenario
    // para verse tal cual como los demas niveles).
    // Izquierda el jugador, derecha la vida del jefe (6 vidas).
    void mostrarHUDNivel3() {
        mostrarHUD(capi.getVidas(),
            " OBJETIVO: Derrota a Iron Man",
            " A/D: MOVER  W/S: VOLAR ESPACIO: ESCUDO ESC: SALIR",
            " El escudo bloquea disparos y regresa",
            "Capitan America");
        mostrarHUDEnemigo("Vida de Iron Man:",
            "Iron Man", ironman.getVidas(), 6);
    }

    // ¿El punto (bx, by) esta dentro del rectangulo del escudo?
    bool escudoBloquea(int bx, int by) {
        if (escudo.estaActiva() == false) {
            return false;
        }
        int ex = escudo.getX();
        int ey = escudo.getY();
        int ancho = escudo.getAncho();
        int alto = escudo.getAlto();
        if (bx >= ex && bx < ex + ancho && by >= ey && by < ey + alto) {
            return true;
        }
        return false;
    }

    // ¿El escudo toca al rectangulo (ex, ey, eAncho, eAlto)?
    // Solo golpea UNA vez por pasada (ida o vuelta).
    bool escudoGolpea(int ex, int ey, int eAncho, int eAlto) {
        if (escudo.estaActiva() == false) {
            return false;
        }
        if (escudoYaGolpeo == true) {
            return false;
        }
        int sx = escudo.getX();
        int sy = escudo.getY();
        int ancho = escudo.getAncho();
        int alto = escudo.getAlto();
        bool tocaX = (sx < ex + eAncho) && (sx + ancho > ex);
        bool tocaY = (sy < ey + eAlto) && (sy + alto > ey);
        if (tocaX && tocaY) {
            escudoYaGolpeo = true;
            return true;
        }
        return false;
    }

    // Lanza el escudo desde la mano del Capitan hacia la derecha.
    void lanzarEscudo() {
        if (escudo.estaActiva() == true) {
            return;
        }
        int inicioX = capi.getX() + capi.getAncho();
        int inicioY = capi.getY() + 1;
        escudo.disparar(inicioX, inicioY, 1);
        escudoXInicio = inicioX;
        escudoVolviendo = false;
        escudoYaGolpeo = false;
    }

    // IronMan se mueve solo: 1 de cada 4 turnos da un paso al azar.
    void moverIronMan() {
        if (ironman.estaVivo() == false) {
            return;
        }
        if (rand() % 4 != 0) {
            return;
        }

        // Vertical: a veces se alinea con la altura del Capitan.
        if (rand() % 2 == 0) {
            char tecla = 'w';
            if (rand() % 2 == 0 && capi.getY() != ironman.getY()) {
                if (capi.getY() < ironman.getY()) {
                    tecla = 'w';
                }
                else {
                    tecla = 's';
                }
            }
            else {
                if (rand() % 2 == 0) {
                    tecla = 'w';
                }
                else {
                    tecla = 's';
                }
            }
            ironman.moverConTecla(tecla);
            return;
        }

        // Horizontal (como antes).
        int dx = 1;
        if (rand() % 2 == 0) {
            dx = -1;
        }
        // No se encima con Capitan America.
        int nuevoX = ironman.getX() + dx;
        bool tapa = (nuevoX < capi.getX() + capi.getAncho()) &&
            (nuevoX + ironman.getAncho() > capi.getX());
        if (tapa) {
            return;
        }
        ironman.mover(dx, 0);
    }

    // IronMan intenta disparar (1 de 20 por turno).
    void ironManIntentaDisparar() {
        if (ironman.estaVivo() == false) {
            return;
        }
        if (balaIron.estaActiva() == true) {
            return;
        }
        int dado = rand() % 20;
        if (dado == 1) {
            int bx = ironman.getX() - 1;
            int by = ironman.getY() + 1;
            balaIron.disparar(bx, by, -1);
        }
    }

    // Mueve la bala de IronMan y revisa si golpeo al Capitan.
    // El escudo la bloquea si la toca.
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
            if (escudoBloquea(balaIron.getX(), balaIron.getY())) {
                balaIron.desactivar();
                break;
            }
            bool golpe = capi.colisionaConBala(balaIron.getX(), balaIron.getY());
            if (golpe == true) {
                balaIron.desactivar();
                balaIron.borrar();
                capi.recibirDano();
                mostrarHUDNivel3();
                break;
            }
        }
        if (balaIron.estaActiva() == true) {
            balaIron.dibujar();
        }
    }

    // Mueve el escudo como bumeran: ida hasta el alcance o muro,
    // luego regreso hasta la mano. Daña a Iron Man una vez por pasada.
    void moverEscudo() {
        if (escudo.estaActiva() == false) {
            return;
        }
        escudo.borrar();
        int pasos = escudo.getVelocidad();
        for (int i = 0; i < pasos && escudo.estaActiva(); i++) {
            // ¿Chocaria con muro si avanza un paso mas?
            int paso = 1;
            if (escudoVolviendo == true) {
                paso = -1;
            }
            int destinoX = escudo.getX() + paso;
            int destinoY = escudo.getY();
            bool chocaMuro = HaySolidoEnZona(destinoX, destinoY,
                escudo.getAncho(), escudo.getAlto());
            if (chocaMuro == true) {
                if (escudoVolviendo == false) {
                    // Choco en la ida: da la vuelta.
                    escudoVolviendo = true;
                    escudo.invertirDireccion();
                    escudoYaGolpeo = false;
                }
                else {
                    // Choco al regresar: se pierde.
                    escudo.desactivar();
                    break;
                }
            }
            else {
                bool pudo = escudo.avanzarUnPaso();
                if (pudo == false) {
                    // Salio de pantalla.
                    break;
                }
            }

            // ¿Llego al alcance maximo? Entonces regresa.
            int distancia = escudo.getX() - escudoXInicio;
            if (distancia < 0) {
                distancia = -distancia;
            }
            if (escudoVolviendo == false && distancia >= escudoAlcance) {
                escudoVolviendo = true;
                escudo.invertirDireccion();
                escudoYaGolpeo = false;
            }

            // ¿Regreso a la mano? Entonces se apaga.
            if (escudoVolviendo == true) {
                // Vuelve hacia la izquierda: llego cuando bajo hasta el inicio.
                bool llego = (escudo.getX() <= escudoXInicio);
                if (llego) {
                    escudo.desactivarConBorrado();
                    break;
                }
            }

            // ¿Golpeo a Iron Man?
            if (ironman.estaVivo() &&
                escudoGolpea(ironman.getX(), ironman.getY(),
                    ironman.getAncho(), ironman.getAlto())) {
                int ix = ironman.getX();
                int iy = ironman.getY();
                ironman.recibirDano();
                mostrarHUDNivel3();
                if (ironman.estaVivo() == false) {
                    balaIron.desactivarConBorrado();
                    caidoX = ix;
                    if (caidoX > ANCHO - 10) {
                        caidoX = ANCHO - 10;
                    }
                    caidoY = iy + ironman.getAlto() - 4;
                }
            }
        }
        // Repara lo que el escudo pudo borrar al pasar.
        if (ironman.estaVivo()) {
            ironman.dibujar();
        }
        capi.dibujar();
        escudo.dibujar();
    }

public:
    // Los personajes usan THIS como escenario (el mismo mapa Nivel3).
    Nivel3()
        : capi(this),
        ironman(this, 6),
        spider(this, 6, 25),
        escudo(this, false, 2, 14, true, false, true),
        balaIron(this, true, 3) {
        caidoX = 0;
        caidoY = 0;
        escudoXInicio = 0;
        escudoAlcance = 40;
        escudoVolviendo = false;
        escudoYaGolpeo = false;
    }
    ~Nivel3() {}

    // Carga SOLO su mapa (no conoce GameOver ni otros niveles).
    void CargarEscenario() override {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                mapaActual[i][j] = mapaNivel3[i][j];
            }
        }
    }

    bool EsSolido(int x, int y) override {
        // Igual que el Nivel 1: lo pintado es fondo y se pasa por encima.
        // Los edificios (7) y la calle (8) no frenan; solo el borde frena.
        // El tope de arriba lo da el movimiento (fila 21) y el de
        // abajo el piso, igual que IronMan en el Nivel 1.
        return HayColision(x, y);
    }

    // Juega TODO el Nivel 3. Devuelve:
    // 0 = gano, 1 = perdio (Juego muestra GameOver), 2 = ESC.
    // continuar = false empieza de cero; = true sigue donde quedo con ESC.
    int jugar(bool continuar = false) {
        Console::Clear();
        Console::CursorVisible = false;

        // 1. Pinta el mapa.
        CargarEscenario();
        DibujarMapa();

        if (continuar == false) {
            // 2. Empieza de cero: reinicia posiciones, vidas y disparos.
            // ironman.revivir recupera sus 6 vidas de jefe.
            capi.revivir(15, 25);
            ironman.revivir(95, 25);
            spider.revivir(-1, 25);
            escudo.desactivar();
            balaIron.desactivar();
            caidoX = 0;
            caidoY = 0;
            escudoVolviendo = false;
            escudoYaGolpeo = false;

            // 3. Los personajes se ven DURANTE el dialogo inicial.
            capi.dibujar();
            ironman.dibujar();
            mostrarHUDNivel3();

            dialogo("CAPITAN AMERICA:", "Tony, esto no debe terminar asi.");
            dialogo("IRONMAN:", "Ya tomaste tu eleccion y yo la mia.");
            dialogo("CAPITAN AMERICA:", "No cambiaras de ideal, verdad?");
            dialogo("IRONMAN:", "No lo hice antes ni menos ahora.");
            dialogo("CAPITAN AMERICA:", "Terminemos con esto aqui y ahora.");
            DibujarMapa();

            capi.dibujar();
            ironman.dibujar();
            mostrarHUDNivel3();
        }
        else {
            // Continua donde quedo con ESC: redibuja a cada uno
            // en su sitio (posiciones y vidas no se tocaron).
            capi.dibujar();
            ironman.dibujar();
            if (escudo.estaActiva()) {
                escudo.dibujar();
            }
            if (balaIron.estaActiva()) {
                balaIron.dibujar();
            }
            mostrarHUDNivel3();
        }

        // 4. Bucle del nivel.
        while (true) {
            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 27) {
                    Console::CursorVisible = true;
                    return 2;
                }
                if (capi.estaVivo()) {
                    capi.moverConTecla(tecla);
                    if (tecla == ' ') {
                        lanzarEscudo();
                    }
                }
            }

            moverIronMan();
            ironManIntentaDisparar();
            moverBalaIron();

            if (capi.estaVivo() == false) {
                Console::CursorVisible = true;
                return 1;
            }

            moverEscudo();

            bool gano = (ironman.estaVivo() == false);
            if (gano) {
                ironman.dibujarDerrotado(caidoX, caidoY);
                spider.borrar();
                int sx = spider.getX();
                if (sx < 6) {
                    int dado = rand() % 5;
                    if (dado == 1) {
                        sx = sx + 1;
                    }
                }
                spider.setPos(sx, 25);
                if (spider.getX() >= 0) {
                    spider.dibujar();
                }
                if (spider.getX() == 6) {
                    dialogo("CAPITAN AMERICA:", "Basta... ya no peleamos por la gente.");
                    dialogo("SPIDERMAN:", "Capitan, lo teniamos! Estaba vencido!");
                    dialogo("CAPITAN AMERICA:", "Mira a tu alrededor, Peter. Mira la ciudad.");
                    dialogo("CAPITAN AMERICA:", "Esto no es ganar. Hay que parar ahora.");
                    dialogo("SPIDERMAN:", "No... no puede terminar asi.");
                    dialogo("IRONMAN:", "...Cap. Vas a tener que venir conmigo.");
                    Console::CursorVisible = true;
                    Console::SetCursorPosition(0, ALTO - 1);
                    return 0;
                }
            }

            Sleep(50);
        }
    }
};
