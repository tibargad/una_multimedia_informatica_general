
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

bool game_over;
int puntaje;
bool salir;

Jugador miJugador;

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

	if ( LINES < ALTO || COLS < ANCHO)
	{
		endwin();
		printf ("La terminal tiene que tener como minimo %dx%d\n\n", ANCHO, ALTO);
		exit (1);
	}

setup();

salir = false;

while (!salir)
{
	while (!game_over)
	{
		input();
		update();
		draw();
	}
	gameover();
}

endwin();

cout << endl;

  return 0;
}

	
//////////////////////////////////////////////////////////////////////////////

void setup()
{

		
	game_over = false;
	puntaje = 0;

	miJugador.setup();

	for (int i = 0;i < 5; i++)
	{
		Cascarudos.push_back(Cascarudo(rand() + 1, 1));

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
		game_over = true;
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

	if(miJugador.getVidas() <=0 ) game_over = true;

	for ( int i = 0; i < Cascarudos.size(); i++)
	{
		Cascarudos[i].update();
		Cascarudos[i].colision(miJugador);

	}

	for (int i=0; i < Proyectiles.size(); i++)
	{
		Proyectiles [i].update();

		if (Proyectiles[i].limite())
		{
			Proyectiles.erase(Proyectiles.begin()+i);
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
	for ( int y = 10; y < 16; y++) 
		mvhline(y, 40, ' ', 40);

		mvaddch(9, 39, ACS_ULCORNER);
		mvaddch(9, 80, ACS_URCORNER);
		mvaddch(16, 39, ACS_LLCORNER);
		mvaddch(16, 80, ACS_LRCORNER);

		mvhline(9, 40, ACS_HLINE, 40);
		mvhline(16, 40, ACS_HLINE, 40);

		mvvline(10, 39, ACS_VLINE, 6);
		mvvline(10, 80, ACS_VLINE, 6);

		mvprintw(12, 55, "HAS SIDO DEVORADO POR UNO DE LOS CASCARUDOS. GAME OVER.");
		mvprintw(13, 50, "SOS EL ETERNAUTA QUE VAGA POR EL TIEMPO. ¿QUERÉS VOLVER A INTENTAR? (S/N)");

		int opcion = getch();

		if (opcion == 's' || opcion == 'S')
		{
			setup();
		}
		else if( opcion == 'n' || opcion == 'N')
		{
			salir = TRUE;

		}


}