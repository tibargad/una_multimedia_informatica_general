
#include <iostream>
#include <ncurses.h>
#include "Jugador.h"
#include "Cascarudo.h"
#include <vector>
#include "Proyectil.h"

using namespace std;


const int ANCHO = 120;
const int ALTO = 40;
const int DELAY = 30;

enum class GameState { PLAYING, LOSE, EXIT, CREDITS, MENU };
GameState estadoActual;

int puntaje;

Jugador miJugador(60, 20); 

vector<Proyectil> Proyectiles;
vector<Cascarudo> Cascarudos;

void setup();
void input();
void update();
void draw();
void gameover();





int main()
{
	initscr();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);


	start_color();
	use_default_colors();
	
	init_pair(10, COLOR_WHITE, COLOR_CYAN); // BASE PARA EL FONDO
	init_pair(1, COLOR_MAGENTA, COLOR_CYAN); // JUGADOR
	init_pair(2, COLOR_BLUE, COLOR_CYAN);  // CASCARUDO
	init_pair(3, COLOR_GREEN, COLOR_CYAN); // ENTORNO
	bkgd(COLOR_PAIR(10)); // FONDO

	estadoActual = GameState::MENU;

	if ( LINES < ALTO || COLS < ANCHO)
	{
		endwin();
		printf ("La terminal tiene que tener como minimo %dx%d\n\n", ANCHO, ALTO);
		exit (1);
	}

setup();


	while (estadoActual != GameState::EXIT) 
		{
			
			switch (estadoActual)
			{
				case GameState::MENU:
            {
                clear();
                int max_y, max_x;
                getmaxyx(stdscr, max_y, max_x);

                
                mvprintw(max_y / 2 - 2, (max_x / 2) - 10, "1 - Jugar");
                mvprintw(max_y / 2 - 1, (max_x / 2) - 10, "2 - Creditos");
                mvprintw(max_y / 2,     (max_x / 2) - 10, "3 - Salir");
                refresh();

                int opcion = getch();

                switch (opcion)
                {
                    case '1':
                        setup();
                        estadoActual = GameState::PLAYING;
                        break;
                    case '2':
                       
                        clear();
                        mvprintw(max_y / 2, (max_x / 2) - 22, "Somos: Ani, Dulce, Lourdes y Tomas");
                        mvprintw(max_y / 2 + 2, (max_x / 2) - 15, "Presiona una tecla para volver...");
                        refresh();
                        getch(); 
                        break;
                    case '3':
                        estadoActual = GameState::EXIT;
                        break;
                }
                break;
            }

            case GameState::PLAYING:
                input();
                update();
                draw();
                break;

            case GameState::LOSE:
                gameover();
                break;
			}
		}

		endwin();
		return 0;
	}

	
//////////////////////////////////////////////////////////////////////////////

void setup()
{

		
	puntaje = 0;

	Cascarudos.clear(); // Para que cuando reiniciemos el juego se limpie

	for (int i = 0;i < 5; i++)
	{
		Cascarudos.push_back(Cascarudo((rand() % (ANCHO - 7)) + 1, 1));

	}

}

void input ()
{
		int tecla = getch();

		switch (tecla)
		{
		case KEY_UP:
		if (miJugador.getY() > 1) miJugador.setY(miJugador.getY() - 1); // obtiene el valor y le resta y para desplazarse
		break;
		case KEY_DOWN:
		if (miJugador.getY() < ALTO - 6) miJugador.setY(miJugador.getY() + 1);
		break;
		case KEY_LEFT:
        if (miJugador.getX() > 1) miJugador.setX(miJugador.getX() - 1);
        break;
        case KEY_RIGHT:
        if (miJugador.getX() < ANCHO -9) miJugador.setX(miJugador.getX() + 1);
        break;
		
	case 27:
		estadoActual = GameState::EXIT;
		break;
	case 'e':
			miJugador.setResistencia (miJugador.getResistencia() - 1);
			break;
	case 'z':
			Proyectiles.push_back(Proyectil(miJugador.getX() + 2, miJugador.getY()));
			break;
	default:
		break;
		}
}

