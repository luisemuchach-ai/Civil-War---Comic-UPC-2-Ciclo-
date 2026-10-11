#pragma once
#include "Escenario.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

using namespace System;
using namespace std;

// ============================================================
// PANTALLAS CON OPCIONES: menu principal y seleccion de mision.
// - Dibuja titulos en pixel-art, lista estados (COMPLETO /
//   DESBLOQUEADO / BLOQUEADO) y lee W/A/S/D, flechas y ENTER.
// - Tambien guarda la musica del menu (MCI: abre, pausa y continua).
// ============================================================
class Menu : public Escenario
{
private:

    short fondo[30][120] = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15, 0, 12, 12, 12, 12, 12, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 12, 12, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 12, 12, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 0, 12, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 15, 0, 12, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 15, 15, 0, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 0, 0, 12, 12, 0, 12, 12, 12, 0, 0, 12, 12, 12, 0, 12, 12, 0, 12, 12, 0, 0, 0, 0, 0, 0, 12, 12, 12, 0, 0, 0, 0, 12, 12, 12, 0, 0, 0, 12, 12, 12, 0, 0, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 0, 12, 12, 12, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 9, 12, 12, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 0, 0, 0, 9, 12, 12, 12, 0, 9, 12, 12, 12, 12, 12, 9, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 0, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 9, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 0, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 9, 12, 12, 9, 12, 12, 9, 9, 9, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 9, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 0, 12, 0, 9, 12, 12, 12, 9, 12, 12, 0, 9, 12, 12, 9, 12, 12, 0, 9, 9, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 0, 9, 0, 0, 0, 9, 12, 12, 9, 12, 12, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 12, 9, 12, 12, 0, 9, 12, 12, 9, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 9, 12, 12, 12, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 9, 12, 12, 9, 12, 12, 12, 9, 12, 12, 12, 12, 12, 12, 9, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 0, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 12, 12, 12, 12, 9, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 9, 9, 9, 9, 9, 15, 15, 15, 9, 9, 0, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 0, 0, 0, 12, 12, 9, 12, 12, 9, 9, 12, 12, 12, 12, 12, 12, 9, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 9, 9, 12, 12, 9, 12, 12, 9, 12, 12, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 0, 0, 12, 12, 12, 9, 12, 12, 9, 9, 12, 12, 12, 12, 12, 0, 9, 9, 12, 12, 9, 12, 12, 0, 0, 0, 0, 0, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 9, 9, 12, 12, 9, 12, 12, 9, 9, 12, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 9, 9, 15, 9, 15, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 0, 9, 9, 12, 12, 12, 12, 0, 9, 9, 12, 12, 9, 12, 12, 12, 12, 12, 12, 0, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 12, 12, 0, 9, 12, 12, 9, 12, 12, 0, 9, 9, 12, 12, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 15, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 9, 12, 12, 12, 12, 12, 12, 0, 9, 12, 12, 0, 0, 9, 12, 12, 12, 12, 0, 9, 9, 12, 12, 9, 12, 12, 12, 12, 12, 12, 0, 9, 9, 9, 12, 12, 9, 9, 12, 12, 0, 9, 9, 12, 12, 0, 9, 12, 12, 9, 12, 12, 0, 9, 9, 12, 12, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 15, 15, 9, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 15, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 0, 0, 0, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 0, 0, 0, 0, 9, 9, 0, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 9, 9, 0, 9, 9, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 15, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 15, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 0, 0, 0, 0, 0, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 9, 0, 15, 15, 15, 15, 15, 15, 15, 15, 12, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 15, 15, 15, 9, 9, 9, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 15, 15, 12, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 0, 0, 0, 15, 15, 15, 9, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 12, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 15, 15, 0, 15, 15, 15, 15, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 15, 15, 15, 15, 0, 12, 12, 12, 15, 15, 15, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 12, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };



    // Titulos  PIXEL-ART
    static const int ALTO_TITULO = 5;
    static const int ANCHO_TITULO = 116;

    short tituloMisionRebelde[ALTO_TITULO][ANCHO_TITULO] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    short tituloPuntoRuptura[ALTO_TITULO][ANCHO_TITULO] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,1,1,0,0,1,1,1,1,0,1,0,0,1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,0,0,1,0,1,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    short tituloPrecioVictoria[ALTO_TITULO][ANCHO_TITULO] = {
        {1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,0,0},
        {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0},
        {1,1,1,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0},
        {1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,0,0,1,0},
        {1,1,1,1,0,1,1,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,1,0,1,0,0,1,0},
    };


    bool musicaMenuActiva = false;
    bool musicaMenuPausada = false;


    // Obtiene automaticamente la carpeta donde esta el .exe
    string obtenerCarpetaExe()
    {
        char ruta[MAX_PATH];

        GetModuleFileNameA(NULL, ruta, MAX_PATH);

        string carpeta = ruta;
        size_t posicion = carpeta.find_last_of("\\/");

        if (posicion != string::npos)
        {
            carpeta = carpeta.substr(0, posicion + 1);
        }
        return carpeta;
    }


    // MUSICA DEL MENU (con MCI para poder pausarla y continuarla
    // donde quedo; PlaySound no puede continuar desde un punto).
    // - Primera vez: abre el wav y lo toca en loop.
    // - Siguientes veces: continua desde donde se pauso.
    void iniciarMusicaMenu()
    {
        if (musicaMenuActiva == true && musicaMenuPausada == false)
            return;

        if (musicaMenuActiva == false)
        {
            string rutaMusica = obtenerCarpetaExe() + "menu_music.wav";
            string ordenAbrir = "open \"" + rutaMusica + "\" alias musicaMenu";

            if (mciSendStringA(ordenAbrir.c_str(), NULL, 0, NULL) != 0)
            {
                // Avisa UNA sola vez si Windows no encuentra el archivo,
                // para no abrir una ventana en cada visita al menu.
                static bool yaAviso = false;
                if (yaAviso == false)
                {
                    yaAviso = true;
                    MessageBoxA(NULL, rutaMusica.c_str(), "No se pudo reproducir menu_music.wav", MB_OK);
                }
                return;
            }

            // Toca en loop manual: este driver MCI no acepta "repeat"
            // (da error 259), asi que se repite con repetirMusicaSiTermino().
            mciSendStringA("play musicaMenu", NULL, 0, NULL);
            musicaMenuActiva = true;
            musicaMenuPausada = false;
            return;
        }

        // Ya estaba abierta y pausada: continua donde quedo.
        mciSendStringA("resume musicaMenu", NULL, 0, NULL);
        musicaMenuPausada = false;
    }

    // Si la musica termino, la toca de nuevo (loop manual).
    // Se llama mientras se espera tecla para que sea continua.
    void repetirMusicaSiTermino()
    {
        if (musicaMenuActiva == false)
            return;

        if (musicaMenuPausada == true)
            return;

        char modo[32] = "";
        if (mciSendStringA("status musicaMenu mode", modo, 32, NULL) != 0)
            return;

        string texto = modo;
        if (texto != "playing")
        {
            mciSendStringA("play musicaMenu", NULL, 0, NULL);
        }
    }


    // Pausa la musica SIN cerrar: guarda la posicion para continuar
    // donde quedo cuando se vuelva al menu.
    void pararMusicaMenu()
    {
        if (musicaMenuActiva == false)
            return;

        if (musicaMenuPausada == true)
            return;

        mciSendStringA("pause musicaMenu", NULL, 0, NULL);
        musicaMenuPausada = true;
    }


    // ========================================================
    // LEE WASD Y FLECHAS
    // ========================================================

    int leerTeclaMenu()
    {
        int tecla = _getch();

        // Flechas del teclado.
        if (tecla == 0 || tecla == 224)
        {
            int especial = _getch();

            if (especial == 72) return 'w'; // arriba
            if (especial == 80) return 's'; // abajo
            if (especial == 75) return 'a'; // izquierda
            if (especial == 77) return 'd'; // derecha
        }

        return tecla;
    }


    // Espera una tecla SIN bloquear la musica (la repite si termino).
    int esperarTeclaMenu()
    {
        while (_kbhit() == false)
        {
            repetirMusicaSiTermino();
            Sleep(50);
        }

        return leerTeclaMenu();
    }


    // ========================================================
    // LIMPIAR UNA ZONA SIN CAMBIAR EL TAMANO DE LA CONSOLA
    // ========================================================

    void limpiarZonaMenu(int x, int y, int ancho, int alto)
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;

        for (int f = y; f < y + alto; f++)
        {
            if (f < 0 || f >= 30)
                continue;

            Console::SetCursorPosition(x, f);

            for (int c = 0; c < ancho; c++)
            {
                if (x + c >= 120)
                    break;

                cout << " ";
            }
        }
    }


    void dibujarTitulo(
        short matriz[ALTO_TITULO][ANCHO_TITULO],
        int inicioX,
        int inicioY,
        ConsoleColor superior,
        ConsoleColor inferior,
        ConsoleColor sombra)
    {
        // =========================
        // 1. SOMBRA 3D
        // =========================
        // Se dibuja corrida 1 a la derecha y 1 hacia abajo.
        // Eso da profundidad sin ensuciar el texto.
        for (int f = 0; f < ALTO_TITULO; f++)
        {
            for (int c = 0; c < ANCHO_TITULO; c++)
            {
                if (matriz[f][c] != 1)
                    continue;

                int px = inicioX + c + 1;
                int py = inicioY + f + 1;

                if (px < 0 || px >= 120 || py < 0 || py >= 30)
                    continue;

                Console::SetCursorPosition(px, py);
                Console::ForegroundColor = sombra;
                Console::BackgroundColor = ConsoleColor::Black;
                cout << (char)219;
            }
        }

        // 2. TITULO PRINCIPAL

        for (int f = 0; f < ALTO_TITULO; f++)
        {
            for (int c = 0; c < ANCHO_TITULO; c++)
            {
                int px = inicioX + c;
                int py = inicioY + f;

                if (px < 0 || px >= 120 || py < 0 || py >= 30)
                    continue;

                Console::SetCursorPosition(px, py);

                if (matriz[f][c] != 1)
                {
                    cout << " ";
                    continue;
                }

                bool bordeSuperior = (f == 0 || matriz[f - 1][c] == 0);
                bool bordeIzquierdo = (c == 0 || matriz[f][c - 1] == 0);

                // Brillo en bordes superiores/izquierdos
                if (bordeSuperior || bordeIzquierdo)
                {
                    Console::ForegroundColor = ConsoleColor::White;
                }
                else if (f <= 1)
                {
                    Console::ForegroundColor = superior;
                }
                else
                {
                    Console::ForegroundColor = inferior;
                }

                Console::BackgroundColor = ConsoleColor::Black;
                cout << (char)219;
            }
        }

        Console::ResetColor();
    }


    // LISTA DE NIVELES
    // Cada nivel muestra su estado:
    // COMPLETO (verde) = ya lo terminaste,
    // DESBLOQUEADO (amarillo) = lo puedes jugar pero no lo has terminado,
    // BLOQUEADO (rojo) = todavia no llegas (gana el anterior).
    void dibujarListaNiveles(
        int seleccion,
        bool nivel1Hecho,
        bool nivel2Hecho,
        bool nivel3Hecho)
    {
        limpiarZonaMenu(0, 0, 120, 8);

        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;

        Console::SetCursorPosition(3, 1);
        cout << "================ SELECCION DE MISION ================";

        for (int i = 1; i <= 3; i++)
        {
            int y = 2 + i;

            Console::SetCursorPosition(4, y);

            if (i == seleccion)
            {
                Console::ForegroundColor = ConsoleColor::Yellow;
                cout << ">> ";
            }
            else
            {
                Console::ForegroundColor = ConsoleColor::DarkGray;
                cout << "   ";
            }

            Console::ForegroundColor = ConsoleColor::White;
            cout << "NIVEL " << i << "  ";

            bool completado = false;
            bool desbloqueado = false;

            if (i == 1)
            {
                completado = nivel1Hecho;
                desbloqueado = true;
            }
            else if (i == 2)
            {
                completado = nivel2Hecho;
                desbloqueado = nivel1Hecho;
            }
            else if (i == 3)
            {
                completado = nivel3Hecho;
                desbloqueado = nivel2Hecho;
            }

            if (completado == true)
            {
                Console::ForegroundColor = ConsoleColor::Green;
                cout << "[ COMPLETO ]";
            }
            else if (desbloqueado == true)
            {
                Console::ForegroundColor = ConsoleColor::Yellow;
                cout << "[ DESBLOQUEADO ]";
            }
            else
            {
                Console::ForegroundColor = ConsoleColor::Red;
                cout << "[ BLOQUEADO ]";
            }
        }

        Console::ResetColor();
    }


    // INFORMACION + TITULO DEL NIVEL SELECCIONADO

    void mostrarFichaNivel(
        int nivel,
        bool nivel1Hecho,
        bool nivel2Hecho,
        bool nivel3Hecho)
    {

        limpiarZonaMenu(0, 8, 120, 21);

        bool bloqueado = false;
        bool completado = false;

        if (nivel == 1)
        {
            bloqueado = false;
            completado = nivel1Hecho;
        }

        if (nivel == 2)
        {
            bloqueado = (nivel1Hecho == false);
            completado = nivel2Hecho;
        }

        if (nivel == 3)
        {
            bloqueado = (nivel2Hecho == false);
            completado = nivel3Hecho;
        }


        // ---------------- NIVEL 1 ----------------
        if (nivel == 1)
        {
            dibujarTitulo(
                tituloMisionRebelde,
                2,
                9,
                ConsoleColor::Yellow,
                ConsoleColor::Red,
                ConsoleColor::Blue
            );

            Console::ForegroundColor = ConsoleColor::White;
            Console::BackgroundColor = ConsoleColor::Black;

            Console::SetCursorPosition(8, 17);
            cout << "MISION REBELDE";

            Console::SetCursorPosition(8, 19);
            cout << "OBJETIVO: Derrota a los dos enemigos rebeldes.";

            Console::SetCursorPosition(8, 21);
            cout << "A / D : Mover    W / S : Volar    ESPACIO : Disparar";

            Console::SetCursorPosition(8, 23);
            cout << "Evita los disparos enemigos y completa el combate.";
        }


        // ---------------- NIVEL 2 ----------------
        else if (nivel == 2)
        {
            dibujarTitulo(
                tituloPuntoRuptura,
                2,
                9,
                ConsoleColor::Green,
                ConsoleColor::DarkGreen,
                ConsoleColor::Magenta
            );

            Console::ForegroundColor = ConsoleColor::White;
            Console::BackgroundColor = ConsoleColor::Black;

            Console::SetCursorPosition(8, 17);
            cout << "PUNTO DE RUPTURA";

            Console::SetCursorPosition(8, 19);
            cout << "OBJETIVO: Destruye al Guardia Stark y al Dron.";

            Console::SetCursorPosition(8, 21);
            cout << "A / D : Mover    W / S : Subir/Bajar    ESPACIO : SpiderWeb";

            Console::SetCursorPosition(8, 23);
            cout << "El SpiderWeb debe tocar el contorno negro antes de danar al Dron.";
        }


        // ---------------- NIVEL 3 ----------------
        else
        {
            dibujarTitulo(
                tituloPrecioVictoria,
                2,
                9,
                ConsoleColor::White,
                ConsoleColor::DarkMagenta,
                ConsoleColor::Magenta
            );

            Console::ForegroundColor = ConsoleColor::White;
            Console::BackgroundColor = ConsoleColor::Black;

            Console::SetCursorPosition(8, 17);
            cout << "EL PRECIO DE LA VICTORIA";

            Console::SetCursorPosition(8, 19);
            cout << "OBJETIVO: Derrota a Iron Man con el escudo.";

            Console::SetCursorPosition(8, 21);
            cout << "A / D : Mover    W / S : Volar    ESPACIO : Lanzar escudo";

            Console::SetCursorPosition(8, 23);
            cout << "El escudo bloquea disparos, hace bumeran y Iron Man aguanta 6 golpes.";
        }


        if (bloqueado)
        {


            Console::SetCursorPosition(8, 25);
            cout << "BLOQUEADO: completa el nivel anterior para acceder.";
        }
        else if (completado)
        {
            Console::ForegroundColor = ConsoleColor::Green;
            Console::BackgroundColor = ConsoleColor::Black;

            Console::SetCursorPosition(8, 25);
            cout << "COMPLETO: ya lo terminaste.";
        }
        else
        {
            Console::ForegroundColor = ConsoleColor::Green;
            Console::BackgroundColor = ConsoleColor::Black;

            Console::SetCursorPosition(8, 25);
            cout << "ENTER: iniciar este nivel.";
        }

        Console::ForegroundColor = ConsoleColor::DarkGray;
        Console::SetCursorPosition(8, 27);
        cout << "W = anterior    S = siguiente    ENTER = seleccionar    ESC = volver";

        Console::ResetColor();
    }


