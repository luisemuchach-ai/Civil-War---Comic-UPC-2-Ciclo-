#pragma once
#include "Escenario.h"
#include <string>

// ============================================================
// CLASE BASE DE PERSONAJES (HERENCIA)
// No hereda de Escenario: GUARDA un puntero al escenario
// para dibujar sobre el MISMO mapa (COMPOSICION).
// Sus hijas (IronMan, SpiderMan, CapitanAmerica, Enemigo)
// cambian como se dibujan y como se mueven (POLIMORFISMO).
// ============================================================
class Personaje
{
protected:
    Escenario* esc;
    int x, y;
    int alto, ancho;
    int vidas;
    bool vivo;
    int frame;

public:
    // Constructor con valores iniciales simples.
    Personaje(Escenario* escenario, int posX, int posY, int altoP, int anchoP) {
        esc = escenario;
        x = posX;
        y = posY;
        alto = altoP;
        ancho = anchoP;
        vidas = 3;
        vivo = true;
        frame = 0;
    }

    virtual ~Personaje() {}

    // Metodo ABSTRACTO: cada hijo se dibuja distinto.
    // (POLIMORFISMO: mismo nombre, distinto dibujo)
    virtual void dibujar() = 0;

    // Borra el dibujo y deja ver el mapa de abajo.
    void borrar() {
        esc->restaurarZona(x, y, ancho, alto);
    }

    // Intenta moverse (dx, dy). Solo se mueve si no hay roca.
    // Devuelve true si se movio.
    bool mover(int dx, int dy) {
        int nuevoX = x + dx;
        int nuevoY = y + dy;
        bool libre = esc->PuedeEstarEn(nuevoX, nuevoY, ancho, alto);
        if (libre == false) {
            return false;
        }
        borrar();
        x = nuevoX;
        y = nuevoY;
        if (frame == 0) { frame = 1; }
        else { frame = 0; }
        dibujar();
        return true;
    }

    // Pierde 1 vida. Con 0 vidas se borra y sale del mapa.
    void recibirDano() {
        if (vivo == false) {
            return;
        }
        vidas = vidas - 1;
        if (vidas <= 0) {
            vidas = 0;
            vivo = false;
            borrar();
            x = -100;
            y = -100;
        }
    }

    // ¿La bala (bx, by) me golpeo?
    bool colisionaConBala(int bx, int by) {
        if (vivo == false) {
            return false;
        }
        return esc->colisionDisparo(x, y, bx, by, alto, ancho);
    }

    // ---- Datos basicos (ENCAPSULAMIENTO: se leen con get) ----
    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }
    int getVidas() { return vidas; }
    bool estaVivo() { return vivo; }

    void setPos(int nuevoX, int nuevoY) {
        x = nuevoX;
        y = nuevoY;
    }

    // Vuelve a la vida en una posicion, con las vidas llenas.
    // Es virtual para que IronMan (jefe con 6 vidas) recupere las suyas.
    virtual void revivir(int nuevoX, int nuevoY) {
        x = nuevoX;
        y = nuevoY;
        vivo = true;
        vidas = 3;
    }
};