/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>

#include <vector>
#include <iostream>
#include <fstream>
#include "colors.h"
#include "utils.h"
#include "direccion.h"
#include "posicion.h"
#include "Celda.h"
#include "tablero.h"
#include "juego.h"
#include "VectorPtrTableros.h"
using namespace std;

typedef enum tCarga { RANDOM, LISTATAB };

tCarga menu();
int menuDificultad();
int pedirNivel();
void jugar(tListaTableros& listaTab);
void jugarPartida(tTablero& tablero, tPos& pos);
tCarga intToCarga(int num);

int main() {
	tTablero tablero;
	tListaTableros tableros;
	ifstream archivo;
	int opcionCarga, dificultad;
	bool listaTablerosValida = leerVectorTableroFichero("tableros.txt", tableros) && tableros.nElem > 0;

	if(listaTablerosValida) opcionCarga = menu();
	
	if(!listaTablerosValida || opcionCarga == RANDOM){ // aleatorio
		tPos pos;
		dificultad = menuDificultad();
		random::generarTableroAleatorio(tablero, dificultad);
		jugarPartida(tablero, pos);
	}
	else if(opcionCarga == LISTATAB){
		cout << tableros << endl;
		jugar(tableros);
		guardarVectorTableroFichero("tableros.txt", tableros);
		deleteVectorTablero(tableros);
	}
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}

tCarga menu() {
	int opcion;
	do {
		cout << "1.- Cargar tableros de archivo" << endl;
		cout << "2.- Generar un tablero aleatorio" << endl;
		cout << "Elige una de las opciones: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 2);

	return intToCarga(opcion);
}

int menuDificultad() {
	int opcion;
	do {
		cout << "1.- Facil" << endl;
		cout << "2.- Medio" << endl;
		cout << "3.- Dificil" << endl;
		cout << "Elige una de las opciones: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 3);

	return opcion;
}

int pedirNivel() {
	int nivel;
	cout << "Dime que nivel quieres jugar: ";
	cin >> nivel;
	return nivel;
}

void jugarPartida(tTablero& tablero, tPos& pos) {

	int contadorTurnos = 0;
	
	bool finalizado = estaTerminado(tablero);

	cout << ORANGE <<"Vas a jugar el nivel: " << getNivel(tablero) << "\n" << RESET;

	cout << tablero;

	while (!finalizado && !esPosQuit(pos)) {

		pedirPos(pos);

		if (esPosReset(pos)) contadorTurnos = 0;
		else if (!esPosQuit(pos) && !esPosValida(tablero, pos)) cout << RED << "\nPosicion introducida no valida. \n\n" << RESET;

		ejecutarPos(tablero, pos);

		cout << tablero;

		contadorTurnos++;

		finalizado = estaTerminado(tablero);

	}
	
	if (finalizado) cout << LGREEN << "\n\tHas acabado la partida en " << contadorTurnos << " movimientos\n\n" << RESET;
}

void jugar(tListaTableros& listaTab) {
	tPos pos;
	int nivel = pedirNivel();
	tPtrTablero ptrTablero = dameTableroNivel(listaTab, nivel);
	if (ptrTablero == NULL) ptrTablero = dameTableroSigNivel(listaTab, nivel);
	if (ptrTablero != NULL) {
		do {

			jugarPartida(*ptrTablero, pos);
			nivel = getNivel(*ptrTablero);

			if (!esPosQuit(pos)) {
				deleteTableroNivel(listaTab, nivel);
				ptrTablero = dameTableroSigNivel(listaTab, nivel);
			}
			
		} while (!esPosQuit(pos) && ptrTablero != NULL);
	}
	else {
		cout << RED << "ERROR: Nivel no encontrado" << RESET;
	}
}

tCarga intToCarga(int num) {
	tCarga carga;
	switch (num)
	{
	case 1: 
		carga = LISTATAB;
		break;
	case 2:
		carga = RANDOM; 
			break;
	}
	return carga;
}