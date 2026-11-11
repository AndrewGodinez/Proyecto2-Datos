#include "ColaEnteros.h"

ColaEnteros::ColaEnteros() {
	frente = nullptr;
	ultimo = nullptr;
	cantidad = 0;
}

ColaEnteros::~ColaEnteros() {
	vaciar();
}

void ColaEnteros::encolar(int valor) {
	NodoCola* nuevo = new NodoCola{ valor, nullptr };
	if (estaVacia()) {
		frente = nuevo;
	} else {
		ultimo->siguiente = nuevo;
	}
	ultimo = nuevo;
	cantidad++;
}

int ColaEnteros::desencolar() {
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

int ColaEnteros::verFrente() const {
	if (estaVacia()) {
		return -1;
	}
	return frente->valor;
}

int ColaEnteros::verPosicion(int pos) const {
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

bool ColaEnteros::estaVacia() const {
	return frente == nullptr;
}

int ColaEnteros::tamanio() const {
	return cantidad;
}

void ColaEnteros::vaciar() {
	while (!estaVacia()) {
		desencolar();
	}
}
