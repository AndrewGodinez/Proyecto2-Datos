#include "Pila.h"

Pila::Pila() {
	tope = nullptr;
	cantidad = 0;
}

Pila::~Pila() {
	vaciar();
}

void Pila::apilar(int valor) {
	NodoPila* nuevo = new NodoPila{ valor, tope };
	tope = nuevo;
	cantidad++;
}

int Pila::desapilar() {
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

int Pila::verTope() const {
	if (estaVacia()) {
		return -1;
	}
	return tope->valor;
}

bool Pila::estaVacia() const {
	return tope == nullptr;
}

int Pila::tamanio() const {
	return cantidad;
}

void Pila::vaciar() {
	while (!estaVacia()) {
		desapilar();
	}
}
