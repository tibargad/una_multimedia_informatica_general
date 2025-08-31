#pragma once
#include <ncurses.h>

class Jugador
{
public:
    void setup();
    void draw();

    void setX(int X);
    void setY(int y); // debe ser distinto para evitar ambigüedades
    int getX();
    int getY();

private:
    int m_x, m_y; // Posicion del jugador. Utilizo M que significa miembro. Practica estandar.

};