#ifndef CONJUNTODISJUNTO_H
#define CONJUNTODISJUNTO_H

#include "Constantes.h"

class ConjuntoDisjunto {
private:
	int padre[MAX_CIUDADES];
	int altura[MAX_CIUDADES];
	
public:
	ConjuntoDisjunto();
	void inicializar(int cantidadCiudades);
	int encontrar(int ciudad);
	bool unir(int ciudadA, int ciudadB);
	bool mismoConjunto(int ciudadA, int ciudadB);
};

#endif
