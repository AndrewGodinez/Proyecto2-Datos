#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"
#include "Grafo.h"

using namespace std;

struct AvionAnimado {
	bool activo;
	bool finalizado;
	int nodos[MAX_CIUDADES];
	int cantidadNodos;
	int tramoActual;      
	float progresoTramo;  
	float velocidad;      
	sf::Vector2f posActual;
	float angulo;         
	sf::Color color;
	string etiqueta;
};

class Animacion {
private:
	AvionAnimado avionPasajero;
	AvionAnimado avionEquipaje;
	bool animandoRutas;
	bool pausado;
	
	bool animandoArbol;
	int totalNodosArbol;
	int nodoActivoArbol;
	float tiempoPasoArbol;
	float acumuladorTiempoArbol;
	
	void actualizarAvion(AvionAnimado& avion, float dt, const Grafo& grafo);
	void dibujarAvion(sf::RenderWindow& ventana, const AvionAnimado& avion) const;
	
public:
	Animacion();
	
	void iniciarVuelo(const ResultadoRuta& rutaPasajero, const ResultadoRuta& rutaEquipaje, const Grafo& grafo);
	void detener();
	void alternarPausa();
	
	void iniciarRecorridoArbol(int cantidadNodos, float intervaloSegundos = 0.5f);
	void detenerRecorridoArbol();
	int getNodoActivoArbol() const;
	bool getAnimandoArbol() const;
	
	void actualizar(float dt, const Grafo& grafo);
	void dibujar(sf::RenderWindow& ventana) const;
	
	bool estaActiva() const;
	bool estaPausada() const;
};

#endif
