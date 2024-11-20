/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef POSICION_H
#define POSICION_H

#include "direccion.h"

typedef struct {
	int fila, col;
} tPos;

int fila(tPos const& pos);
int columna(tPos const& pos);
void pedirPos(tPos& pos);
tPos crearPos(int fila, int columna);
void avanzarPosDir(tPos& pos, tDir dir);
tPos devolverAvanzarPosDir(tPos pos, tDir dir);
bool esPosQuit(const tPos& pos);
bool esPosReset(const tPos& pos);
void copiarPos(tPos& posCopia, const tPos posOriginal);

#endif // !POSICION_H
