/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/
#include "VectorPtrTableros.h"
#include <iostream>
#include "tablero.h"
#include "juego.h"

istream& operator>>(istream& in, tPtrTablero tablero) {
	in >> *tablero;

	int nBombillas, fila, col;

	in >> nBombillas;
	for (int i = 0; i < nBombillas; i++) {

		in >> fila;
		in >> col;

		ejecutarPos(*tablero, crearPos(fila, col));

	}
	return in;
}

bool estaLleno(const tListaTableros& losTableros) {
	return losTableros.nElem >= losTableros.capacidad;
}

bool esPosValida(tListaTableros const& losTableros, int pos) {
	return pos >= 0 && pos < losTableros.nElem;
}

tPtrTablero ptrTableroEnPos(const tListaTableros& losTableros, int pos) {
	return esPosValida(losTableros, pos) ? losTableros.datos[pos] : NULL;
}


void resizeMemCopy(tListaTableros& tableros) {
	tPtrTablero* aux = tableros.datos;
	tableros.capacidad *= 2;

	tableros.datos = new tPtrTablero[tableros.capacidad];

	memcpy(tableros.datos, aux, sizeof(tPtrTablero*) * tableros.capacidad / 2);

	delete[] aux;
}

//void resizeCopy(tListaTableros& losTableros, tPtrTablero* datosSalvar) {
//	for (int i = 0; i < losTableros.nElem; i++) {
//		losTableros.datos[i] = datosSalvar[i];
//	}
//}
//
//void resizeListaTableros(tListaTableros& losTableros) {
//	tPtrTablero* aux = losTableros.datos;
//	int nElem = losTableros.nElem;
//	inicializaVectorTablero(losTableros, losTableros.capacidad * 2);
//	losTableros.nElem = nElem;
//
//	resizeCopy(losTableros, aux);
//
//	delete[] aux;
//}


void insertarOrdTablero(tListaTableros& losTableros, tPtrTablero const& elTablero) {
	if (estaLleno(losTableros)) resizeMemCopy(losTableros);
	int i = losTableros.nElem;

	while (i > 0 && *elTablero < *ptrTableroEnPos(losTableros, i - 1)) {
		losTableros.datos[i] = losTableros.datos[i - 1];
		i--;
	}

	losTableros.datos[i] = elTablero;
	losTableros.nElem++;
}

istream& operator>> (istream& in, tListaTableros& losTableros) {
	int nElem;
	in >> nElem;
	inicializaVectorTablero(losTableros, nElem);

	for (int i = 0; i < nElem; i++) {
		tPtrTablero tablero = new tTablero;
		in >> tablero;
		insertarOrdTablero(losTableros, tablero);
	}

	return in;
}

ostream& operator<< (ostream& out, tListaTableros const& losTableros) {
	out << "\n";
	for (int i = 0; i < losTableros.nElem; i++) {
		out << "Nivel: " << losTableros.datos[i]->nivel << "\n" << *losTableros.datos[i] << "\n";
	}

	return out;
}


void inicializaVectorTablero(tListaTableros& losTableros, int capacidad) {
	losTableros.nElem = 0;
	losTableros.capacidad = capacidad;
	losTableros.datos = new tPtrTablero[capacidad];
	
}

bool leerVectorTableroFichero(string nombreFich, tListaTableros& losTableros) {
	ifstream archivo;
	archivo.open(nombreFich);
	bool abierto = archivo.is_open();

	if (abierto) {

		archivo >> losTableros;

		archivo.close();
	}

	return abierto;
}

bool hayTableroNivel(tListaTableros const& losTableros, int nivel) {
	return dameTableroNivel(losTableros, nivel) != NULL;
}

int busquedaBinariaSigElem(const tListaTableros& tableros, int posIni, int posFin, int nivelBuscado) {
	int posMitad = (posFin + posIni) / 2, pos = posMitad;
	int nivel = getNivel(*ptrTableroEnPos(tableros, posMitad));

	if (posIni > posFin) pos = posIni;
	else if (nivel == nivelBuscado) pos = posMitad;
	else if (nivel > nivelBuscado) pos = busquedaBinariaSigElem(tableros, posIni, posMitad - 1, nivelBuscado);
	else pos = busquedaBinariaSigElem(tableros, posMitad + 1, posFin, nivelBuscado);


	return pos;
}

int busquedaBinaria(const tListaTableros& tableros, int posIni, int posFin, int nivelBuscado, bool aproximar = false) {
	int posMitad = (posFin + posIni) / 2, pos = posMitad;
	int nivel = getNivel(*ptrTableroEnPos(tableros, posMitad));
	
	if (posIni > posFin) {
		if (aproximar) pos = posIni;
		else pos = -1;
	}
	else if (nivel == nivelBuscado) pos = posMitad;
	else if (nivel > nivelBuscado) pos = busquedaBinaria(tableros, posIni, posMitad - 1, nivelBuscado, aproximar);
	else pos = busquedaBinaria(tableros, posMitad + 1, posFin, nivelBuscado, aproximar);
	
	
	return pos;
}

tPtrTablero dameTableroNivel(tListaTableros const& losTableros, int nivel) {
	int pos;
	tPtrTablero ptrTablero = NULL;

	if (losTableros.nElem > 0) {
		pos = busquedaBinaria(losTableros, 0, losTableros.nElem - 1, nivel);
		ptrTablero = ptrTableroEnPos(losTableros, pos);
	}

	return (ptrTablero && getNivel(*ptrTablero) == nivel ? ptrTablero : NULL);
}

tPtrTablero dameTableroSigNivel(tListaTableros const& losTableros, int nivel) {
	int pos;
	tPtrTablero ptrTablero = NULL;

	if (losTableros.nElem > 0) {
		pos = busquedaBinaria(losTableros, 0, losTableros.nElem - 1, nivel, true);
		ptrTablero = ptrTableroEnPos(losTableros, pos);
	}

	if (ptrTablero && getNivel(*ptrTablero) <= nivel) ptrTablero = ptrTableroEnPos(losTableros, pos + 1);
	
	return ptrTablero;
}

void deleteTableroNivel(tListaTableros& losTableros, int nivel) {
	int pos = busquedaBinaria(losTableros, 0, losTableros.nElem - 1, nivel);

	if(ptrTableroEnPos(losTableros, pos)) delete ptrTableroEnPos(losTableros, pos);

	for (int i = pos; i < losTableros.nElem - 1; i++) {
		losTableros.datos[i] = ptrTableroEnPos(losTableros, i + 1);
		
	}
	losTableros.nElem--;
	
}

void deleteVectorTablero(tListaTableros & losTableros) {
	for (int i = 0; i < losTableros.nElem; i++) delete losTableros.datos[i];

	delete[] losTableros.datos;
}

bool guardarVectorTableroFichero(string nombreFich, tListaTableros const& losTableros) {
	ofstream archivo;
	bool abierto;
	archivo.open(nombreFich);
	abierto = archivo.is_open();
	if (abierto) {
		archivo << losTableros.nElem << "\n";
		for (int i = 0; i < losTableros.nElem; i++) {
			archivo << *ptrTableroEnPos(losTableros, i);
		}
		archivo.close();
	}
	return abierto;
}