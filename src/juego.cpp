/*
Pablo Rodriguez Gonzalez
Andres Armengol Rosales
parogr20@ucm.es; aarmen01@ucm.es
*/

#include <fstream>
#include "direccion.h"
#include "posicion.h"
#include "Celda.h"
#include "tablero.h"
#include "juego.h"
#include <ctime>

void resetearTablero(tTablero& tablero) {
	tPos pos;
	tCelda celda;

	for (int i = 0; i < getNumFilas(tablero); i++) {
		for (int j = 0; j < getNumCols(tablero); j++) {

			pos = crearPos(i, j);
			celda = celdaEnPos(tablero, pos);
			resetearCelda(celda);
			cambiaCeldaEnPos(tablero, pos, celda);

		}
	}
}

int numBombillasVecinas(const tTablero& tablero, tPos pos) {

	tDir dir[] = { NORTE, SUR, ESTE, OESTE };
	int numDir = sizeof(dir) / sizeof(tDir);
	int numBombillas = 0;

	tPos posAux;

	for (int i = 0; i < numDir; i++) {
		copiarPos(posAux, pos);
		avanzarPosDir(posAux, dir[i]);
		if (esPosValida(tablero, posAux) && esBombilla(celdaEnPos(tablero, posAux))) numBombillas++;
	}

	return numBombillas;
}

bool seCumpleRestriccionFin(const tTablero& tablero, tPos pos) {

	tCelda celda = celdaEnPos(tablero, pos);
	return	esBombilla(celda) || estaIluminada(celda)
		|| (esParedRestringida(celda) && (numParedRestringida(celda) == numBombillasVecinas(tablero, pos)))
		|| (esPared(celda) && !esParedRestringida(celda));

}

void cambiarIluminacionDir(tTablero& tablero, tPos pos, tDir dir, bool iluminar) {

	avanzarPosDir(pos, dir);

	tCelda celda;

	while (esPosValida(tablero, pos) && !esPared(celdaEnPos(tablero, pos))) {

		celda = celdaEnPos(tablero, pos);

		if (iluminar) aumentaIluminacion(celda);
		else decrementaIluminacion(celda);

		cambiaCeldaEnPos(tablero, pos, celda);

		avanzarPosDir(pos, dir);
	}

}

void cambiarIluminacion(tTablero& tablero, tPos pos, bool iluminar) {

	tDir dir[] = { NORTE, SUR, ESTE, OESTE };
	int numDir = sizeof(dir) / sizeof(tDir);

	for (int i = 0; i < numDir; i++) {

		cambiarIluminacionDir(tablero, pos, dir[i], iluminar);
	}

}

bool estaTerminado(tTablero const& juego) {
	bool correcto = true;
	int i = 0, j = 0;

	while (i < getNumFilas(juego) && correcto) {
		j = 0;

		while (j < getNumCols(juego) && correcto) {
			correcto = seCumpleRestriccionFin(juego, crearPos(i, j));
			j++;
		}

		i++;
	}

	return correcto;
}

void ejecutarPos(tTablero& tab, tPos pos) {

	if (esPosReset(pos)) resetearTablero(tab);

	else if (esPosValida(tab, pos)){
		tCelda celda = celdaEnPos(tab, pos);

		if (!esPared(celda) && !estaIluminada(celda)) {

			if (esBombilla(celda)) resetearCelda(celda);
			else ponBombilla(celda);

			cambiaCeldaEnPos(tab, pos, celda);
			cambiarIluminacion(tab, pos, esBombilla(celda));

		}
	}

}

bool leerJuegoFichero(string nombreFich, tTablero& tablero) {

	ifstream archivo;
	archivo.open(nombreFich);
	bool abierto = archivo.is_open();

	if (abierto) {

		archivo >> tablero;

		int nBombillas, fila, col;

		archivo >> nBombillas;
		for (int i = 0; i < nBombillas; i++) {

			archivo >> fila;
			archivo >> col;

			ejecutarPos(tablero, crearPos(fila, col));

		}

		archivo.close();


	}

	return abierto;

}

int numCeldasVaciasVecinas(const tTablero& tablero, tPos pos) {

	tDir dir[] = { NORTE, SUR, ESTE, OESTE };
	int numDir = sizeof(dir) / sizeof(tDir);
	int numCeldas = 0;

	tPos posAux;

	for (int i = 0; i < numDir; i++) {
		copiarPos(posAux, pos);
		avanzarPosDir(posAux, dir[i]);
		if (esPosValida(tablero, posAux) && !esBombilla(celdaEnPos(tablero, posAux)) && !esPared(celdaEnPos(tablero, posAux))) numCeldas++;
	}

	return numCeldas;
}



namespace random {

	void generarParedes(tTablero& tablero) {
		for (int i = 0; i < getNumFilas(tablero); i++) {
			for (int j = 0; j < getNumCols(tablero); j++) {
				tPos pos = crearPos(i, j);
				int numProb = rand() % 100;
				if (numProb < 35) {
					cambiaCeldaEnPos(tablero, pos, random::crearCelda(PARED, -1));
				}
			}
		}
	}

	void generarBombillas(tTablero& tablero, bool aleatorio = false) {
		for (int i = 0; i < getNumFilas(tablero); i++) {
			for (int j = 0; j < getNumCols(tablero); j++) {
				int numProb = 0;
				tPos pos = crearPos(i, j);
				if (aleatorio) numProb = rand() % 100;
				if (estaApagada(celdaEnPos(tablero, pos)) && (numProb <= 20)) {
					cambiaCeldaEnPos(tablero, pos, crearCelda(BOMBILLA, 0));
					cambiarIluminacion(tablero, pos, true);
				}
			}
		}
	}

	void generarParedesRestringidas(tTablero& tablero) {
		for (int i = 0; i < getNumFilas(tablero); i++) {
			for (int j = 0; j < getNumCols(tablero); j++) {
				tPos pos = crearPos(i, j);
				int numProb = rand() % 100;
				int numBombillas = numBombillasVecinas(tablero, pos);
				if (esPared(celdaEnPos(tablero, pos)) &&
					((numProb < 10 && numBombillas == 0 && numCeldasVaciasVecinas(tablero, pos) > 0) ||
						(numProb < 40 && numBombillas == 1) ||
						(numProb < 50 && numBombillas == 2) ||
						(numProb < 60 && numBombillas == 3) ||
						(numProb < 70 && numBombillas == 4))) {
					cambiaCeldaEnPos(tablero, pos, crearCelda(PARED, numBombillas));
				}
			}
		}
	}

	void generarTableroAleatorio(tTablero& tablero, int dificultad) {
		int rangeF;
		int rangeC;
		srand(time(NULL));
	
		rangeF = (MAX_FILS * dificultad / 3) - (MAX_FILS * (dificultad - 1) / 3 + (dificultad == 1 ? 4 : 0)) + 1;
		rangeC = (MAX_COLS * dificultad / 3) - (MAX_COLS * (dificultad - 1) / 3 + (dificultad == 1 ? 4 : 0)) + 1;
		tablero.nFils = rand() % rangeF + (MAX_FILS * (dificultad - 1) / 3 + (dificultad == 1 ? 4 : 0));
		tablero.nCols = rand() % rangeC + (MAX_COLS * (dificultad - 1) / 3 + (dificultad == 1 ? 4 : 0));
		
		resetearTablero(tablero);

		generarParedes(tablero);

		generarBombillas(tablero, true);
		generarBombillas(tablero);

		generarParedesRestringidas(tablero);

		resetearTablero(tablero);
	}
}
