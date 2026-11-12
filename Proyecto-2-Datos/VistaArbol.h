#ifndef VISTAARBOL_H
#define VISTAARBOL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"

using namespace std;

enum TipoRecorrido {
	RECORRIDO_PREORDEN,
	RECORRIDO_INORDEN,
	RECORRIDO_POSTORDEN,
	RECORRIDO_NIVELES
};

struct PosicionVisual {
	float x;
	float y;
	bool calculada;
};

class VistaArbol {
private:
	sf::FloatRect area;
	NodoVisual nodos[MAX_CIUDADES * 2];
	PosicionVisual posiciones[MAX_CIUDADES * 2];
	int totalNodos;
	int raiz;
	string titulo;
	bool esAVL;
	bool esGeneral;
	
	int contarNiveles(int idx) const;
	int contarHojas(int idx) const;
	void posicionarBinario(int idx, int profundidad, int& columna, float separacionY);
	void posicionarGeneral(int idx, float xMin, float xMax, float y, float separacionY);
	void ordenRecursivo(int idx, int recorrido, int orden[], int& cantidad) const;
	void dibujarConectores(sf::RenderWindow& ventana) const;
	void dibujarNodos(sf::RenderWindow& ventana, int nodoResaltado) const;
	
public:
	VistaArbol();
	VistaArbol(float x, float y, float ancho, float alto);
	
	void cargarArbol(const NodoVisual listaNodos[], int cantidad, int indiceRaiz, 
					 const string& tituloArbol, bool esArbolAVL = false, bool esArbolGeneral = false);
	int calcularOrden(int recorrido, int orden[]) const;
	void limpiar();
	
	void dibujar(sf::RenderWindow& ventana, int nodoResaltado = -1) const;
	
	int getTotalNodos() const;
	bool estaVacio() const;
};

#endif
