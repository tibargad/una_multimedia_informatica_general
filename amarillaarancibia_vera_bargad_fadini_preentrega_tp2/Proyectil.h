#pragma once
#include <iostream>
#include <ncurses.h>

using namespace std;

class Proyectil
{
    public:
        Proyectil(int x, int y);
        void update();
        void draw();

    private:
        int m_x, m_y;
        

}