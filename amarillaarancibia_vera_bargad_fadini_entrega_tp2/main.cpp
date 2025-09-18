
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

enum class GameState { PLAYING, LOSE, EXIT, CREDITS, MENU, WIN };
GameState estadoActual;

const int MAX_ENEMIGOS = 2;
int spawn_timer = 0;
int cascarudos_destruidos;

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
	srand(time(NULL)); // Nos va a proveer de un azar real
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

				int start_x = (max_x / 2) - 39;
                int start_y = max_y / 2 - 8;

				attron(COLOR_PAIR(1));
                mvprintw(start_y,     start_x, "(  ( \\(  )(  __)/ )( \\(  __)  ( \\/ ) /  \\(  _ \\(_  _)/ _\\ (  )    (___ \\");
                mvprintw(start_y + 1, start_x, "/    / )(  ) _) \\ \\/ / ) _)   / \\/ \\(  O ))   /  )( /    \\/ (_/\\   / __/");
                mvprintw(start_y + 2, start_x, "\\_)__)(__)(____) \\__/ (____)  \\_)(_/ \\__/(__\\_) (__)\\_/\\_/\\____/  (____)");
                attroff(COLOR_PAIR(1));
                
                mvprintw(max_y / 2 - 2, (max_x / 2) - 10, "1 - Jugar");
                mvprintw(max_y / 2 - 1, (max_x / 2) - 10, "2 - Creditos");
                mvprintw(max_y / 2,     (max_x / 2) - 10, "3 - Salir");
                refresh();

                int opcion = getch();

                switch (opcion)
                {
                    case '1':
                    {
                        
                        clear();
                        int start_y = 5;
                        int start_x = (max_x / 2) - 45;

                        mvprintw(start_y, start_x, "Buenos Aires. Una noche cualquiera... o al menos eso parecia.");
                        mvprintw(start_y + 1, start_x, "Un grupo de amigos en un monoambiente de Almagro, mate, risas, videojuegos... hasta que la luz se apago.");
                        
                        mvprintw(start_y + 3, start_x, "Afuera, la nieve caia en silencio. Pero no era nieve normal: era mortal.");
                        mvprintw(start_y + 4, start_x, "Bastaba con tocarla para no volver a levantarse.");

                        mvprintw(start_y + 6, start_x, "Las redes cayeron. Las radios callaron. El mundo, de golpe, se quedo sin respuesta.");
                        mvprintw(start_y + 7, start_x, "Y en ese vacio, nacio la primera decision: ?como sobrevivir?");

                        mvprintw(start_y + 9, start_x, "En el primer viaje nos unimos, improvisamos, y creamos un traje protector para desafiar la tormenta.");
                        mvprintw(start_y + 10, start_x, "Fue el primer paso. Con miedo, pero tambien con valor, salimos a la ciudad,");
                        mvprintw(start_y + 11, start_x, "sabiendo que nada volveria a ser como antes.");

                        mvprintw(start_y + 13, start_x, "Ahora, la historia continua. El viento corta, la nieve sigue cayendo, y cada rincon es un peligro.");

                        mvprintw(start_y + 15, start_x, "De pronto, el silencio se quiebra. Un zumbido, primero lejano, despues ensordecedor.");
                        mvprintw(start_y + 16, start_x, "No es el viento. No es un auto. Es otra cosa.");
                        mvprintw(start_y + 17, start_x, "La tierra tiembla... y entonces los ves: los cascarudos gigantes avanzando,");
                        mvprintw(start_y + 18, start_x, "encontrás el arma de un policía. Tu única defensa.");

                        mvprintw(start_y + 22, start_x + 30, "La supervivencia recien empieza. DEFIENDETE DISPARANDO CON 'Z'");
                        mvprintw(start_y + 24, start_x + 28, "[ Presiona una tecla para continuar ]");

                        refresh();
                        nodelay(stdscr, FALSE);
                        getch();
                        nodelay(stdscr, TRUE);

                        setup();
                        estadoActual = GameState::PLAYING;
                        
                        break;
                    }
                    case '2':
                       
                        estadoActual = GameState::CREDITS; 
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

				case GameState::WIN:
            {
                clear();
                int max_y, max_x;
                getmaxyx(stdscr, max_y, max_x);
                int start_x = (max_x / 2) - 40; 

                mvprintw(max_y / 2 - 4, start_x, "Y de pronto... Silencio. Se fueron? Eso parece.");
                mvprintw(max_y / 2 - 3, start_x, "Se llevaron los cadaveres de sus companeros a rastras.");
                mvprintw(max_y / 2 - 1, start_x, "No entiendo mucho de lo que paso ni de lo que pasara, pero tengo que seguir adelante.");
                mvprintw(max_y / 2, start_x, "Debo buscar sobrevivientes. Ante mi, solo la eternidad.");

                mvprintw(max_y / 2 + 4, start_x + 25, "[ Presiona una tecla para volver al menu ]");
                refresh();

                nodelay(stdscr, FALSE);
                getch(); 
                estadoActual = GameState::MENU; 
                nodelay(stdscr, TRUE);
                break;
            }

			case GameState::CREDITS:
				{
					clear();
					int max_y, max_x;
					getmaxyx(stdscr, max_y, max_x);
					mvprintw(max_y / 2, (max_x / 2) - 22, "Somos: Ani, Dulce, Lourdes y Tomas. Tropa del Capitán Tirigall y Vice-Almirante Qualindi");
					mvprintw(max_y / 2 + 2, (max_x / 2) - 15, "Presiona una tecla para volver...");
					refresh();

					nodelay(stdscr, FALSE);
					getch(); // Espera una tecla
					estadoActual = GameState::MENU; // Vuelve al menú
					nodelay(stdscr, TRUE);
					break;
				}
			}
		}

		endwin();
		return 0;
	}

	
