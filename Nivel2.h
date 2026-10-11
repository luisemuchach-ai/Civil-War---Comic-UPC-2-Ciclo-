#pragma once
#include "Escenario.h"
// Personajes
#include "SpiderMan.h"
#include "IronMan.h"
// Enemigos
#include "GuardStark1.h"
#include "DronStark.h"
// Proyectiles (todos son Disparo: balas, escudo y telaraña).
#include "Disparo.h"

// ============================================================
// NIVEL 2 : hereda de Escenario y TIENE TODO lo de este nivel.
// - Su mapa (la casa: cielo, techo, cuartos y salida).
// - Sus personajes, balas, telaraña, dialogos y su forma de jugar.
// Juego SOLO lo invoca: nivel2.jugar(). No guarda nada del nivel.
// ============================================================
class Nivel2 : public Escenario
{
private:

    short mapaNivel2[30][120] = {
        {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,15,15,15,15,15,15,15,15,15,15,15,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,14,14,14,14,14,14,14,8,8,0,0},
        {0,0,7,7,7,7,7,7,0,0,0,0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,0,0,0,0,0,7,7,7,7,7,7,7,0,0,0,0,0,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,7,7,7,7,7,7,7,14,14,14,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,14,14,14,7,7,7,7,7,7,7,6,6,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,6,6,7,7,7,7,7,14,14,14,7,7,7,7,7,7,7,7,7,14,14,14,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,0,11,11,15,15,15,15,15,15,11,11,11,11,0,0,11,11,11,11,15,15,15,15,15,15,11,11,0,7,7,7,7,7,6,6,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,8,11,11,11,11,11,15,15,15,15,11,11,0,0},
        {0,0,7,7,7,8,8,8,7,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,7,8,8,8,7,7,7,7,6,6,7,7,7,7,7,0,11,15,15,15,15,15,15,15,15,11,11,11,0,0,11,11,11,15,15,15,15,15,15,15,15,11,0,7,7,7,7,7,6,6,7,7,7,7,0,3,3,3,3,3,3,3,3,3,3,3,3,0,7,7,7,7,7,7,0,8,11,11,11,15,15,15,15,15,15,15,11,0,0},
        {0,0,7,7,7,8,14,8,7,0,3,3,3,11,11,11,11,11,11,15,15,11,11,11,11,11,11,3,3,3,0,7,8,14,8,7,7,7,7,6,6,7,7,7,7,7,0,11,11,11,11,11,11,11,11,11,11,11,11,0,0,11,11,11,11,11,11,11,11,11,11,11,11,0,7,7,7,7,7,6,6,7,7,7,7,0,3,3,3,11,11,11,11,3,12,12,3,3,0,7,7,7,7,7,7,0,8,11,11,11,15,15,15,15,15,15,15,11,0,0},
        {0,0,7,7,7,8,14,8,7,0,3,3,3,11,11,11,11,11,11,15,15,11,11,11,11,11,11,3,3,3,0,7,8,14,8,7,7,7,7,6,6,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,6,6,7,7,7,7,0,3,3,3,3,3,3,3,3,3,3,3,3,0,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,8,8,8,7,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,7,8,8,8,7,7,7,7,6,6,7,7,7,7,7,0,11,11,11,11,11,11,11,11,11,11,11,11,0,0,11,11,11,11,11,11,11,11,11,11,11,11,0,7,7,7,7,7,6,6,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,0,11,11,11,11,11,11,11,11,11,11,11,11,0,0,11,11,11,11,11,11,11,11,11,11,11,11,0,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,7,7,7,7,7,7,6,6,7,7,7,7,7,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,7,0,8,11,11,11,11,11,11,11,11,11,11,11,0,0},
        {0,0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,7,6,6,7,7,7,7,8,8,8,8,8,8,8,7,7,7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0},
        {0,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };


    SpiderMan spider;      
    IronMan iron;          

    GuardStark guardia;   
    DronStark dron;        

    Disparo balaGuardia;  
    Disparo balaDron;     

    Disparo telarana;

    bool estaEnSalida(int x, int y)
    {

        return (x >= 108 && x <= 117 && y >= 10 && y <= 24);
    }


    void mostrarHUDNivel2()
    {
        string linea3 = " GUARDIA: cubrete y esquiva las balas enemigas.";

        if (guardia.estaVivo() == false)
        {
            linea3 = " DRON: DISPARA AL DRON PARA ESCAPAR";
        }

        mostrarHUD(spider.getVidas(),
            " OBJETIVO: Destruye al Guardia y al Dron",
            " A/D: MOVER  W/S: SUBIR-BAJAR ESPACIO: RED ESC: SALIR",
            linea3,
            "Spider-Man");
        mostrarHUDEnemigos("Vidas de los dispositivos de Stark:",
            "Guardia", guardia.getVidas(),
            "Dron", dron.getVidas(), 3);
    }

    // Flecha amarilla al centro cuando ya no hay enemigos:
    // se dibuja cada turno porque Spider-Man pasa por encima.
    void mostrarMensajeEscape()
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::Yellow;

        string texto = "VETE A LA DERECHA PARA ESCAPAR ->";
        int x = (ANCHO - (int)texto.length()) / 2;

        Console::SetCursorPosition(x, 14);
        cout << texto;
    }