//////////////////////////////////////////////////////////////////////////////

void update()
{
	miJugador.update();

	if(miJugador.getVidas() <=0 ) estadoActual = GameState::LOSE;

	for ( int i = 0; i < Cascarudos.size(); i++)
	{
		Cascarudos[i].update();
		Cascarudos[i].colision(miJugador);

	}

	for (int i=0; i < Proyectiles.size(); i++)
	{
		Proyectiles [i].update();

        for( int j = 0; j < Cascarudos.size(); j++)
		{
			if (Proyectiles[i].colision(Cascarudos[j]))
			{
				Cascarudos[j].setX(rand() + 1);
				Cascarudos[j].setY(1);

				Proyectiles.erase(Proyectiles.begin() + i);
				i--; // Para no saltarnos un proyectil
				break;
			}
			
		}
		if (i >= 0 && Proyectiles[i].limite())
		{
			Proyectiles.erase(Proyectiles.begin() + i);
			i--; // Para no saltarnos el proyectil
		}

	}

}

//////////////////////////////////////////////////////////////////////////////
void draw()
{
	erase();
	box(stdscr, 0, 0);

	mvprintw(0, 80, "[ RESISTENCIA:     ]");
	for (int i = 0; i < miJugador.getResistencia(); i++)
	{
		mvaddch(0, 94 + i, ACS_CKBOARD);
	}

	mvprintw(0, 100, "[ VIDAS:     ]");
	for (int i = 0; i < miJugador.getVidas(); i++)
	{
		mvaddch(0, 109 + i, A_ALTCHARSET | 128 );
	}
	

	miJugador.draw();
	
	for (int i = 0; i < Cascarudos.size(); i++)
	{
		Cascarudos[i].draw();
	}

	for ( int i = 0; i < Proyectiles.size(); i++) Proyectiles [i].draw();


	refresh();
	delay_output(DELAY);

}


//////////////////////////////////////////////////////////////////////////////

void gameover()
{
    int centro_x = ANCHO / 2;
    int centro_y = ALTO / 2;
    int ancho_caja = 50; 
    int alto_caja = 6;  

    int caja_x1 = centro_x - (ancho_caja / 2);
    int caja_y1 = centro_y - (alto_caja / 2);
    int caja_x2 = centro_x + (ancho_caja / 2);
    int caja_y2 = centro_y + (alto_caja / 2);

    mvaddch(caja_y1, caja_x1, ACS_ULCORNER);
    mvaddch(caja_y1, caja_x2, ACS_URCORNER);
    mvaddch(caja_y2, caja_x1, ACS_LLCORNER);
    mvaddch(caja_y2, caja_x2, ACS_LRCORNER);
    mvhline(caja_y1, caja_x1 + 1, ACS_HLINE, ancho_caja - 1);
    mvhline(caja_y2, caja_x1 + 1, ACS_HLINE, ancho_caja - 1);
    mvvline(caja_y1 + 1, caja_x1, ACS_VLINE, alto_caja - 1);
    mvvline(caja_y1 + 1, caja_x2, ACS_VLINE, alto_caja - 1);

 
    mvprintw(centro_y - 1, centro_x - 17, "FUISTE DEVORADO POR UN CASCARUDO.");
    mvprintw(centro_y + 1, centro_x - 15, "¿Reintentar? (S/N)");
    
		nodelay(stdscr, FALSE);
		int opcion = getch();

		if (opcion == 's' || opcion == 'S')
		{
			setup(); 
			estadoActual = GameState::PLAYING;
		}
		else if( opcion == 'n' || opcion == 'N')
		{
			estadoActual = GameState::EXIT;
		}

		nodelay(stdscr, TRUE);
}


