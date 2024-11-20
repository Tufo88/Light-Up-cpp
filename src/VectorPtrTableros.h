/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef PNTTABLERO_H
#define PNTTABLERO_H

#include "tablero.h"
#include <iostream>
typedef tTablero* tPtrTablero;
struct tListaTableros {
	int nElem;
	int capacidad;
	tPtrTablero* datos;
};

istream& operator>> (istream& in, tListaTableros& losTableros);
ostream& operator<< (ostream& out, tListaTableros const& losTableros);
void inicializaVectorTablero(tListaTableros& losTableros, int capacidad);
bool leerVectorTableroFichero(string nombreFich, tListaTableros& losTableros);
bool hayTableroNivel(tListaTableros const& losTableros, int nivel);
tPtrTablero dameTableroNivel(tListaTableros const& losTableros, int nivel);
tPtrTablero dameTableroSigNivel(tListaTableros const& losTableros, int nivel);
void insertarOrdTablero(tListaTableros& losTableros, tPtrTablero const& elTablero);
void deleteTableroNivel(tListaTableros& losTableros, int nivel);
void deleteVectorTablero(tListaTableros& losTableros);
bool guardarVectorTableroFichero(string nombreFich, tListaTableros const& losTableros);

#endif