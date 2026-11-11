#include "PilaEnteros.h"

PilaEnteros::PilaEnteros() {
	tope = nullptr;
	cantidad = 0;
}

PilaEnteros::~PilaEnteros() {
	vaciar();
}

void PilaEnteros::apilar(int valor) {
	NodoPila* nuevo = new NodoPila{ valor, tope };
	tope = nuevo;
	cantidad++;
}

int PilaEnteros::desapilar() {
	if (estaVacia()) {
		return -1;
	}
	NodoPila* viejo = tope;
	int valor = viejo->valor;
	tope = tope->siguiente;
	delete viejo;
	cantidad--;
	return valor;
}

int PilaEnteros::verTope() const {
	if (estaVacia()) {
		return -1;
	}
	return tope->valor;
}

bool PilaEnteros::estaVacia() const {
	return tope == nullptr;
}

int PilaEnteros::tamanio() const {
	return cantidad;
}

void PilaEnteros::vaciar() {
	while (!estaVacia()) {
		desapilar();
	}
}
