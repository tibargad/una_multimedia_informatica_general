#include "Cascarudo.h"

Cascarudo::Cascarudo(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Cascarudo::update()
{
    m_y = m_y + 1;

    if ( m_y >= 39)
    {
        m_x = rand() % 119 + 1;
        m_y = 1;
    }

}

void Cascarudo::draw()
{
    mvaddch(m_y, m_x + 3, ACS_ULCORNER);
    mvaddch(m_y, m_x + 4, ACS_URCORNER);
    mvaddch(m_y + 1, m_x + 2, ACS_ULCORNER);
    mvaddch(m_y + 1, m_x + 3, ACS_HLINE);
    mvaddch(m_y + 1, m_x + 4, ACS_HLINE);
    mvaddch(m_y + 1, m_x + 5, ACS_URCORNER);
    mvaddch(m_y + 2, m_x + 1, '/');
    mvaddch(m_y + 2, m_x + 2, ACS_VLINE);
    mvaddch(m_y + 2, m_x + 3, ACS_HLINE);
    mvaddch(m_y + 2, m_x + 4, ACS_HLINE);
    mvaddch(m_y + 2, m_x + 5, ACS_VLINE);
    mvaddch(m_y + 2, m_x + 6, '\\');
    mvaddch(m_y + 3, m_x + 2, '\\');
    mvaddch(m_y + 3, m_x + 5, '/');
    mvaddch(m_y + 4, m_x + 3, ACS_LLCORNER);
    mvaddch(m_y + 4, m_x + 4, ACS_LRCORNER);

}

void Cascarudo::colision(Jugador &rJugador)
{
    if (m_x >= rJugador.getX() && m_x <= rJugador.getX() + 6 && m_y >= rJugador.getY() && m_y <= rJugador.getY() + 3 )
    {
        rJugador.setResistencia(rJugador.getResistencia() - 1);
        
        m_x = rand() % 119 + 1;
        m_y = 1;

    }
}

////////////////////////////////////

int Cascarudo::getX() { return m_x; }
int Cascarudo::getY() { return m_y; } // metodos accesor para la colision

