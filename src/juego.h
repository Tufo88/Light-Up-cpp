/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef JUEGO_H
#define JUEGO_H

#include <fstream>
#include "direccion.h"
#include "posicion.h"
#include "Celda.h"
#include "tablero.h"

void resetearTablero(tTablero& tablero);
bool estaTerminado(tTablero const& juego);
void ejecutarPos(tTablero& tab, tPos pos);

bool leerJuegoFichero(string nombreFich, tTablero& tablero);

namespace random {
	void generarTableroAleatorio(tTablero& tablero, int dificultad);
}
#endif // !JUEGO_H