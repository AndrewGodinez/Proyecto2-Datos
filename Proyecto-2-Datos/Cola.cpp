#include "Cola.h"

Cola::Cola() {
	frente = nullptr;
	ultimo = nullptr;
	cantidad = 0;
}

Cola::~Cola() {
	vaciar();
}

void Cola::encolar(int valor) {
	NodoCola* nuevo = new NodoCola{ valor, nullptr };
	if (estaVacia()) {
		frente = nuevo;
	} else {
		ultimo->siguiente = nuevo;
	}
	ultimo = nuevo;
	cantidad++;
}

int Cola::desencolar() {
	if (estaVacia()) {
		return -1;
	}
	NodoCola* viejo = frente;
	int valor = viejo->valor;
	frente = frente->siguiente;
	if (frente == nullptr) {
		ultimo = nullptr;
	}
	delete viejo;
	cantidad--;
	return valor;
}

int Cola::verFrente() const {
	if (estaVacia()) {
		return -1;
	}
	return frente->valor;
}

int Cola::verPosicion(int pos) const {
	NodoCola* actual = frente;
	int i = 0;
	while (actual != nullptr && i < pos) {
		actual = actual->siguiente;
		i++;
	}
	if (actual == nullptr) {
		return -1;
	}
	return actual->valor;
}

bool Cola::estaVacia() const {
	return frente == nullptr;
}

int Cola::tamanio() const {
	return cantidad;
}

void Cola::vaciar() {
	while (!estaVacia()) {
		desencolar();
	}
}
