#include "pch.h"
#include <iostream>
#include <ctime>
#include "Juego.h"

using namespace System;

int main()
{
    srand((unsigned)time(NULL));
    Juego juego;
    juego.iniciar();
    return 0;
}
