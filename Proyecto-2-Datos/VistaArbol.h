#ifndef VISTAARBOL_H
#define VISTAARBOL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"

using namespace std;

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
	
	void calcularPosiciones(int idx, float xMin, float xMax, float y, float separacionY);
	void dibujarConectores(sf::RenderWindow& ventana) const;
	void dibujarNodos(sf::RenderWindow& ventana, int nodoResaltado) const;
	
public:
	VistaArbol();
	VistaArbol(float x, float y, float ancho, float alto);
	
	void cargarArbol(const NodoVisual listaNodos[], int cantidad, int indiceRaiz, 
					 const string& tituloArbol, bool esArbolAVL = false);
	void limpiar();
	
	void dibujar(sf::RenderWindow& ventana, int nodoResaltado = -1) const;
	
	int getTotalNodos() const;
	bool estaVacio() const;
};

#endif
