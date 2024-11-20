/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef TABLERO_H
#define TABLERO_H

#include "colors.h"
#include "posicion.h"
#include "celda.h"

const int MAX_FILS = 20;
const int MAX_COLS = 20;
typedef tCelda tTableroDatos[MAX_FILS][MAX_COLS];

struct tTablero {
	int nivel;
	int nFils, nCols;
	tTableroDatos datos;
};

int getNumFilas(const tTablero& tab);
int getNumCols(const tTablero& tab);
int getNivel(tTablero const& tab);
bool esPosValida(tTablero const& tablero, tPos pos);
tCelda celdaEnPos(const tTablero& tablero, tPos pos);
void cambiaCeldaEnPos(tTablero& tablero, tPos pos, tCelda laCelda);
ostream& operator<<(ostream& out, const tTablero& tab);
istream& operator>>(istream& archivo, tTablero& tab);
bool operator< (tTablero const& tab1, tTablero const& tab2);
void guardarJuego(ostream& out, tTablero const& elJuego);


#endif // !TABLERO_H

