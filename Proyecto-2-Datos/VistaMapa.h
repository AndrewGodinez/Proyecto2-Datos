#ifndef VISTAMAPA_H
#define VISTAMAPA_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"
#include "Grafo.h"
#include "PrimKruskal.h"
#include "Animacion.h"

class VistaMapa {
private:
	sf::FloatRect area;
	int origenSeleccionado;
	int destinoSeleccionado;
	int ciudadHover;
	
	ResultadoRuta rutaPasajero;
	ResultadoRuta rutaEquipaje;
	ResultadoMST redMST;
	bool mostrarRutasAlgoritmo;
	bool mostrarMST;
	ResultadoRuta caminosBF[MAX_CIUDADES];
	int totalCaminosBF;
	bool mostrarCaminosBF;
	bool hayPuntoNuevo;
	sf::Vector2f puntoNuevo;
	
	void dibujarCaminosBF(sf::RenderWindow& ventana, const Grafo& grafo) const;
	void dibujarRutasBase(sf::RenderWindow& ventana, const Grafo& grafo) const;
	void dibujarRutasResaltadas(sf::RenderWindow& ventana, const Grafo& grafo) const;
	void dibujarRedMST(sf::RenderWindow& ventana, const Grafo& grafo) const;
	void dibujarCiudades(sf::RenderWindow& ventana, const Grafo& grafo) const;
	
public:
	VistaMapa();
	VistaMapa(float x, float y, float ancho, float alto);
	
	int procesarEvento(const sf::Event& evento, const Grafo& grafo);
	void actualizarHover(sf::Vector2f posMouse, const Grafo& grafo);
	
	void dibujar(sf::RenderWindow& ventana, const Grafo& grafo, const Animacion& animacion) const;
	
	void setRutas(const ResultadoRuta& pasajero, const ResultadoRuta& equipaje);
	void setMST(const ResultadoMST& mst);
	void setCaminosBF(const ResultadoRuta rutas[], int total);
	bool getPuntoNuevo(const Grafo& grafo, float& x, float& y) const;
	void limpiarRutas();
	
	int getOrigen() const;
	int getDestino() const;
	void setOrigen(int id);
	void setDestino(int id);
	void limpiarSeleccion();
};

#endif
