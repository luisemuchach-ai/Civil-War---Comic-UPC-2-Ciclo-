#pragma once
#include "Escenario.h"

// ============================================================
// UNICA CLASE DE PROYECTILES: todo lo que vuela es un Disparo.
// - Bala de heroe: "=D" rapida a la derecha (Nivel 1).
// - Bala enemiga: "*" lenta (la de Daredevil es "=-=" y mide 3).
// - Bala dirigida: apunta a un punto (Guardia del Nivel 2).
// - Escudo: circulo de pixeles 6 x 3 que va y vuelve (Nivel 3).
// - Telaraña: red de pixeles 9 x 3 que rebota en negro (Nivel 2).
// El Nivel decide: cuando nace, como se mueve y cuando pega.
// ============================================================
class Disparo
{
private:
    Escenario* esc;

    int x;
    int y;

    int dirX;
    int dirY;

    int velocidad;

    bool deEnemigo;
    bool activa;

    int color;
    bool atraviesaMuros;

    // Si es true, la bala enemiga se dibuja como "=-=" (Daredevil).
    // Si es false, se dibuja como "*" (los demas enemigos).
    bool esDaredevil;

    // Si es true, este Disparo es el ESCUDO del Capitan America.
    // NO es otra clase: es el mismo Disparo configurado como escudo.
    // Se dibuja como circulo con pixeles (rojo/blanco/azul) y mide 6 x 3.
    bool esEscudo;

    // Si es true, este Disparo es la TELARAÑA de Spider-Man.
    // Tampoco es otra clase: es el mismo Disparo configurado como red.
    // Se dibuja como red blanca con pixeles y mide 9 x 3.
    bool esTelaraña;

    // true = ya toco el negro una vez (vale para dañar al Dron).
    bool reboto;

    // Para un disparo dirigido exactamente hacia un punto.
    bool modoObjetivo;

    double posRealX;
    double posRealY;

    double pasoX;
    double pasoY;

    // Sprite del escudo: 6 pixeles de ancho x 6 pixeles de alto
    // = 6 columnas x 3 filas de consola (2 pixeles por celda).
    // 12 = rojo (borde), 9 = azul, 15 = blanco (centro), -1 = vacio.
    static const int Ancho_Escudo = 6;
    static const int Alto_Escudo_Pixeles = 6;
    static const int Alto_Escudo_Consola = 3;

    short spriteEscudo[Alto_Escudo_Pixeles][Ancho_Escudo] =
    {
        {-1, 12, 12, 12, 12, -1},
        {12,  9,  9,  9,  9, 12},
        {12,  9, 15, 15,  9, 12},
        {12,  9, 15, 15,  9, 12},
        {12,  9,  9,  9,  9, 12},
        {-1, 12, 12, 12, 12, -1}
    };

    void dibujarEscudo()
    {
        for (int filaConsola = 0; filaConsola < Alto_Escudo_Consola; filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0; columna < Ancho_Escudo; columna++)
            {
                int colorArriba = spriteEscudo[filaArriba][columna];
                int colorAbajo = spriteEscudo[filaAbajo][columna];

                if (colorArriba == -1 && colorAbajo == -1)
                {
                    continue;
                }

                esc->ponerCeldaPixel(x + columna, y + filaConsola, colorArriba, colorAbajo);
            }
        }
    }


    // Sprite de la telaraña: 9 pixeles de ancho x 6 pixeles de alto
    // = 9 columnas x 3 filas de consola (2 pixeles por celda).
    // 15 = blanco (hilos), -1 = vacio. Igual que el escudo pero en red.
    static const int Ancho_Telarana = 9;
    static const int Alto_Telarana_Pixeles = 6;
    static const int Alto_Telarana_Consola = 3;

    short spriteTelaraña[Alto_Telarana_Pixeles][Ancho_Telarana] =
    {
        {-1, -1, -1, -1, -1, -1, 15, -1, -1},
        {-1, -1, -1, -1, -1, 15, -1, 15, -1},
        {15, -1, -1, -1, 15, -1, 15, -1, 15},
        {-1, 15, 15, 15, -1, 15, 15, 15, 15},
        {15, -1, -1, -1, 15, -1, 15, -1, 15},
        {-1, -1, -1, -1, -1, 15, -1, 15, -1}
    };

    // Dibuja la red con el frente en x (a la derecha si va a la
    // derecha, a la izquierda si va a la izquierda).
    void dibujarTelaraña()
    {
        int inicioY = y - 1;

        for (int filaConsola = 0; filaConsola < Alto_Telarana_Consola; filaConsola++)
        {
            int filaArriba = filaConsola * 2;
            int filaAbajo = filaArriba + 1;

            for (int columna = 0; columna < Ancho_Telarana; columna++)
            {
                int columnaSprite = columna;
                if (dirX < 0)
                {
                    columnaSprite = Ancho_Telarana - 1 - columna;
                }

                int colorArriba = spriteTelaraña[filaArriba][columnaSprite];
                int colorAbajo = spriteTelaraña[filaAbajo][columnaSprite];

                if (colorArriba == -1 && colorAbajo == -1)
                {
                    continue;
                }

                int dibujarX = x - (Ancho_Telarana - 1) + columna;
                if (dirX < 0)
                {
                    dibujarX = x + columna;
                }

                esc->ponerCeldaPixel(dibujarX, inicioY + filaConsola,
                    colorArriba, colorAbajo);
            }
        }
    }


    int anchoDibujo()
    {
        if (esEscudo == true)
            return Ancho_Escudo;

        if (esTelaraña == true)
            return Ancho_Telarana;

        if (esDaredevil == true)
            return 3;

        if (deEnemigo == true)
            return 1;

        return 2;
    }

    int altoDibujo()
    {
        if (esEscudo == true)
            return Alto_Escudo_Consola;

        if (esTelaraña == true)
            return Alto_Telarana_Consola;

        return 1;
    }


