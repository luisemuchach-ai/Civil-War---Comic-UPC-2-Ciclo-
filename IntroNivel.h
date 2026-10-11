#pragma once
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <string>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

using namespace System;
using namespace std;

// ============================================================
// CINEMATICAS: explican cada nivel antes de jugarlo.
// Todas tienen titulo, historia, objetivo y espera de ENTER.
// Juego las invoca con musica y en silencio se juega.
// ============================================================
class IntroNivel
{
private:


    bool narracionActiva = false;

    string obtenerCarpetaExe()
    {
        char ruta[MAX_PATH];
        GetModuleFileNameA(NULL, ruta, MAX_PATH);

        string carpeta = ruta;
        size_t posicion = carpeta.find_last_of("\\/");

        if (posicion != string::npos)
            carpeta = carpeta.substr(0, posicion + 1);

        return carpeta;
    }

    void reproducirNarracion(const string& nombreArchivo)
    {
        mciSendStringA("stop vozIntro", NULL, 0, NULL);
        mciSendStringA("close vozIntro", NULL, 0, NULL);
        narracionActiva = false;

        string rutaAudio = obtenerCarpetaExe() + nombreArchivo;
        string comandoAbrir =
            "open \"" + rutaAudio + "\" type waveaudio alias vozIntro";

        MCIERROR error = mciSendStringA(
            comandoAbrir.c_str(), NULL, 0, NULL);

        if (error != 0)
        {
            char mensaje[256] = "";
            mciGetErrorStringA(error, mensaje, 256);

            string detalle =
                "Archivo:\n" + rutaAudio +
                "\n\nError de Windows:\n" + mensaje;

            MessageBoxA(
                NULL,
                detalle.c_str(),
                "No se pudo abrir la narracion",
                MB_OK
            );
            return;
        }

        error = mciSendStringA("play vozIntro", NULL, 0, NULL);

        if (error != 0)
        {
            char mensaje[256] = "";
            mciGetErrorStringA(error, mensaje, 256);
            MessageBoxA(
                NULL,
                mensaje,
                "No se pudo reproducir la narracion",
                MB_OK
            );
            mciSendStringA("close vozIntro", NULL, 0, NULL);
            return;
        }

        narracionActiva = true;
    }

    bool narracionTermino()
    {
        if (narracionActiva == false)
            return true;

        char modo[32] = "";
        MCIERROR error =
            mciSendStringA("status vozIntro mode", modo, 32, NULL);

        if (error != 0)
        {
            narracionActiva = false;
            return true;
        }

        string estado = modo;

        if (estado == "playing")
            return false;

        mciSendStringA("close vozIntro", NULL, 0, NULL);
        narracionActiva = false;
        return true;
    }

    void detenerNarracion()
    {
        mciSendStringA("stop vozIntro", NULL, 0, NULL);
        mciSendStringA("close vozIntro", NULL, 0, NULL);
        narracionActiva = false;
    }

    void escribirLinea(const string& texto, int x, int y, int velocidad = 28)
    {
        Console::SetCursorPosition(x, y);

        bool rapido = false;

        for (int i = 0; i < (int)texto.length(); i++)
        {
            cout << texto[i];

            if (_kbhit())
            {
                int tecla = _getch();

                if (tecla == 13)
                    rapido = true;
            }

            if (rapido == false)
                Sleep(velocidad);
        }
    }


    void lineaHorizontal(int x, int y, int largo)
    {
        Console::ForegroundColor = ConsoleColor::DarkGray;
        Console::SetCursorPosition(x, y);

        for (int i = 0; i < largo; i++)
            cout << "=";

        Console::ResetColor();
    }

    // Espera a que termine la voz y luego permite iniciar.
    void esperarInicio()
    {
        Console::ForegroundColor = ConsoleColor::DarkGray;
        Console::SetCursorPosition(37, 26);
        cout << "[ NARRACION EN CURSO... ]";

        while (narracionTermino() == false)
            Sleep(30);

        Console::SetCursorPosition(37, 26);
        cout << "                              ";
        Console::SetCursorPosition(37, 26);
        cout << "[ ENTER ]  Comenzar Mision";

        while (_kbhit())
            _getch();

        while (true)
        {
            if (_kbhit())
            {
                int tecla = _getch();
                if (tecla == 13)
                    break;
            }
            Sleep(20);
        }
        Console::ResetColor();
    }


public:

    IntroNivel() {}

    // NIVEL 1 - MISION REBELDE

    void mostrarNivel1()
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::Clear();
        Console::CursorVisible = false;

        lineaHorizontal(26, 4, 68);

        Console::ForegroundColor = ConsoleColor::Yellow;
        escribirLinea("MISION REBELDE", 51, 6, 45);

        Console::ForegroundColor = ConsoleColor::DarkGray;
        escribirLinea("ARCHIVO DE MISION // NIVEL 1", 45, 8, 20);

        Sleep(295);

        reproducirNarracion("redaccion1.wav");

