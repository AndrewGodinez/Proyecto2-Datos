#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include "Constantes.h"
#include "Grafo.h"

class BellmanFord {
public:

	static ResultadoRuta calcularRuta(const Grafo& grafo, int origen, int destino, int criterio);
	
	static int calcularTodosLosDestinos(const Grafo& grafo, int origen, int criterio, ResultadoRuta rutasDestinos[MAX_CIUDADES]);
};

#endif
