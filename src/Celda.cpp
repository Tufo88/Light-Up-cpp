/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#include <iostream>
#include <fstream>
#include "celda.h"
#include "utils.h"
#include "colors.h"

using namespace std;

bool esPared(const tCelda& c) {
	return c.tipo == PARED;
}

bool esParedRestringida(const tCelda& c) {
	return c.tipo == PARED && c.numBombillas != -1;
}

int numParedRestringida(const tCelda& c) {
	return c.numBombillas;
}

bool esBombilla(const tCelda& c) {
	return c.tipo == BOMBILLA;
}

bool estaApagada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas == 0;
}

bool estaIluminada(const tCelda& c) {
	return c.tipo == LIBRE && c.numBombillas > 0;
}

void decrementaIluminacion(tCelda& c) {
	if (!esPared(c)) c.numBombillas--;
}

void aumentaIluminacion(tCelda& c) {
	if (!esPared(c)) c.numBombillas++;
}

void resetearCelda(tCelda& c) {
	if (!esPared(c)) {
		c.tipo = LIBRE;
		c.numBombillas = 0;
	}
}

void ponBombilla(tCelda& c) {
	if (!esPared(c)) c.tipo = BOMBILLA;
}

istream& operator>>(istream& in, tCelda& celda) {
	char casillaLeida;
	in >> casillaLeida;

	if (isdigit(casillaLeida)) {
		celda.tipo = PARED;
		celda.numBombillas = numCharAInt(casillaLeida);
	}
	else {
		switch (casillaLeida)
		{
		case 'X':
			celda.tipo = PARED;
			celda.numBombillas = -1;
			break;
		case '.':
			celda.tipo = LIBRE;
			celda.numBombillas = 0;
			break;
		}
	}

	return in;
}

ostream& operator<<(ostream& out, const tCelda& celda) {
	if (!esConsola(out)) {
		
		if (esParedRestringida(celda)) out << numParedRestringida(celda);
		else if (esPared(celda)) out << "X";
		else out << ".";
	}
	else {

		out << WHITE << BG_BLACK << "|";

		if (!esPared(celda)) {				//casos si no es pared

			if (esBombilla(celda)) {		 //bombilla
				out << BG_YELLOW << BLACK << " * ";
			}

			else if (estaIluminada(celda)) { //casilla iluminada
				out << BG_YELLOW << "   ";
			}

			else {							//casilla sin nada
				out << BG_WHITE << "   ";
			}

		}
		else if (esParedRestringida(celda)) { // pared con restriccion
			out << " " << numParedRestringida(celda) << " ";

		}
		else out << "   "; //pared normal

	}
	return out;
}

bool operator!=(const tCelda& celda1, const tCelda& celda2)
{
	return celda1.tipo != celda2.tipo || celda1.numBombillas != celda2.numBombillas;
}

bool operator==(const tCelda& celda1, const tCelda& celda2)
{
	return celda1.tipo == celda2.tipo && celda1.numBombillas == celda2.numBombillas;
}

namespace random {
	tCelda crearCelda(tTipo tipo, int numBombillas) {
		tCelda celda;
		celda.tipo = tipo;
		celda.numBombillas = numBombillas;
		return celda;
	}
}