#pragma once
#include <iostream>
#include <ncurses.h>
#include "Jugador.h"

using namespace std;

class Cascarudo
{
public:
    Cascarudo( int x, int y);
    void update();
    void draw();

    void colision( Jugador &rJugador );

    void setX(int x);
    void setY(int y);
    int getX();
    int getY();


private:
    float m_x, m_y;

};