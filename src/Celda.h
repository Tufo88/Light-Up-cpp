/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef CELDA_H
#define CELDA_H

#include <iostream>
using namespace std;

typedef enum tTipo { PARED, BOMBILLA, LIBRE };

typedef struct {
	tTipo tipo;
	int numBombillas;
} tCelda;

bool esPared(const tCelda& c);
bool esParedRestringida(const tCelda& c);
int numParedRestringida(const tCelda& c);
bool esBombilla(const tCelda& c);
bool estaApagada(const tCelda& c);
bool estaIluminada(const tCelda& c);
void decrementaIluminacion(tCelda& c);
void aumentaIluminacion(tCelda& c);
void resetearCelda(tCelda& c);
void ponBombilla(tCelda& c);
istream& operator>>(istream& in, tCelda& celda);
bool operator!=(const tCelda& celda1, const tCelda& celda2);
bool operator==(const tCelda& celda1, const tCelda& celda2);
ostream& operator<<(ostream& out, const tCelda& celda);

namespace random {
	tCelda crearCelda(tTipo tipo, int numBombillas);
}
#endif // !CELDA_H