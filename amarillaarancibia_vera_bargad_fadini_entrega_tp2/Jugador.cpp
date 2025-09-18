#include "Jugador.h"

Jugador::Jugador(int startX, int startY)
{
    m_x = startX;
    m_y = startY;

    m_resistencia = 3;
    m_vidas = 3;
    m_derrota = false;
}

///////////////////////////////////////////////////////////////

void Jugador::update()
{
    if (m_resistencia <= 0)
    {
        m_derrota = true;
        m_vidas--;
        m_resistencia = 3;

    }



}


///////////////////////////////////////////////////////////////
void Jugador::draw()
{
if (!m_derrota)

{
    attron(COLOR_PAIR(1));
    mvaddch(m_y, m_x + 2, ACS_ULCORNER);
    mvaddch(m_y, m_x + 3, ACS_HLINE);
    mvaddch(m_y, m_x + 4, ACS_HLINE);
    mvaddch(m_y, m_x + 5, ACS_HLINE);
    mvaddch(m_y, m_x + 6, ACS_URCORNER);

    mvaddch(m_y + 1, m_x + 2, ACS_VLINE);   
    mvaddch(m_y + 1, m_x + 3, ' ');
    mvaddch(m_y + 1, m_x + 4, ' ');
    mvaddch(m_y + 1, m_x + 5, ' ');
    mvaddch(m_y + 1, m_x + 6, ACS_VLINE);

    mvaddch(m_y + 2, m_x + 2, ACS_LLCORNER);
    mvaddch(m_y + 2, m_x + 3, ACS_HLINE);
    mvaddch(m_y + 2, m_x + 4, ACS_HLINE);
    mvaddch(m_y + 2, m_x + 5, ACS_HLINE);
    mvaddch(m_y + 2, m_x + 6, ACS_LRCORNER);
    mvaddch(m_y + 3, m_x + 2, '/');
    mvaddch(m_y + 3, m_x + 3, ' ');
    mvaddch(m_y + 3, m_x + 4, 'A');
    mvaddch(m_y + 3, m_x + 5, ' ');
    mvaddch(m_y + 3, m_x + 6, '\\');

    mvaddch(m_y + 4, m_x + 3, '/');
    mvaddch(m_y + 4, m_x + 4, ' ');
    mvaddch(m_y + 4, m_x + 5, '\\');
    attroff(COLOR_PAIR(1));

}
else{
attron(COLOR_PAIR(2));
mvaddch(m_y, m_x + 2, ACS_ULCORNER);
mvaddch(m_y, m_x + 3, ACS_HLINE);
mvaddch(m_y, m_x + 4, ACS_HLINE);
mvaddch(m_y, m_x + 5, ACS_HLINE);
mvaddch(m_y, m_x + 6, ACS_URCORNER);

mvaddch(m_y + 1, m_x + 2, ACS_VLINE);
mvaddch(m_y + 1, m_x + 3, '\\');
mvaddch(m_y + 1, m_x + 4, ' ');
mvaddch(m_y + 1, m_x + 5, '/'); 
mvaddch(m_y + 1, m_x + 6, ACS_VLINE);

mvaddch(m_y + 2, m_x + 2, ACS_LLCORNER);
mvaddch(m_y + 2, m_x + 3, ACS_HLINE);
mvaddch(m_y + 2, m_x + 4, ACS_HLINE);
mvaddch(m_y + 2, m_x + 5, ACS_HLINE);
mvaddch(m_y + 2, m_x + 6, ACS_LRCORNER);
mvaddch(m_y + 3, m_x + 2, '/');
mvaddch(m_y + 3, m_x + 3, ' ');
mvaddch(m_y + 3, m_x + 4, 'A');
mvaddch(m_y + 3, m_x + 5, ' ');
mvaddch(m_y + 3, m_x + 6, '\\');

mvaddch(m_y + 1, m_x + 3, '\\');
mvaddch(m_y + 1, m_x + 5, '/');

mvaddch(m_y + 4, m_x + 3, '/');
mvaddch(m_y + 4, m_x + 4, ' ');
mvaddch(m_y + 4, m_x + 5, '\\');

refresh();
delay_output(400);

mvaddch(m_y, m_x + 2, ACS_ULCORNER);
mvaddch(m_y, m_x + 3, ACS_HLINE);
mvaddch(m_y, m_x + 4, ACS_HLINE);
mvaddch(m_y, m_x + 5, ACS_HLINE);
mvaddch(m_y, m_x + 6, ACS_URCORNER);
mvaddch(m_y + 1, m_x + 2, ACS_VLINE); 
mvaddch(m_y + 1, m_x + 3, ' ');
mvaddch(m_y + 1, m_x + 4, 'X');
mvaddch(m_y + 1, m_x + 5, ' ');
mvaddch(m_y + 1, m_x + 6, ACS_VLINE);
mvaddch(m_y + 2, m_x + 2, ACS_LLCORNER);
mvaddch(m_y + 2, m_x + 3, ACS_HLINE);
mvaddch(m_y + 2, m_x + 4, ' ');
mvaddch(m_y + 2, m_x + 5, ACS_HLINE);
mvaddch(m_y + 2, m_x + 6, ACS_LRCORNER);
mvaddch(m_y + 3, m_x + 2, '/');
mvaddch(m_y + 3, m_x + 3, '_');
mvaddch(m_y + 3, m_x + 4, ' ');
mvaddch(m_y + 3, m_x + 5, '_');
mvaddch(m_y + 3, m_x + 6, '\\');

attroff(COLOR_PAIR(2));

refresh();
delay_output(400);

m_derrota = false;

}

}

// Modelo de personaje  
//                      ┌───┐
//                      │   │
//                      └───┘
//                      / A \
//                       / \


///////////////////////////

void Jugador::setX(int x) { m_x = x; }
void Jugador::setY(int y) { m_y = y; } 

int Jugador::getX() { return m_x; } 
int Jugador::getY() { return m_y; } 

void Jugador::setResistencia(int resistencia) { m_resistencia = resistencia; }
int Jugador::getResistencia() { return m_resistencia; }

void Jugador::setVidas(int vidas) { m_vidas = vidas; }
int Jugador::getVidas() { return m_vidas; }