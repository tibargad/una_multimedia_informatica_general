#include "Proyectil.h"

Proyectil::Proyectil(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Proyectil::update()
{
    if ( m_y >= 1) m_y--;
}

void Proyectil::draw()
{
    mvaddch(m_y,m_x, '*'); // en Ncurses las coordenadas van al revés

}