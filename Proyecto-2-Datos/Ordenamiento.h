#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include "Constantes.h"

class Ordenamiento {
private:
	static bool esMenorIgual(const AristaRuta& rutaIzq, const AristaRuta& rutaDer, int criterio);
	static void merge(AristaRuta rutas[], int izq, int medio, int der, int criterio);
	static void mergeSort(AristaRuta rutas[], int izq, int der, int criterio);
	
public:
	static void ordenarRutas(AristaRuta rutas[], int cantidad, int criterio);
};

#endif
