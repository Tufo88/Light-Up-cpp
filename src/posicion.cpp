/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#include <iostream>

#include "direccion.h"
#include "posicion.h"
#include "utils.h"
#include <ctime>
using namespace std;

int fila(tPos const& pos) {
	return pos.fila;
}

int columna(tPos const& pos) {
	return pos.col;
}

void pedirPos(tPos& pos)
{
	cout << "Pos: ";

	pos.fila = pedirInt();
	pos.col = pedirInt();

}

tPos crearPos(int fila, int columna) {
	return tPos({ fila, columna });
}

void avanzarPosDir(tPos& pos, tDir dir) {

	switch (dir) {
	case NORTE:
		pos.fila--;
		break;
	case SUR:
		pos.fila++;
		break;
	case ESTE:
		pos.col++;
		break;
	case OESTE:
		pos.col--;
		break;
	}
}

tPos devolverAvanzarPosDir(tPos pos, tDir dir) {
	avanzarPosDir(pos, dir);
	return pos;
}

bool esPosQuit(const tPos& pos) {
	return pos.fila == -1 && pos.col == 0;
}

bool esPosReset(const tPos& pos) {
	return pos.fila == -1 && pos.col == -1;
}

void copiarPos(tPos& posCopia, const tPos posOriginal) {
	posCopia.col = posOriginal.col;
	posCopia.fila = posOriginal.fila;
}
