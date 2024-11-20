/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#include "utils.h"
#include <iostream>  // cin, cout, etc.
#include <io.h> // _isatty, _fileno

int numCharAInt(char num) {
	return int(num - '0');
}

int pedirInt()
{
	int num;
	cin >> num;
	while (cin.fail())
	{
		if (cin.fail())
		{
			cout << "ERROR: No es un entero" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');

		}
		cin >> num;
	}
	return num;
}

// Indica si el str corresponde con una consola.
bool esConsola(ios& str) {
	return (_isatty(_fileno(stdin)) && &str == &std::cin)
		|| (_isatty(_fileno(stdout)) && &str == &std::cout)
		|| (_isatty(_fileno(stderr)) && &str == &std::cerr);
}

// Configurar la consola para espa�ol.
void configuraCastellanoConsola() {
	setlocale(LC_ALL, "spanish");  // Escribe bien y lo coloca a entorno espa?ol.
	system("chcp 1252"); // lee bien pero realizo una llamada al sistema no me gusta
	system("cls"); // LLamada al sistema para dejar limpia la pantalla
	/* La l�nea system("chcp 1252"); puede ser sustuida por:
		#include <windows.h> // SetConsoleCP...
		SetConsoleCP(1252); // Cambiar STDIN -  Para m�quinas Windows
		SetConsoleOutputCP(1252); // Cambiar STDOUT - Para m�quinas Windows
	*/
}