#ifndef ARBOLABB_H
#define ARBOLABB_H
#include "Constantes.h"
struct ElementoABB {
	string codigo;
	string nombre;
};
struct NodoABB {
	ElementoABB dato;
	NodoABB* izq;
	NodoABB* der;
};
class ArbolABB {
private:
	NodoABB* raiz;
	int cantidad;
	
	NodoABB* insertarNodo(NodoABB* nodo, const ElementoABB& dato, bool& insertado);
	NodoABB* buscarNodo(NodoABB* nodo, const string& texto) const;
	void liberarSubarbol(NodoABB* nodo);
	void recPreorden(NodoABB* nodo, string& texto) const;
	void recInorden(NodoABB* nodo, string& texto) const;
	void recPostorden(NodoABB* nodo, string& texto) const;
	int exportarNodoVisual(NodoABB* nodo, NodoVisual listaVisual[], int& cantidadActual, int maxNodos) const;
	
public:
	ArbolABB();
	~ArbolABB();
	
	bool insertar(string codigo, string nombre);
	bool buscar(string nombreOCodigo, ElementoABB& resultado) const;
	bool contiene(string nombreOCodigo) const;
	int tamanio() const;
	void limpiar();
	
	string preorden() const;
	string inorden() const;
	string postorden() const;
	string anchura() const;
	string porNiveles() const;
	
	int exportarVisual(NodoVisual listaVisual[], int maxNodos, int& indiceRaiz) const;
	
	ArbolABB(const ArbolABB&) = delete;
	ArbolABB& operator=(const ArbolABB&) = delete;
};
#endif
