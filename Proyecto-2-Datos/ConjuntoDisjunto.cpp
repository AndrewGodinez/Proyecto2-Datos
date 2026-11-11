#include "ConjuntoDisjunto.h"

ConjuntoDisjunto::ConjuntoDisjunto() {
	inicializar(MAX_CIUDADES);
}

void ConjuntoDisjunto::inicializar(int cantidadCiudades) {
	for (int i = 0; i < cantidadCiudades && i < MAX_CIUDADES; i++) {
		padre[i] = i;
		altura[i] = 0;
	}
}

int ConjuntoDisjunto::encontrar(int ciudad) {
	if (padre[ciudad] == ciudad) {
		return ciudad;
	}
	padre[ciudad] = encontrar(padre[ciudad]);
	return padre[ciudad];
}

bool ConjuntoDisjunto::unir(int ciudadA, int ciudadB) {
	int jefeA = encontrar(ciudadA);
	int jefeB = encontrar(ciudadB);
	if (jefeA == jefeB) {
		return false;
	}
	if (altura[jefeA] < altura[jefeB]) {
		padre[jefeA] = jefeB;
	} else if (altura[jefeA] > altura[jefeB]) {
		padre[jefeB] = jefeA;
	} else {
		padre[jefeB] = jefeA;
		altura[jefeA]++;
	}
	return true;
}

bool ConjuntoDisjunto::mismoConjunto(int ciudadA, int ciudadB) {
	return encontrar(ciudadA) == encontrar(ciudadB);
}
