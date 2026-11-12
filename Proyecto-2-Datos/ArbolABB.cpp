#include "ArbolABB.h"
#include "Cola.h"
#include "Texto.h"

static const int MAX_NODOS_ABB = 256;

ArbolABB::ArbolABB() {
	raiz = nullptr;
	cantidad = 0;
}

ArbolABB::~ArbolABB() {
	limpiar();
}

void ArbolABB::liberarSubarbol(NodoABB* nodo) {
	if (nodo != nullptr) {
		liberarSubarbol(nodo->izq);
		liberarSubarbol(nodo->der);
		delete nodo;
	}
}

void ArbolABB::limpiar() {
	liberarSubarbol(raiz);
	raiz = nullptr;
	cantidad = 0;
}

int ArbolABB::tamanio() const {
	return cantidad;
}


NodoABB* ArbolABB::insertarNodo(NodoABB* nodo, const ElementoABB& dato, bool& insertado) {
	if (nodo == nullptr) {
		insertado = true;
		NodoABB* nuevo = new NodoABB{ dato, nullptr, nullptr };
		return nuevo;
	}
	
	string clave = Texto::minusculas(dato.nombre);
	string claveNodo = Texto::minusculas(nodo->dato.nombre);
	if (clave < claveNodo) {
		nodo->izq = insertarNodo(nodo->izq, dato, insertado);
	} else if (clave > claveNodo) {
		nodo->der = insertarNodo(nodo->der, dato, insertado);
	} else {
		insertado = false; 
	}
	return nodo;
}

bool ArbolABB::insertar(string codigo, string nombre) {
	bool insertado = false;
	ElementoABB dato = { codigo, nombre };
	raiz = insertarNodo(raiz, dato, insertado);
	if (insertado) {
		cantidad++;
	}
	return insertado;
}


NodoABB* ArbolABB::buscarNodo(NodoABB* nodo, const string& texto) const {
	if (nodo == nullptr) {
		return nullptr;
	}
	string clave = Texto::minusculas(texto);
	string claveNodo = Texto::minusculas(nodo->dato.nombre);
	if (clave == claveNodo) {
		return nodo;
	}
	if (clave < claveNodo) {
		return buscarNodo(nodo->izq, texto);
	}
	return buscarNodo(nodo->der, texto);
}

bool ArbolABB::buscar(string nombreOCodigo, ElementoABB& resultado) const {
	NodoABB* nodo = buscarNodo(raiz, nombreOCodigo);
	if (nodo != nullptr) {
		resultado = nodo->dato;
		return true;
	}
	return false;
}

bool ArbolABB::contiene(string nombreOCodigo) const {
	return buscarNodo(raiz, nombreOCodigo) != nullptr;
}

void ArbolABB::recPreorden(NodoABB* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += nodo->dato.codigo + " (" + nodo->dato.nombre + ")";
	recPreorden(nodo->izq, texto);
	recPreorden(nodo->der, texto);
}

void ArbolABB::recInorden(NodoABB* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	recInorden(nodo->izq, texto);
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += nodo->dato.codigo + " (" + nodo->dato.nombre + ")";
	recInorden(nodo->der, texto);
}

void ArbolABB::recPostorden(NodoABB* nodo, string& texto) const {
	if (nodo == nullptr) {
		return;
	}
	recPostorden(nodo->izq, texto);
	recPostorden(nodo->der, texto);
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += nodo->dato.codigo + " (" + nodo->dato.nombre + ")";
}

string ArbolABB::preorden() const {
	string texto = "";
	recPreorden(raiz, texto);
	return texto;
}

string ArbolABB::inorden() const {
	string texto = "";
	recInorden(raiz, texto);
	return texto;
}

string ArbolABB::postorden() const {
	string texto = "";
	recPostorden(raiz, texto);
	return texto;
}

string ArbolABB::anchura() const {
	if (raiz == nullptr) {
		return "";
	}
	string texto = "";
	NodoABB* listaNodos[MAX_NODOS_ABB];
	int totalGuardados = 0;
	
	Cola colaIndices;
	listaNodos[0] = raiz;
	totalGuardados = 1;
	colaIndices.encolar(0);
	
	while (!colaIndices.estaVacia()) {
		int indiceActual = colaIndices.desencolar();
		NodoABB* actual = listaNodos[indiceActual];
		
		if (!texto.empty()) {
			texto += " -> ";
		}
		texto += actual->dato.codigo + " (" + actual->dato.nombre + ")";
		
		if (actual->izq != nullptr && totalGuardados < MAX_NODOS_ABB) {
			listaNodos[totalGuardados] = actual->izq;
			colaIndices.encolar(totalGuardados);
			totalGuardados++;
		}
		if (actual->der != nullptr && totalGuardados < MAX_NODOS_ABB) {
			listaNodos[totalGuardados] = actual->der;
			colaIndices.encolar(totalGuardados);
			totalGuardados++;
		}
	}
	return texto;
}

string ArbolABB::porNiveles() const {
	return anchura();
}

int ArbolABB::exportarNodoVisual(NodoABB* nodo, NodoVisual listaVisual[], int& cantidadActual, int maxNodos) const {
	if (nodo == nullptr || cantidadActual >= maxNodos) {
		return -1;
	}
	int miIndice = cantidadActual;
	cantidadActual++;
	
	listaVisual[miIndice].etiqueta = nodo->dato.codigo + " (" + nodo->dato.nombre + ")";
	listaVisual[miIndice].factorEquilibrio = 0;
	listaVisual[miIndice].izq = exportarNodoVisual(nodo->izq, listaVisual, cantidadActual, maxNodos);
	listaVisual[miIndice].der = exportarNodoVisual(nodo->der, listaVisual, cantidadActual, maxNodos);
	return miIndice;
}

int ArbolABB::exportarVisual(NodoVisual listaVisual[], int maxNodos, int& indiceRaiz) const {
	int cantidadActual = 0;
	indiceRaiz = exportarNodoVisual(raiz, listaVisual, cantidadActual, maxNodos);
	return cantidadActual;
}
