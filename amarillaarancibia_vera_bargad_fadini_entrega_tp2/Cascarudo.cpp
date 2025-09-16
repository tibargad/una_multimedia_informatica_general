#include "Cascarudo.h"

Cascarudo::Cascarudo(int x, int y)
{
    m_x = x;
    m_y = y;
    m_timer = 0;
}

const int VELOCIDAD_CASCARUDO = 2; // Control de velocidad cascarudo

void Cascarudo::update()
{
    m_timer++; 


    if (m_timer > VELOCIDAD_CASCARUDO)
    {
        m_timer = 0;

        m_y++;

        
        if (m_y >= 40 - 5) 
        {
            m_x = (rand() % (120 - 7)) + 1;
            m_y = 1;
        }
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
int Cascarudo::getY() { return m_y; }
void Cascarudo::setX(int x) { m_x = x; }
void Cascarudo::setY(int y) { m_y = y; }