    bool balaChocaRoca(int x, int y)
    {
        if (x < 0 || x >= columnas || y < 0 || y >= filas)
        {
            return true;
        }

        if (mapaActual[y][x] == 8)
            return true;

        return false;
    }

    // El Guardia intenta disparar (1 de 28 por turno).
    // Dispara dirigido al centro de Spider-Man.
    void guardiaIntentaDisparar()
    {
        if (guardia.estaVivo() == false)
            return;

        if (balaGuardia.estaActiva() == true)
            return;

        int dado = rand() % 28;

        if (dado == 1)
        {
            int centroGuardiaX =
                guardia.getX() + guardia.getAncho() / 2;

            int centroGuardiaY =
                guardia.getY() + guardia.getAlto() / 2;

            int centroSpiderX =
                spider.getX() + spider.getAncho() / 2;

            int centroSpiderY =
                spider.getY() + spider.getAlto() / 2;

            int bx;

            if (centroSpiderX < centroGuardiaX)
                bx = guardia.getX() - 1;
            else
                bx = guardia.getX() + guardia.getAncho();

            int by = centroGuardiaY;

            // DISPARO DIRECTO: no se va a una diagonal fija.
            balaGuardia.dispararHacia(
                bx,
                by,
                centroSpiderX,
                centroSpiderY
            );
        }
    }


    // Mueve la bala del Guardia y revisa si golpeo a Spider-Man.
    // La roca (8) la bloquea.
    void moverBalaGuardia()
    {
        if (balaGuardia.estaActiva() == false)
            return;

        balaGuardia.borrar();

        int pasos = balaGuardia.getVelocidad();

        for (int i = 0; i < pasos; i++)
        {
            bool pudo = balaGuardia.avanzarUnPaso();

            if (pudo == false)
                break;

            // La roca (8) bloquea la bala del Guardia.
            if (balaChocaRoca(balaGuardia.getX(), balaGuardia.getY()))
            {
                balaGuardia.borrar();
                balaGuardia.desactivar();
                break;
            }

            // ¿La bala golpeo a Spider-Man? Pierde 1 vida.
            if (spider.colisionaConBala(balaGuardia.getX(), balaGuardia.getY()))
            {
                balaGuardia.desactivar();
                balaGuardia.borrar();
                spider.recibirDano();
                mostrarHUDNivel2();
                break;
            }
        }
        if (balaGuardia.estaActiva() == true)
            balaGuardia.dibujar();
    }

    // El Dron intenta disparar (1 de 30 por turno).
    // Dispara vertical hacia abajo desde su centro.
    void dronIntentaDisparar()
    {
        if (dron.estaVivo() == false)
            return;

        if (balaDron.estaActiva() == true)
            return;

        int dado = rand() % 30;

        if (dado == 1)
        {
            int bx = dron.getX() + dron.getAncho() / 2;
            int by = dron.getY() + dron.getAlto();

            balaDron.dispararVertical(bx, by, 1);
        }
    }


