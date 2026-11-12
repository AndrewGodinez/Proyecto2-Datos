#include "ArbolAVL.h"
#include "Cola.h"
#include "Texto.h"

static const int MAX_NODOS_AVL = 256;

ArbolAVL::ArbolAVL() {
	raiz = nullptr;
	cantidad = 0;
}

ArbolAVL::~ArbolAVL() {
	limpiar();
}

int ArbolAVL::maximo(int valorA, int valorB) const {
	return (valorA > valorB) ? valorA : valorB;
}

int ArbolAVL::obtenerAltura(NodoAVL* nodo) const {
	return (nodo == nullptr) ? 0 : nodo->altura;
}

int ArbolAVL::obtenerFactorEquilibrio(NodoAVL* nodo) const {
	if (nodo == nullptr) {
		return 0;
	}
	return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
}

void ArbolAVL::actualizarAltura(NodoAVL* nodo) {
	if (nodo != nullptr) {
		nodo->altura = 1 + maximo(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
	}
}

NodoAVL* ArbolAVL::rotarDerecha(NodoAVL* nodoDesbalanceado) {
	NodoAVL* nuevaRaiz = nodoDesbalanceado->izq;
	NodoAVL* subArbolMedio = nuevaRaiz->der;
	
	nuevaRaiz->der = nodoDesbalanceado;
	nodoDesbalanceado->izq = subArbolMedio;
	
	actualizarAltura(nodoDesbalanceado);
	actualizarAltura(nuevaRaiz);
	return nuevaRaiz;
}

NodoAVL* ArbolAVL::rotarIzquierda(NodoAVL* nodoDesbalanceado) {
	NodoAVL* nuevaRaiz = nodoDesbalanceado->der;
	NodoAVL* subArbolMedio = nuevaRaiz->izq;
	
	nuevaRaiz->izq = nodoDesbalanceado;
	nodoDesbalanceado->der = subArbolMedio;
	
	actualizarAltura(nodoDesbalanceado);
	actualizarAltura(nuevaRaiz);
	return nuevaRaiz;
}

NodoAVL* ArbolAVL::balancear(NodoAVL* nodo) {
	if (nodo == nullptr) {
		return nullptr;
	}
	actualizarAltura(nodo);
	int factorEq = obtenerFactorEquilibrio(nodo);
	
	if (factorEq > 1 && obtenerFactorEquilibrio(nodo->izq) >= 0) {
		return rotarDerecha(nodo);
	}
	if (factorEq > 1 && obtenerFactorEquilibrio(nodo->izq) < 0) {
		nodo->izq = rotarIzquierda(nodo->izq);
		return rotarDerecha(nodo);
	}
	if (factorEq < -1 && obtenerFactorEquilibrio(nodo->der) <= 0) {
		return rotarIzquierda(nodo);
	}
	if (factorEq < -1 && obtenerFactorEquilibrio(nodo->der) > 0) {
		nodo->der = rotarDerecha(nodo->der);
		return rotarIzquierda(nodo);
	}
	return nodo;
}

NodoAVL* ArbolAVL::insertarNodo(NodoAVL* nodo, const ElementoAVL& nuevoDato, bool& insertado) {
	if (nodo == nullptr) {
		insertado = true;
		NodoAVL* nuevo = new NodoAVL{ nuevoDato, nullptr, 1, nullptr, nullptr };
		return nuevo;
	}
	if (nuevoDato.id < nodo->dato.id) {
		nodo->izq = insertarNodo(nodo->izq, nuevoDato, insertado);
	} else if (nuevoDato.id > nodo->dato.id) {
		nodo->der = insertarNodo(nodo->der, nuevoDato, insertado);
	} else {
		insertado = false;
		return nodo;
	}
	return balancear(nodo);
}

NodoAVL* ArbolAVL::obtenerMinimo(NodoAVL* nodo) const {
	NodoAVL* actual = nodo;
	while (actual != nullptr && actual->izq != nullptr) {
		actual = actual->izq;
	}
	return actual;
}

NodoAVL* ArbolAVL::eliminarNodo(NodoAVL* nodo, int id, bool& eliminado) {
	if (nodo == nullptr) {
		return nullptr;
	}
	if (id < nodo->dato.id) {
		nodo->izq = eliminarNodo(nodo->izq, id, eliminado);
	} else if (id > nodo->dato.id) {
		nodo->der = eliminarNodo(nodo->der, id, eliminado);
	} else {
		eliminado = true;
		if (nodo->izq == nullptr || nodo->der == nullptr) {
			NodoAVL* hijoUnico = (nodo->izq != nullptr) ? nodo->izq : nodo->der;
			liberarReservas(nodo->reservas);
			delete nodo;
			return hijoUnico;
		}
		NodoAVL* sucesor = obtenerMinimo(nodo->der);
		nodo->dato = sucesor->dato;
		liberarReservas(nodo->reservas);
		nodo->reservas = sucesor->reservas;
		sucesor->reservas = nullptr;
		bool borradoAux = false;
		nodo->der = eliminarNodo(nodo->der, sucesor->dato.id, borradoAux);
	}
	return balancear(nodo);
}

NodoAVL* ArbolAVL::buscarNodo(NodoAVL* nodo, int id) const {
	if (nodo == nullptr || nodo->dato.id == id) {
		return nodo;
	}
	if (id < nodo->dato.id) {
		return buscarNodo(nodo->izq, id);
	}
	return buscarNodo(nodo->der, id);
}

void ArbolAVL::liberarSubarbol(NodoAVL* nodo) {
	if (nodo == nullptr) {
		return;
	}
	liberarSubarbol(nodo->izq);
	liberarSubarbol(nodo->der);
	liberarReservas(nodo->reservas);
	delete nodo;
}

void ArbolAVL::liberarReservas(NodoReserva* lista) {
	while (lista != nullptr) {
		NodoReserva* borrar = lista;
		lista = lista->siguiente;
		delete borrar;
	}
}

bool ArbolAVL::insertar(int id, string nombre, string detalle) {
	bool insertado = false;
	ElementoAVL nuevoDato = { id, nombre, detalle };
	raiz = insertarNodo(raiz, nuevoDato, insertado);
	if (insertado) {
		cantidad++;
	}
	return insertado;
}

bool ArbolAVL::eliminar(int id) {
	bool eliminado = false;
	raiz = eliminarNodo(raiz, id, eliminado);
	if (eliminado) {
		cantidad--;
	}
	return eliminado;
}

bool ArbolAVL::buscar(int id, ElementoAVL& resultado) const {
	NodoAVL* encontrado = buscarNodo(raiz, id);
	if (encontrado == nullptr) {
		return false;
	}
	resultado = encontrado->dato;
	return true;
}

bool ArbolAVL::agregarReserva(int id, string nombre, int idReserva, string vuelos) {
	insertar(id, nombre, "");
	NodoAVL* nodo = buscarNodo(raiz, id);
	if (nodo == nullptr) {
		return false;
	}
	NodoReserva* nueva = new NodoReserva{ idReserva, vuelos, nullptr };
	if (nodo->reservas == nullptr) {
		nodo->reservas = nueva;
		return true;
	}
	NodoReserva* actual = nodo->reservas;
	while (actual->siguiente != nullptr) {
		actual = actual->siguiente;
	}
	actual->siguiente = nueva;
	return true;
}

bool ArbolAVL::quitarReserva(int id, int idReserva) {
	NodoAVL* nodo = buscarNodo(raiz, id);
	if (nodo == nullptr) {
		return false;
	}
	NodoReserva* anterior = nullptr;
	NodoReserva* actual = nodo->reservas;
	while (actual != nullptr && actual->idReserva != idReserva) {
		anterior = actual;
		actual = actual->siguiente;
	}
	if (actual == nullptr) {
		return false;
	}
	if (anterior == nullptr) {
		nodo->reservas = actual->siguiente;
	} else {
		anterior->siguiente = actual->siguiente;
	}
	delete actual;
	if (nodo->reservas == nullptr) {
		eliminar(id);
	}
	return true;
}

bool ArbolAVL::estaEnVuelo(int id, string codigoVuelo) const {
	NodoAVL* nodo = buscarNodo(raiz, id);
	if (nodo == nullptr) {
		return false;
	}
	for (NodoReserva* actual = nodo->reservas; actual != nullptr; actual = actual->siguiente) {
		if (Texto::listaContiene(actual->vuelos, codigoVuelo)) {
			return true;
		}
	}
	return false;
}

string ArbolAVL::reservasDe(int id) const {
	string texto = "";
	NodoAVL* nodo = buscarNodo(raiz, id);
	if (nodo == nullptr) {
		return texto;
	}
	for (NodoReserva* actual = nodo->reservas; actual != nullptr; actual = actual->siguiente) {
		if (!texto.empty()) {
			texto += "  ";
		}
		texto += "#" + to_string(actual->idReserva) + " (" + actual->vuelos + ")";
	}
	return texto;
}

int ArbolAVL::tamanio() const {
	return cantidad;
}

void ArbolAVL::limpiar() {
	liberarSubarbol(raiz);
	raiz = nullptr;
	cantidad = 0;
}

void ArbolAVL::recPreorden(NodoAVL* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += to_string(nodo->dato.id) + ":" + nodo->dato.nombre;
	recPreorden(nodo->izq, texto);
	recPreorden(nodo->der, texto);
}

void ArbolAVL::recInorden(NodoAVL* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	recInorden(nodo->izq, texto);
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += to_string(nodo->dato.id) + ":" + nodo->dato.nombre;
	recInorden(nodo->der, texto);
}

void ArbolAVL::recPostorden(NodoAVL* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	recPostorden(nodo->izq, texto);
	recPostorden(nodo->der, texto);
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += to_string(nodo->dato.id) + ":" + nodo->dato.nombre;
}

string ArbolAVL::preorden() const {
	string texto = "";
	recPreorden(raiz, texto);
	return texto;
}

string ArbolAVL::inorden() const {
	string texto = "";
	recInorden(raiz, texto);
	return texto;
}

string ArbolAVL::postorden() const {
	string texto = "";
	recPostorden(raiz, texto);
	return texto;
}

string ArbolAVL::anchura() const {
	if (raiz == nullptr) {
		return "";
	}
	string texto = "";
	NodoAVL* listaNodos[MAX_NODOS_AVL];
	int totalGuardados = 0;
	
	Cola colaIndices;
	listaNodos[0] = raiz;
	totalGuardados = 1;
	colaIndices.encolar(0);
	
	while (!colaIndices.estaVacia()) {
		int indiceActual = colaIndices.desencolar();
		NodoAVL* nodoActual = listaNodos[indiceActual];
		if (!texto.empty()) {
			texto += " -> ";
		}
		texto += to_string(nodoActual->dato.id) + ":" + nodoActual->dato.nombre;
		
		if (nodoActual->izq != nullptr && totalGuardados < MAX_NODOS_AVL) {
			listaNodos[totalGuardados] = nodoActual->izq;
			colaIndices.encolar(totalGuardados);
			totalGuardados++;
		}
		if (nodoActual->der != nullptr && totalGuardados < MAX_NODOS_AVL) {
			listaNodos[totalGuardados] = nodoActual->der;
			colaIndices.encolar(totalGuardados);
			totalGuardados++;
		}
	}
	return texto;
}

int ArbolAVL::exportarNodoVisual(NodoAVL* nodo, NodoVisual listaVisual[], int& cantidadActual, int maxNodos) const {
	if (nodo == nullptr || cantidadActual >= maxNodos) {
		return -1;
	}
	int miIndice = cantidadActual;
	cantidadActual++;
	
	listaVisual[miIndice].etiqueta = to_string(nodo->dato.id) + " (" + nodo->dato.nombre + ")";
	listaVisual[miIndice].factorEquilibrio = obtenerFactorEquilibrio(nodo);
	listaVisual[miIndice].izq = exportarNodoVisual(nodo->izq, listaVisual, cantidadActual, maxNodos);
	listaVisual[miIndice].der = exportarNodoVisual(nodo->der, listaVisual, cantidadActual, maxNodos);
	return miIndice;
}

int ArbolAVL::exportarVisual(NodoVisual listaVisual[], int maxNodos, int& indiceRaiz) const {
	int cantidadActual = 0;
	indiceRaiz = exportarNodoVisual(raiz, listaVisual, cantidadActual, maxNodos);
	return cantidadActual;
}
