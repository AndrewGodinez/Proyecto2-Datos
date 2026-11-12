#ifndef PANTALLASCLIENTE_H
#define PANTALLASCLIENTE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"
#include "Boton.h"
#include "CajaTexto.h"
#include "ArbolABB.h"

using namespace std;

class App;

class PantallasCliente {
private:
	Boton btnCriterioCosto;
	Boton btnCriterioTiempo;
	Boton btnCalcularDijkstra;
	Boton btnAnimarDijkstra;
	bool dijkstraPorTiempo;
	string textoInfoDijkstra;
	string textoRutaPasajero;
	string textoRutaEquipaje;
	ResultadoRuta ultimaRutaPasajero;
	ResultadoRuta ultimaRutaEquipaje;
	
	Boton btnBFCriterio;
	Boton btnCalcularBF;
	Boton btnBFPrev;
	Boton btnBFNext;
	Boton btnAnimarBF;
	bool bfPorTiempo;
	int bfOrigen;
	int bfPaginaActual;
	int bfTotalDestinos;
	ResultadoRuta bfResultados[MAX_CIUDADES];
	string textoInfoBF;
	
	CajaTexto txtBuscarABB;
	Boton btnBuscarABB;
	Boton btnVerArbolABB;
	Boton btnPreorden;
	Boton btnInorden;
	Boton btnPostorden;
	Boton btnNiveles;
	string textoResultadoABB;
	string textoRecorridoABB;
	ArbolABB abbCiudades;
	bool abbCargado;
	
	CajaTexto txtCedula;
	CajaTexto txtNombre;
	Boton btnReservaCosto;
	Boton btnReservaTiempo;
	Boton btnVerViaje;
	bool reservaPorTiempo;
	Boton btnConfirmarReserva;
	Boton btnLimpiarReserva;
	string textoResultadoReserva;
	string textoDetalleReserva;
	
	void inicializarControles();
	void construirABB(App& app);
	string formatearRuta(const Grafo& grafo, const ResultadoRuta& ruta) const;
	
	void procesarDijkstra(const sf::Event& evento, App& app);
	void procesarBellmanFord(const sf::Event& evento, App& app);
	void procesarABB(const sf::Event& evento, App& app);
	void procesarReserva(const sf::Event& evento, App& app);
	
	void dibujarPantallaDijkstra(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaBellmanFord(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaABB(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaReserva(sf::RenderWindow& ventana, App& app);
	
public:
	PantallasCliente();
	void procesarEvento(const sf::Event& evento, App& app);
	void actualizar(sf::Vector2f posMouse, App& app);
	void dibujar(sf::RenderWindow& ventana, App& app);
};

#endif
