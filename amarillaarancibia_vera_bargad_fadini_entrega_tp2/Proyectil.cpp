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

bool Proyectil::colision(Cascarudo &rCascarudo)
{
    if (m_x >= rCascarudo.getX() && m_x <= rCascarudo.getX() + 6 && m_y >= rCascarudo.getY() && m_y <= rCascarudo.getY() + 4)
    {
        return true;
    }
    return false;
}

bool Proyectil::limite()
{
    if (m_y < 1) return true; // Si es verdadero se ejecuta
    return false; // si es falso se ejecuta. O sea se ejecuta un solo return.

}

int Proyectil::getX() { return m_x; }
int Proyectil::getY() { return m_y; }