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

    void setDisparos ( int disparos);
    int getDisparos();

    void setResistencia(int resistencia);
    int getResistencia();


private:
    int m_x, m_y; // Posicion del jugador. Utilizo M que significa miembro. Practica estandar.
    int m_resistencia;
    int m_disparos;
    bool m_derrota;
};