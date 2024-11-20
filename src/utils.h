/*
Pablo Rodriguez Gonzalez

Andres Armengol Rosales

parogr20@ucm.es; aarmen01@ucm.es

*/

#ifndef __UTILS_H__
#define __UTIL_H__
#include <fstream> // para ficheros
using namespace std;

// Indica si el str corresponde con una consola.
bool esConsola(ios& str);
// Configurar la consola para espa�ol.
void configuraCastellanoConsola();

int pedirInt();
int numCharAInt(char num);

#endif // !__UTILS_H__