//////////////////////////////////////////////////////////////////////////////

void setup()
{

	miJugador.reset();
	cascarudos_destruidos = 0;
	Cascarudos.clear(); // Limpiamos los enemigos de la partida anterior

	// El bucle "for" que creaba los 5 enemigos aquí, se ha eliminado.
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
			Proyectiles.push_back(Proyectil(miJugador.getX() + 4, miJugador.getY()));
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
			if (Proyectiles[i].colision(Cascarudos[j]))
			{
				cascarudos_destruidos++; 
				Cascarudos.erase(Cascarudos.begin() + j);
				Proyectiles.erase(Proyectiles.begin() + i);

				i--; 
				
				break;
			}
			
		}
		if (i >= 0 && Proyectiles[i].limite())
		{
			Proyectiles.erase(Proyectiles.begin() + i);
			i--; // Para no saltarnos el proyectil
		}

	}

	  	const int INTERVALO_SPAWN = 60;
    static int spawn_timer = 0; 
    spawn_timer++;

    if (spawn_timer > INTERVALO_SPAWN && Cascarudos.size() < MAX_ENEMIGOS && cascarudos_destruidos < 10)
    {
        spawn_timer = 0;
        int posX = (rand() % (ANCHO - 7)) + 1;
        Cascarudos.push_back(Cascarudo(posX, 1));
    }

    if (cascarudos_destruidos >= 10 && Cascarudos.empty())
    {
        estadoActual = GameState::WIN;
    }

}

//////////////////////////////////////////////////////////////////////////////
void draw()
{
	erase();
	box(stdscr, 0, 0);

	int restantes = 9 - cascarudos_destruidos;
	if (restantes < 0) restantes = 0; // Para que no muestre números negativos
	mvprintw(0, 55, "[ RESTANTES: %d ]", restantes);

	
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


void Jugador::reset()
{
    m_resistencia = 3;
    m_vidas = 3;
    m_derrota = false;
    m_x = ANCHO / 2;
    m_y = ALTO - 10;
}