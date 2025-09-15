#pragma once
#include <ncurses.h>

class Jugador
{
public:
    Jugador(int startX, int startY);
    void draw();
    void update();

    void setX(int X);
    void setY(int y); // debe ser distinto para evitar ambigüedades
    int getX();
    int getY();

    void setVidas( int vidas);
    int getVidas();

    void setResistencia(int resistencia);
    int getResistencia();


private:
    int m_x, m_y; // Posicion del jugador. Utilizo M que significa miembro. Practica estandar.
    int m_resistencia;
    int m_vidas;
    bool m_derrota;
};