        Console::ForegroundColor = ConsoleColor::White;
        escribirLinea("El conflicto entre los Vengadores ha dividido al equipo.", 20, 12, 90);
        escribirLinea("Tony Stark intenta detener la rebelion antes de que todo empeore.", 20, 14, 90);
        escribirLinea("Spider-Man lo acompana, aunque empieza a dudar de lo que esta haciendo.", 20, 16, 90);
        escribirLinea("Dos rebeldes bloquean el camino.", 20, 18, 90);
        Sleep(300);

        Console::ForegroundColor = ConsoleColor::Red;
        escribirLinea("OBJETIVO: DERROTA A LOS REBELDES.", 20, 21, 35);

        lineaHorizontal(26, 24, 68);
        esperarInicio();
        detenerNarracion();
        Console::Clear();
    }


    // NIVEL 2 - PUNTO DE RUPTURA

    void mostrarNivel2()
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::Clear();
        Console::CursorVisible = false;

        lineaHorizontal(26, 4, 68);

        Console::ForegroundColor = ConsoleColor::Green;

        escribirLinea("PUNTO DE RUPTURA", 49, 6, 45);

        Console::ForegroundColor = ConsoleColor::DarkGray;
        escribirLinea("ARCHIVO DE MISION // NIVEL 2", 45, 8, 20);
        Sleep(300);

        reproducirNarracion("redaccion2.wav");

        Console::ForegroundColor = ConsoleColor::White;
        escribirLinea("El combate termino, pero Peter no puede ignorar lo ocurrido.", 20, 12, 90);
        escribirLinea("De regreso en la Torre Stark, sus dudas se convierten en una decision.", 20, 14, 90);
        escribirLinea("Spider-Man quiere salir... pero la seguridad de Stark se activa.", 20, 16, 90);
        escribirLinea("Un Guardia Stark y un Dron bloquean la ruta de escape.", 20, 18, 90);
        Sleep(300);

        Console::ForegroundColor = ConsoleColor::Cyan;
        escribirLinea("OBJETIVO: ABRETE PASO Y ESCAPA DE LA TORRE.", 20, 21, 35);

        lineaHorizontal(26, 24, 68);
        esperarInicio();
        detenerNarracion();
        Console::Clear();
    }


    // NIVEL 3 - EL PRECIO DE LA VICTORIA
    void mostrarNivel3()
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::Clear();
        Console::CursorVisible = false;

        lineaHorizontal(26, 4, 68);

        Console::ForegroundColor = ConsoleColor::Red;

        escribirLinea("EL PRECIO DE LA VICTORIA", 47, 6, 45);

        Console::ForegroundColor = ConsoleColor::DarkGray;
        escribirLinea("ARCHIVO DE MISION // NIVEL 3", 45, 8, 20);
        Sleep(300);

        reproducirNarracion("redaccion3.wav");

        Console::ForegroundColor = ConsoleColor::White;
        escribirLinea("Peter escapo, pero el conflicto aun no termina.", 20, 12, 110);
        escribirLinea("El Capitan America sale a enfrentar a Tony Stark.", 20, 14, 110);
        escribirLinea("La ciudad esta en ruinas y cada golpe cuenta.", 20, 16, 110);
        escribirLinea("Iron Man es mas fuerte: aguanta 6 golpes.", 20, 18, 110);
        Sleep(300);

        Console::ForegroundColor = ConsoleColor::Blue;
        escribirLinea("OBJETIVO: DERROTA A IRON MAN CON TU ESCUDO.", 20, 21, 35);

        lineaHorizontal(26, 24, 68);
        esperarInicio();
        detenerNarracion();
        Console::Clear();
    }


    // PARTE FINAL - CAPTURA DE CAPITAN AMERICA (automatico, sin controles)

    void mostrarParteFinal()
    {
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::White;
        Console::Clear();
        Console::CursorVisible = false;

        lineaHorizontal(26, 4, 68);

        Console::ForegroundColor = ConsoleColor::Magenta;

        escribirLinea("CAPTURA DE CAPITAN AMERICA", 47, 6, 45);

        Console::ForegroundColor = ConsoleColor::DarkGray;
        escribirLinea("ARCHIVO DE MISION // PARTE FINAL", 45, 8, 20);
        Sleep(300);

        reproducirNarracion("CapturaDeCapi.wav");

        Console::ForegroundColor = ConsoleColor::White;
        escribirLinea("Tony gano, pero nadie celebra la victoria.", 20, 12, 90);
        escribirLinea("El Capitan se entrego para frenar la guerra.", 20, 14, 90);
        escribirLinea("Ahora esta detenido y la historia se cuenta sola.", 20, 16, 90);
        escribirLinea("Mira que paso con el en la escena final.", 20, 18, 90);
        Sleep(300);

        Console::ForegroundColor = ConsoleColor::Yellow;
        escribirLinea("FINAL: MIRA QUE PASO CON EL CAPITAN.", 20, 21, 35);

        lineaHorizontal(26, 24, 68);
        esperarInicio();
        detenerNarracion();
        Console::Clear();
    }
};
