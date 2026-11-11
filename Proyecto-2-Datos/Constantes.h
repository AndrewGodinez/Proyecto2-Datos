#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>
using namespace std;

const int ANCHO_VENTANA = 1280;
const int ALTO_VENTANA = 720;
const int MAX_CIUDADES = 60;

const int CRITERIO_COSTO = 0;
const int CRITERIO_DURACION = 1;
const int CRITERIO_ESCALAS = 2;

struct Ciudad {
	int id;
	string codigo;
	string nombre;
	float posX;
	float posY;
};

struct AristaRuta {
	int origen;
	int destino;
	double costo;
	double duracion;
	bool activa;
};

struct ResultadoRuta {
	bool existe;
	bool cicloNegativo;
	int nodos[MAX_CIUDADES];
	int cantidadNodos;
	double costoTotal;
	double duracionTotal;
	int escalas;
};

struct NodoVisual {
	string etiqueta;
	int factorEquilibrio;
	int izq;
	int der;
};

#endif
