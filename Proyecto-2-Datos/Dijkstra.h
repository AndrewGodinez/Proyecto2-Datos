#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Constantes.h"
#include "Grafo.h"

class Dijkstra {
public:
	static ResultadoRuta calcularRuta(const Grafo& grafo, int origen, int destino, int criterio, int ignorarOrigen = -1, int ignorarDestino = -1);
	static ResultadoRuta calcularRutaEquipaje(const Grafo& grafo, int origen, int destino, int criterioEquipaje, const ResultadoRuta& rutaPasajero);
};

#endif
