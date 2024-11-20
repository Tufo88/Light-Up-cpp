/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#include "utils.h"
#include "colors.h"
#include "posicion.h"
#include "celda.h"
#include "tablero.h"
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

const int ESPACIO = 10;

int getNumFilas(const tTablero& tab) {
	return tab.nFils;
}

int getNumCols(const tTablero& tab) {
	return tab.nCols;
}

int getNivel(tTablero const& tab) {
	return tab.nivel;
}

bool esPosValida(tTablero const& tablero, tPos pos) {
	return fila(pos) >= 0 && fila(pos) < getNumFilas(tablero) && columna(pos) >= 0 && columna(pos) < getNumCols(tablero);
}

tCelda celdaEnPos(const tTablero& tablero, tPos pos) {
	if (!esPosValida(tablero, pos)) throw invalid_argument("Pos provided is not valid");
	return tablero.datos[fila(pos)][columna(pos)];
}

void cambiaCeldaEnPos(tTablero& tablero, tPos pos, tCelda laCelda) {
	tablero.datos[fila(pos)][columna(pos)] = laCelda;
}

void imprimirFila_ObtenerBombillas(ostream& out, const tTablero& elJuego, int i, vector<tPos>& bombillasAnadir) {
	for (int columna = 0; columna < getNumCols(elJuego); columna++) {
		tPos pos = crearPos(i, columna);
		tCelda celda = celdaEnPos(elJuego, pos);
		out << celda;
		if (esBombilla(celda)) bombillasAnadir.push_back(pos);
	}
	out << endl;
}

void imprimirBombillas(ostream& out, vector<tPos>& bombillas) {
	for (vector<tPos>::iterator iter = bombillas.begin(); iter != bombillas.end(); iter++) {
		out << fila(*iter) << " " << columna(*iter) << " ";
	}
	if (bombillas.size()) out << "\n";
}

void guardarJuego(ostream& out, tTablero const& elJuego) {
	vector<tPos>bombillas;
	out << "LEVEL " << getNivel(elJuego) << "\n";
	out << getNumFilas(elJuego) << " " << getNumCols(elJuego) << "\n";
	for (int i = 0; i < getNumFilas(elJuego); i++) {
		imprimirFila_ObtenerBombillas(out, elJuego, i, bombillas);
	}
	out << bombillas.size() << "\n";
	imprimirBombillas(out, bombillas);
}

//metodo priv
void printSeparadorFila(ostream& out, const tTablero& tab) {
	out << setw(ESPACIO) << right << "-+";

	for (int j = 0; j < getNumCols(tab); j++) { //separador -+  ---+
		out << "---+";
	}
	out << '\n';
}

//metodo priv
void printFila(ostream& out, const tTablero& tab, int fila) {
	tCelda celda;

	out << LBLUE << setw(ESPACIO - 1) << right << fila;

	for (int columna = 0; columna < getNumCols(tab); columna++) {

		celda = celdaEnPos(tab, crearPos(fila, columna));

		out << celda;

	}

	out << WHITE << BG_BLACK << "|" << '\n';
}

//metodo priv
void printNumFila(ostream& out, const tTablero& tab) {
	out << setw(ESPACIO + 1) << right << "| ";
	for (int i = 0; i < getNumCols(tab); i++) { //numeros primeros
		out << LBLUE << i << WHITE << (i > 9 ? "" : " ") << "| ";
	}
	out << '\n';
}

ostream& operator<<(ostream& out, const tTablero& tab) {
	if (!esConsola(out)) {

		guardarJuego(out, tab);
	}
	else {
		printNumFila(out, tab);

		for (int i = 0; i < getNumFilas(tab); i++) {
			printSeparadorFila(out, tab);
			printFila(out, tab, i);
		}
		printSeparadorFila(out, tab);
	}

	return out;
}

istream& operator>>(istream& archivo, tTablero& tab) { //carga del tablero
	string aux;
	archivo >> aux;

	archivo >> tab.nivel;
	archivo >> tab.nFils;
	archivo >> tab.nCols;
	for (int i = 0; i < getNumFilas(tab); i++) {
		for (int j = 0; j < getNumCols(tab); j++) {
			tCelda celda;
			archivo >> celda;
			cambiaCeldaEnPos(tab, crearPos(i, j), celda);
		}
	}

	return archivo;
}

bool operator< (tTablero const& tab1, tTablero const& tab2) {
	return tab1.nivel < tab2.nivel;
}

