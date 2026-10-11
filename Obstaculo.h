#pragma once

// ============================================================
// CLASE OBSTACULO (ROCAS)
// Igual que Personaje: guarda su propio x, y, alto y ancho.
// Nivel1 tiene 2 objetos (roca1 y roca2) y todo se lee con get.
// Asi no hay const ROCA1_X... sueltos en el codigo.
// ============================================================
class Obstaculo
{
protected:
    int x;        // columna donde empieza
    int y;        // fila donde empieza
    int alto;     // filas que ocupa
    int ancho;    // columnas que ocupa

public:
    // Mismo orden que Personaje: posX, posY, alto, ancho.
    Obstaculo(int posX, int posY, int altoO, int anchoO) {
        x = posX;
        y = posY;
        alto = altoO;
        ancho = anchoO;
    }

    ~Obstaculo() {}

    // ¿El punto (px, py) esta dentro de la roca?
    bool contiene(int px, int py) {
        if (px >= x && px < x + ancho && py >= y && py < y + alto) return true;
        return false;
    }

    // ¿El punto (px, py) esta pegado a la roca (1 de borde)?
    // Se usa para el borde negro que tambien bloquea.
    bool estaCerca(int px, int py) {
        if (px >= x - 1 && px < x + ancho + 1 && py >= y - 1 && py < y + alto + 1) return true;
        return false;
    }

    // ---- Datos basicos (ENCAPSULAMIENTO: se leen con get) ----
    int getX() { return x; }
    int getY() { return y; }
    int getAncho() { return ancho; }
    int getAlto() { return alto; }
};