public:

    Menu() {}

    // Se puede llamar desde Juego.h antes de cerrar el programa.
    void detenerMusica()
    {
        pararMusicaMenu();
    }

    // Se puede llamar desde Juego.h para la explicacion de cada nivel:
    // con musica se explica, en el juego hay silencio.
    void iniciarMusica()
    {
        iniciarMusicaMenu();
    }


    void CargarEscenario() override
    {
        CargarMapa(fondo);
    }


    bool EsSolido(int x, int y) override
    {
        return false;
    }

    // Muestra opciones y devuelve la elegida (1 a n).
    int mostrar(const char* opciones[], int n)
    {
        iniciarMusicaMenu();

        Console::ResetColor();
        Console::CursorVisible = false;

        try
        {
            Console::SetWindowSize(120, 30);
            Console::SetBufferSize(120, 30);
        }
        catch (...)
        {
            // En algunas PCs de laboratorio Windows no permite
            // cambiar el tamano. El menu igual continua.
        }

        system("cls");

        CargarEscenario();
        DibujarMapa();

        int opcionSeleccionada = 1;

        while (true)
        {
            Console::BackgroundColor = ConsoleColor::Black;

            for (int i = 0; i < n; i++)
            {
                Console::SetCursorPosition(22, 22 + i);
                cout << "      ";

                Console::SetCursorPosition(29, 22 + i);

                if (i + 1 == opcionSeleccionada)
                {
                    Console::ForegroundColor = ConsoleColor::Yellow;
                    cout << ">> " << i + 1 << ") " << opciones[i] << "       ";
                }
                else
                {
                    Console::ForegroundColor = ConsoleColor::White;
                    cout << "   " << i + 1 << ") " << opciones[i] << "       ";
                }
            }

            Console::ForegroundColor = ConsoleColor::DarkGray;
            Console::SetCursorPosition(24, 28);
            cout << "W : Subir     S : Bajar     ENTER : Seleccionar";

            int tecla = esperarTeclaMenu();

            if (tecla == 'w' || tecla == 'W')
            {
                opcionSeleccionada--;

                if (opcionSeleccionada < 1)
                    opcionSeleccionada = n;
            }

            else if (tecla == 's' || tecla == 'S')
            {
                opcionSeleccionada++;

                if (opcionSeleccionada > n)
                    opcionSeleccionada = 1;
            }

            else if (tecla == 13)
            {
                Console::ResetColor();
                return opcionSeleccionada;
            }
        }
    }

    int seleccionarNivel(
        bool nivel1Hecho = false,
        bool nivel2Hecho = false,
        bool nivel3Hecho = false)
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::Clear();
        Console::CursorVisible = false;

        int seleccion = 1;

        while (true)
        {
            dibujarListaNiveles(
                seleccion,
                nivel1Hecho,
                nivel2Hecho,
                nivel3Hecho
            );

            mostrarFichaNivel(
                seleccion,
                nivel1Hecho,
                nivel2Hecho,
                nivel3Hecho
            );

            int tecla = esperarTeclaMenu();

            // W = anterior (W es para subir)
            if (tecla == 'w' || tecla == 'W')
            {
                seleccion--;

                if (seleccion < 1)
                    seleccion = 3;
            }

            // S = siguiente (S es para bajar)
            else if (tecla == 's' || tecla == 'S')
            {
                seleccion++;

                if (seleccion > 3)
                    seleccion = 1;
            }

            // ESC = regresar al menu principal
            else if (tecla == 27)
            {
                Console::ResetColor();
                return 0;
            }

            // ENTER
            else if (tecla == 13)
            {
                bool desbloqueado = false;
                bool completado = false;

                if (seleccion == 1)
                {
                    desbloqueado = true;
                    completado = nivel1Hecho;
                }

                else if (seleccion == 2)
                {
                    desbloqueado = nivel1Hecho;
                    completado = nivel2Hecho;
                }

                else if (seleccion == 3)
                {
                    desbloqueado = nivel2Hecho;
                    completado = nivel3Hecho;
                }


                // COMPLETO: igual que bloqueado, no deja entrar
                // pero porque ya lo termino. Espera una tecla.
                if (completado == true)
                {
                    Console::Beep(600, 100);

                    Console::ForegroundColor = ConsoleColor::Red;
                    Console::BackgroundColor = ConsoleColor::Black;
                    Console::SetCursorPosition(8, 26);
                    cout << "NO PUEDES ENTRAR: ya terminaste este nivel.                  ";

                    while (_kbhit() == false)
                    {
                        Sleep(20);
                    }
                    _getch();
                }

                else if (desbloqueado == true)
                {
                    pararMusicaMenu();

                    Console::ResetColor();
                    return seleccion;
                }

                else
                {
                    Console::Beep(600, 100);

                    Console::ForegroundColor = ConsoleColor::Red;
                    Console::BackgroundColor = ConsoleColor::Black;
                    Console::SetCursorPosition(8, 26);
                    cout << "NO PUEDES ENTRAR: el nivel sigue bloqueado.                  ";

                    // Espera una tecla para que el mensaje no se borre al instante.
                    while (_kbhit() == false)
                    {
                        Sleep(20);
                    }
                    _getch();
                }
            }
        }
    }


};
