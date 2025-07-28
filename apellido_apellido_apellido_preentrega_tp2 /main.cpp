/*************************************************************************\
 Instalar la librería ncurses
 Ejecutar en la terminal de Linux:
 sudo apt install libncurses-dev
 
 En el proyecto de C++:
 Agregar en el archivo tasks.json, que está en la carpeta .vscode, 
 debajo de:
 “${fileDirname}/${fileBasenameNoExtension}”,
 "-lncurses"
\*************************************************************************/

#include <iostream>
#include <ncurses.h>

using namespace std;

int main()
{
	initscr(); // Es para entrar en modo ncurses
	getch(); // Pausa para poder ver lo de ncurses.
	endwin(); // Es para salir del modo ncurses

	cout << "Hasta luego Ncurses!!!" << endl;
  return 0;
}