    // Mueve la bala del Dron y revisa si golpeo a Spider-Man.
    // La roca (8) es cobertura: la bloquea.
    void moverBalaDron()
    {
        if (balaDron.estaActiva() == false)
            return;

        balaDron.borrar();

        int pasos = balaDron.getVelocidad();

        for (int i = 0; i < pasos; i++)
        {
            bool pudo = balaDron.avanzarUnPaso();

            if (pudo == false) break;

            // La roca (8) es cobertura: bloquea la bala del Dron.
            if (balaChocaRoca(balaDron.getX(), balaDron.getY()))
            {
                balaDron.borrar();
                balaDron.desactivar();
                break;
            }

            // ¿La bala golpeo a Spider-Man? Pierde 1 vida.
            if (spider.colisionaConBala(balaDron.getX(), balaDron.getY()))
            {
                balaDron.desactivar();
                balaDron.borrar();

                spider.recibirDano();
                mostrarHUDNivel2();
                break;
            }
        }

        if (balaDron.estaActiva() == true)
            balaDron.dibujar();
    }


    // Mueve la telaraña y revisa si golpeo al Guardia o al Dron.
    // - Al Guardia le da directo.
    // - Al Dron solo lo daña si antes toco el marco negro (rebote).
    void moverTelarana()
    {
        if (telarana.estaActiva() == false) return;
        telarana.borrar();
        int pasos = telarana.getVelocidad();

        if (spider.estaVivo() == true)
            spider.dibujar();

        if (guardia.estaVivo() == true)
            guardia.dibujar();

        if (dron.estaVivo() == true)
            dron.dibujar();

        for (int i = 0; i < pasos; i++)
        {
            int xActual = telarana.getX();
            int yActual = telarana.getY();

            // La telaraña NO se corrige en el aire: sale en diagonal
            // hacia arriba (restando Y) del lado del Dron y sigue recto.
            // Si falla o toca el techo, desaparece sola.
            int siguienteX = xActual + telarana.getDirX();
            int siguienteY = yActual + telarana.getDirY();

            // ¿Salio del mapa? Se apaga.
            if (siguienteX < 0 || siguienteX >= columnas || siguienteY < 0 || siguienteY >= filas)
            {
                telarana.desactivar(); return;
            }

            // ¿Choco con roca (8)? Se apaga.
            if (mapaActual[siguienteY][siguienteX] == 8)
            {
                telarana.desactivar();
                return;
            }

            // ¿Entro al marco negro del cuarto del Dron (0)?
            // Solo la primera vez cuenta como rebote.
            bool marcoDron =
                siguienteX >= 46 &&
                siguienteX <= 73 &&
                siguienteY >= 11 &&
                siguienteY <= 19 &&
                mapaActual[siguienteY][siguienteX] == 0;

            if (marcoDron == true &&
                telarana.yaReboto() == false)
            {
                telarana.marcarRebote();
                telarana.avanzar();
            }
            else if (telarana.yaReboto() == true)
            {
                // Ya reboto una vez en el marco: sigue recto hasta el techo.
                // Asi no se queda rebotando en su sitio dentro del cuarto.
                // Si no toca a nadie, se apaga al salir del mapa o en roca
                // (lo revisan los dos if de arriba en el siguiente paso).
                telarana.avanzar();
            }
            // Rebote en paredes negras (0): revisa al costado y
            // arriba/abajo, voltea la direccion que choco y avanza.
            else
            {
                bool choqueVertical = false;
                bool choqueHorizontal = false;
                int revisarX = xActual + telarana.getDirX();

                if (revisarX >= 0 && revisarX < columnas)
                {
                    if (mapaActual[yActual][revisarX] == 0)
                        choqueVertical = true;
                }

                int revisarY = yActual + telarana.getDirY();

                if (revisarY >= 0 && revisarY < filas)
                {
                    if (mapaActual[revisarY][xActual] == 0)
                        choqueHorizontal = true;
                }

                if (choqueVertical == true)
                    telarana.rebotarHorizontal();

                if (choqueHorizontal == true)
                    telarana.rebotarVertical();

                if (choqueVertical == false && choqueHorizontal == false && mapaActual[siguienteY][siguienteX] == 0)
                {
                    telarana.rebotarHorizontal();
                    telarana.rebotarVertical();
                }
                telarana.avanzar();
            }

            // ¿Golpeo al Guardia? Le quita 1 vida y se apaga.
            if (guardia.estaVivo() == true)
            {
                if (guardia.colisionaConBala(telarana.getX(), telarana.getY()))
                {
                    guardia.recibirDano();
                    telarana.desactivarConBorrado();

                    if (guardia.estaVivo() == false)
                    {
                        balaGuardia.desactivarConBorrado();
                    }
                    // Actualiza barras y fase (Guardia o Dron) del HUD.
                    mostrarHUDNivel2();
                    return;
                }
            }


            // ¿Golpeo al Dron? Solo vale despues del Guardia:
            // primero se derrota al Guardia y luego al Dron.
            // Ademas solo lo daña si ya reboto en el marco.
            // Si no, se apaga sin hacer daño.
            if (dron.estaVivo() == true && guardia.estaVivo() == false)
            {
                if (dron.colisionaConBala(telarana.getX(), telarana.getY()))
                {
                    if (telarana.yaReboto() == true)
                    {
                        dron.recibirDano();
                        if (dron.estaVivo() == false)
                            balaDron.desactivarConBorrado();
                    }
                    telarana.desactivarConBorrado();
                    // Actualiza la barra del Dron en el cuadro derecho.
                    mostrarHUDNivel2();
                    return;
                }
            }
        }

        // Dibuja la telaraña si sigue volando.
        if (telarana.estaActiva() == true)
        {
            telarana.dibujar();
        }
    }

public:

    Nivel2()
        : spider(this, 5, 22),
        iron(this),
        guardia(this),
        dron(this, 48, 12),

        // Las balas enemigas son negras (0) para verse
        balaGuardia(this, true, 3, 0, true),
        balaDron(this, true, 3, 0, true),

        // Red: del jugador (false), rapida (10), atraviesa muros (true)
        telarana(this, false, 10, 15, true, false, false, true)
    {
    }

    ~Nivel2() {}

    void CargarEscenario() override
    {
        CargarMapa(mapaNivel2);
    }


    bool EsSolido(int x, int y) override
    {
        if (x < 0 || x >= columnas || y < 0 || y >= filas)
            return true;

        // La salida SI debe dejar pasar
        if (estaEnSalida(x, y))
            return false;

        if (mapaActual[y][x] == 0)
            return true;

        if (mapaActual[y][x] == 8)
            return true;

        return false;
    }

    // Juega TODO el Nivel 2. Devuelve:
    // 0 = gano (pasaria al Nivel 3), 1 = perdio (Juego muestra GameOver), 2 = ESC.
    // continuar = false empieza de cero; = true sigue donde quedo con ESC.
    int jugar(bool continuar = false)
    {
        Console::Clear();
        Console::CursorVisible = false;

        // 1. Pinta el mapa.
        CargarEscenario();
        DibujarMapa();

        if (continuar == false) {
            // Empieza de cero: reinicia posiciones, vidas y disparos.
            spider.revivir(5, 22);
            guardia.revivir(96, 22);
            dron.revivir(48, 12);
            balaGuardia.desactivar();
            balaDron.desactivar();
            telarana.desactivar();

            iron.dibujar();
            spider.dibujar();

            // 2. Dialogo inicial.
            dialogo("IRONMAN:", "Peter, ahora podemos hablar.");
            dialogo("SPIDERMAN:", "Lo pense, Tony. No puedo seguir apoyando esto.");
            dialogo("IRONMAN:", "Estas tomando una decision muy seria.");
            dialogo("SPIDERMAN:", "Lo se. Por eso tengo que irme.");
            dialogo("IRONMAN:", "Peter, no hagas esto.");
            dialogo("SPIDERMAN:", "Lo siento, Tony.");

            DibujarMapa();

            // 3. IronMan se va: Spider-Man queda solo contra los 2 enemigos.
            iron.borrar();
            iron.setPos(-100, -100);

            spider.dibujar();

            guardia.dibujar();
            dron.dibujar();

            mostrarHUDNivel2();
        }
        else {
            // Continua donde quedo con ESC: redibuja a cada uno
            // en su sitio (posiciones y vidas no se tocaron).
            spider.dibujar();
            guardia.dibujar();
            dron.dibujar();
            if (balaGuardia.estaActiva()) {
                balaGuardia.dibujar();
            }
            if (balaDron.estaActiva()) {
                balaDron.dibujar();
            }
            if (telarana.estaActiva()) {
                telarana.dibujar();
            }
            mostrarHUDNivel2();
        }

        int contadorDron = 0;
        int contadorGuardia = 0;

        // 4. Bucle del nivel.
        while (true)
        {
            if (_kbhit())
            {
                char tecla = _getch();

                if (tecla == 27)
                {
                    Console::CursorVisible = true;
                    return 2;
                }

                if (spider.estaVivo() == true)
                {
                    // Igual que IronMan en el Nivel 1: una sola llamada.
                    spider.moverConTecla(tecla);


                    // Lanzamiento de Telaraña
                    if (tecla == ' ')
                    {
                        if (telarana.estaActiva() == true)
                        {
                            telarana.desactivarConBorrado();
                        }

                        int direccionX;

                        // Guardia vivo: tiro recto al lado donde esta.
                        if (guardia.estaVivo() == true)
                        {
                            if (guardia.getX() > spider.getX())
                                direccionX = 1;
                            else
                                direccionX = -1;

                            int tx;

                            if (direccionX == 1)
                                tx = spider.getX() + spider.getAncho();
                            else
                                tx = spider.getX() - 1;
                            int ty = spider.getY() + 1;
                            telarana.dispararDireccion(tx, ty, direccionX, 0);
                        }

                        // Guardia muerto: tiro en diagonal hacia arriba,
                        // del lado donde esta el Dron.
                        else if (dron.estaVivo() == true)
                        {
                            if (dron.getX() > spider.getX())
                                direccionX = 1;
                            else
                                direccionX = -1;
                            int tx;

                            if (direccionX == 1)
                                tx = spider.getX() + spider.getAncho();
                            else
                                tx = spider.getX() - 1;

                            int ty = spider.getY();
                            telarana.dispararDireccion(tx, ty, direccionX, -1);
                        }
                    }
                }
            }
            // Guardia: patrulla su zona cada 5 turnos.
            contadorGuardia++;

            if (contadorGuardia >= 5)
            {
                guardia.moverZona();
                contadorGuardia = 0;
            }

            // Dron: va de izquierda a derecha cada 3 turnos.
            contadorDron++;

            if (contadorDron >= 3)
            {
                dron.moverHorizontal();
                contadorDron = 0;
            }

            // Disparos de los 2 enemigos y red del jugador.
            guardiaIntentaDisparar();
            moverBalaGuardia();

            dronIntentaDisparar();
            moverBalaDron();

            moverTelarana();

            // Si Spider-Man murio, se perdio (Juego muestra GameOver).
            if (spider.estaVivo() == false)
            {
                balaGuardia.desactivarConBorrado();
                balaDron.desactivarConBorrado();
                telarana.desactivarConBorrado();

                Console::CursorVisible = true;

                return 1;
            }
            //Victoria
            // Si los 2 enemigos murieron, gana al llegar a la salida.
            if (guardia.estaVivo() == false && dron.estaVivo() == false)
            {
                // Flecha amarilla al centro hasta que escape.
                mostrarMensajeEscape();

                int bordeDerecho = spider.getX() + spider.getAncho();

                // Spider-Man llego a la salida de la derecha.
                if (bordeDerecho >= 103)
                {
                    dialogo("SPIDERMAN:", "Lo logre... por fin consegui escapar.");
                    dialogo("IRON MAN:", "Maldicion... Peter se escapo.");

                    Console::CursorVisible = false;
                    Console::SetCursorPosition(0, ALTO - 1);
                    return 0;
                }
            }
            Sleep(100);
        }
    }
};
