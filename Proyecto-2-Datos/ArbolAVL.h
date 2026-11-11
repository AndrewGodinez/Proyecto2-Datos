#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include "Constantes.h"

struct ElementoAVL {
	int id;
	string nombre;
	string detalle;
};

struct NodoAVL {
	ElementoAVL dato;
	int altura;
	NodoAVL* izq;
	NodoAVL* der;
};

class ArbolAVL {
private:
	NodoAVL* raiz;
	int cantidad;
	
	int maximo(int valorA, int valorB) const;
	int obtenerAltura(NodoAVL* nodo) const;
	int obtenerFactorEquilibrio(NodoAVL* nodo) const;
	void actualizarAltura(NodoAVL* nodo);
	NodoAVL* rotarDerecha(NodoAVL* nodoDesbalanceado);
	NodoAVL* rotarIzquierda(NodoAVL* nodoDesbalanceado);
	NodoAVL* balancear(NodoAVL* nodo);
	NodoAVL* insertarNodo(NodoAVL* nodo, const ElementoAVL& nuevoDato, bool& insertado);
	NodoAVL* obtenerMinimo(NodoAVL* nodo) const;
	NodoAVL* eliminarNodo(NodoAVL* nodo, int id, bool& eliminado);
	NodoAVL* buscarNodo(NodoAVL* nodo, int id) const;
	void liberarSubarbol(NodoAVL* nodo);
	void recPreorden(NodoAVL* nodo, string& texto) const;
	void recInorden(NodoAVL* nodo, string& texto) const;
	void recPostorden(NodoAVL* nodo, string& texto) const;
	int exportarNodoVisual(NodoAVL* nodo, NodoVisual listaVisual[], int& cantidadActual, int maxNodos) const;
	
public:
	ArbolAVL();
	~ArbolAVL();
	
	bool insertar(int id, string nombre, string detalle);
	bool eliminar(int id);
	bool buscar(int id, ElementoAVL& resultado) const;
	int tamanio() const;
	void limpiar();
	
	string preorden() const;
	string inorden() const;
	string postorden() const;
	string anchura() const;
	int exportarVisual(NodoVisual listaVisual[], int maxNodos, int& indiceRaiz) const;
};

#endif