public:

    Disparo(Escenario* escenario,
        bool esEnemigo,
        int vel,
        int colorP = 14,
        bool atraviesaMurosP = false,
        bool esDaredevilP = false,
        bool esEscudoP = false,
        bool esTelarañaP = false)
    {
        esc = escenario;

        x = 0;
        y = 0;

        dirX = 1;
        dirY = 0;

        velocidad = vel;

        deEnemigo = esEnemigo;
        activa = false;

        color = colorP;
        atraviesaMuros = atraviesaMurosP;
        esDaredevil = esDaredevilP;
        esEscudo = esEscudoP;
        esTelaraña = esTelarañaP;
        reboto = false;

        modoObjetivo = false;

        posRealX = 0;
        posRealY = 0;

        pasoX = 0;
        pasoY = 0;
    }


    ~Disparo()
    {
    }


    bool estaActiva()
    {
        return activa;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    int getVelocidad()
    {
        return velocidad;
    }

    // ¿Esta bala es la de Daredevil ("=-=")?
    bool esDisparoDaredevil()
    {
        return esDaredevil;
    }

    // ¿Ya toco el negro una vez? (vale para dañar al Dron).
    bool yaReboto()
    {
        return reboto;
    }

    // Marca que toco el negro (la llama el Nivel, no se marca sola).
    void marcarRebote()
    {
        reboto = true;
    }

    // Voltea la direccion al chocar con negro (y cuenta como rebote,
    // igual que antes hacia la clase Telarana).
    void rebotarHorizontal()
    {
        dirX = -dirX;
        reboto = true;
    }

    void rebotarVertical()
    {
        dirY = -dirY;
        reboto = true;
    }

    int getDirX()
    {
        return dirX;
    }

    int getDirY()
    {
        return dirY;
    }

    // Avanza sin revisar nada (el Nivel ya reviso mapa y roca antes).
    // Solo para vuelo recto (telaraña); el resto usa avanzarUnPaso().
    void avanzar()
    {
        x = x + dirX;
        y = y + dirY;
    }

    // Ancho y alto que ocupa en pantalla (el escudo ocupa 6 x 3).
    int getAncho()
    {
        return anchoDibujo();
    }

    int getAlto()
    {
        return altoDibujo();
    }

    // Invierte la direccion horizontal (para el regreso bumeran del escudo).
    void invertirDireccion()
    {
        dirX = -dirX;

        if (modoObjetivo == true)
        {
            pasoX = -pasoX;
        }
    }

    //Disparo Horizontal

    void disparar(int inicioX, int inicioY, int direccion)
    {
        x = inicioX;
        y = inicioY;

        dirX = direccion;
        dirY = 0;

        modoObjetivo = false;
        activa = true;
        reboto = false;

        dibujar();
    }


    //Disparo Vertical

    void dispararVertical(int inicioX, int inicioY, int direccionY)
    {
        x = inicioX;
        y = inicioY;

        dirX = 0;
        dirY = direccionY;

        modoObjetivo = false;
        activa = true;
        reboto = false;

        dibujar();
    }


    //  DIRECCIONES (la usa la telaraña: sale en diagonal).
    void dispararDireccion(int inicioX,
        int inicioY,
        int direccionX,
        int direccionY)
    {
        x = inicioX;
        y = inicioY;

        dirX = direccionX;
        dirY = direccionY;

        modoObjetivo = false;
        activa = true;
        reboto = false;

        dibujar();
    }


    void dispararHacia(int inicioX,
        int inicioY,
        int objetivoX,
        int objetivoY)
    {
        x = inicioX;
        y = inicioY;

        posRealX = inicioX;
        posRealY = inicioY;

        int diferenciaX = objetivoX - inicioX;
        int diferenciaY = objetivoY - inicioY;

        int absX;

        if (diferenciaX < 0)
            absX = -diferenciaX;
        else
            absX = diferenciaX;

        int absY;

        if (diferenciaY < 0)
            absY = -diferenciaY;
        else
            absY = diferenciaY;

        int distancia;

        if (absX > absY)
            distancia = absX;
        else
            distancia = absY;

        if (distancia == 0)
            distancia = 1;

        pasoX = (double)diferenciaX / distancia;
        pasoY = (double)diferenciaY / distancia;

        modoObjetivo = true;
        activa = true;
        reboto = false;

        dibujar();
    }


    void desactivar()
    {
        activa = false;
        reboto = false;
    }


    void desactivarConBorrado()
    {
        if (activa == true)
            borrar();

        activa = false;
    }


    void borrar()
    {
        if (esTelaraña == true)
        {
            // La red se dibuja hacia atras del frente (x):
            // se borra en ese mismo origen (restaurarZona ignora
            // lo que caiga fuera de pantalla).
            int bx = x;
            if (dirX >= 0)
            {
                bx = x - (Ancho_Telarana - 1);
            }
            esc->restaurarZona(bx, y - 1, Ancho_Telarana,
                Alto_Telarana_Consola);
            return;
        }

        if (x >= 0 && x < ANCHO &&
            y >= 0 && y < ALTO)
        {
            esc->restaurarZona(
                x,
                y,
                anchoDibujo(),
                altoDibujo()
            );
        }
    }


    void dibujar()
    {
        if (activa == false)
            return;

        if (esEscudo == true)
        {
            dibujarEscudo();
            return;
        }

        if (esTelaraña == true)
        {
            dibujarTelaraña();
            return;
        }

        if (deEnemigo == true)
        {
            if (esDaredevil == true)
            {
                // Bala de Daredevil: ocupa 3 casillas ("=-=").
                // Los "=" van en negro (0) y el "-" del centro en gris (7).
                esc->ponerCaracter(x, y, '=', 0);
                esc->ponerCaracter(x + 1, y, '-', 7);
                esc->ponerCaracter(x + 2, y, '=', 0);
            }
            else
            {
                // Bala enemiga normal ("*") con el color recibido.
                esc->ponerCaracter(x, y, '*', color);
            }
        }
        else
        {
            esc->ponerCaracter(x, y, '=', color);
            esc->ponerCaracter(x + 1, y, 'D', color);
        }
    }


    bool avanzarUnPaso()
    {
        if (activa == false)
            return false;

        int siguienteX;
        int siguienteY;


        // --------------------------------------------------------
        // DISPARO APUNTADO
        // --------------------------------------------------------
        if (modoObjetivo == true)
        {
            posRealX = posRealX + pasoX;
            posRealY = posRealY + pasoY;

            // Las posiciones del mapa son positivas.
            siguienteX = (int)(posRealX + 0.5);
            siguienteY = (int)(posRealY + 0.5);
        }


        else
        {
            siguienteX = x + dirX;
            siguienteY = y + dirY;
        }


        if (esEscudo == true)
        {
            // El escudo ocupa 6 x 3. Solo muere cuando sale todo.
            if (siguienteX + Ancho_Escudo - 1 < 0 || siguienteX >= ANCHO ||
                siguienteY < 0 || siguienteY + Alto_Escudo_Consola - 1 >= ALTO)
            {
                activa = false;
                return false;
            }
        }
        else if (esDaredevil == true)
        {
            // La bala ocupa x, x+1 y x+2. Solo muere cuando sale toda.
            if (siguienteX + 2 < 0 || siguienteX >= ANCHO ||
                siguienteY < 0 || siguienteY >= ALTO)
            {
                activa = false;
                return false;
            }
        }
        else
        {
            if (siguienteX < 0 || siguienteX >= ANCHO ||
                siguienteY < 0 || siguienteY >= ALTO)
            {
                activa = false;
                return false;
            }
        }


        if (atraviesaMuros == false)
        {
            if (esEscudo == true)
            {
                // Revisa todo el rectangulo 6 x 3 del escudo.
                for (int fila = 0; fila < Alto_Escudo_Consola; fila++)
                {
                    for (int col = 0; col < Ancho_Escudo; col++)
                    {
                        if (esc->BalaChocaMuro(siguienteX + col, siguienteY + fila) == true)
                        {
                            activa = false;
                            return false;
                        }
                    }
                }
            }
            else if (deEnemigo == false)
            {
                bool choca1 =
                    esc->BalaChocaMuro(siguienteX, siguienteY);

                bool choca2 =
                    esc->BalaChocaMuro(siguienteX + 1, siguienteY);

                if (choca1 == true || choca2 == true)
                {
                    activa = false;
                    return false;
                }
            }
            else if (esDaredevil == true)
            {
                // Revisa las 3 casillas del "=-=".
                bool choca1 = esc->BalaChocaMuro(siguienteX, siguienteY);
                bool choca2 = esc->BalaChocaMuro(siguienteX + 1, siguienteY);
                bool choca3 = esc->BalaChocaMuro(siguienteX + 2, siguienteY);

                if (choca1 == true || choca2 == true || choca3 == true)
                {
                    activa = false;
                    return false;
                }
            }
            else
            {
                if (esc->BalaChocaMuro(
                    siguienteX,
                    siguienteY) == true)
                {
                    activa = false;
                    return false;
                }
            }
        }


        x = siguienteX;
        y = siguienteY;

        return true;
    }
};
