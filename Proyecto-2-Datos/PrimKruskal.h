#ifndef PRIMKRUSKAL_H
#define PRIMKRUSKAL_H

#include "Constantes.h"
#include "Grafo.h"

struct ResultadoMST {
	bool conectado;
	AristaRuta aristas[MAX_CIUDADES];
	int cantidadAristas;
	double costoTotal;
	double duracionTotal;
	string preorden;
	string inorden;
	string postorden;
	string anchura;
};

class PrimKruskal {
private:
	static void construirHijos(int cantidadCiudades, const AristaRuta aristas[], int cantidadAristas, int raiz, int hijos[][MAX_CIUDADES], int cantHijos[]);
	static void recPreorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto);
	static void recInorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto);
	static void recPostorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto);
	static void recAnchura(const Grafo& grafo, int raiz, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto);
	static void llenarRecorridos(const Grafo& grafo, int raiz, ResultadoMST& resultado);
	
public:
	static ResultadoMST calcularPrim(const Grafo& grafo, int ciudadInicial = 0);
	static ResultadoMST calcularKruskal(const Grafo& grafo, int ciudadInicial = 0);
};

#endif
