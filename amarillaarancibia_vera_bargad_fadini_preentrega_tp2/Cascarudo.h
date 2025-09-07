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


private:
    float m_x, m_y;

};