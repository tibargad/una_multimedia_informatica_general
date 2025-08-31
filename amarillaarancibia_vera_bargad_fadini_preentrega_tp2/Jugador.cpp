#include "Jugador.h"

void Jugador::setup()
{
    m_x = 60;
    m_y = 20;

}

///////////////////////////////////////////////////////////////
void Jugador::draw()
{
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

}

// Modelo de personaje  
//                      ┌───┐
//                      │   │
//                      └───┘
//                      / A \
//                       / \


///////////////////////////

void Jugador::setX(int x) {m_x = x;}
void Jugador::setY(int y) {m_y = y;}


int Jugador::getX() { return m_x;}
int Jugador::getY() { return m_y;}