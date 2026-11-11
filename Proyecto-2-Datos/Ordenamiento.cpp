#include "Ordenamiento.h"

bool Ordenamiento::esMenorIgual(const AristaRuta& rutaIzq, const AristaRuta& rutaDer, int criterio) {
	if (criterio == CRITERIO_DURACION) {
		if (rutaIzq.duracion != rutaDer.duracion) {
			return rutaIzq.duracion < rutaDer.duracion;
		}
		return rutaIzq.costo <= rutaDer.costo;
	}
	if (rutaIzq.costo != rutaDer.costo) {
		return rutaIzq.costo < rutaDer.costo;
	}
	return rutaIzq.duracion <= rutaDer.duracion;
}

void Ordenamiento::merge(AristaRuta rutas[], int izq, int medio, int der, int criterio) {
	int tamIzq = medio - izq + 1;
	int tamDer = der - medio;
	
	AristaRuta* mitadIzq = new AristaRuta[tamIzq];
	AristaRuta* mitadDer = new AristaRuta[tamDer];
	
	for (int i = 0; i < tamIzq; i++) {
		mitadIzq[i] = rutas[izq + i];
	}
	for (int j = 0; j < tamDer; j++) {
		mitadDer[j] = rutas[medio + 1 + j];
	}
	
	int i = 0;
	int j = 0;
	int posActual = izq;
	
	while (i < tamIzq && j < tamDer) {
		if (esMenorIgual(mitadIzq[i], mitadDer[j], criterio)) {
			rutas[posActual] = mitadIzq[i];
			i++;
		} else {
			rutas[posActual] = mitadDer[j];
			j++;
		}
		posActual++;
	}
	
	while (i < tamIzq) {
		rutas[posActual] = mitadIzq[i];
		i++;
		posActual++;
	}
	
	while (j < tamDer) {
		rutas[posActual] = mitadDer[j];
		j++;
		posActual++;
	}
	
	delete[] mitadIzq;
	delete[] mitadDer;
}

void Ordenamiento::mergeSort(AristaRuta rutas[], int izq, int der, int criterio) {
	if (izq >= der) {
		return;
	}
	int medio = izq + (der - izq) / 2;
	mergeSort(rutas, izq, medio, criterio);
	mergeSort(rutas, medio + 1, der, criterio);
	merge(rutas, izq, medio, der, criterio);
}

void Ordenamiento::ordenarRutas(AristaRuta rutas[], int cantidad, int criterio) {
	if (cantidad <= 1) {
		return;
	}
	mergeSort(rutas, 0, cantidad - 1, criterio);
}
