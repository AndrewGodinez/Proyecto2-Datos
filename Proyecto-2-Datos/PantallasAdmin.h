#ifndef PANTALLASADMIN_H
#define PANTALLASADMIN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"
#include "Boton.h"
#include "CajaTexto.h"
#include "PrimKruskal.h"

using namespace std;

class App;

class PantallasAdmin {
private:
	Boton btnFlotaPrev;
	Boton btnFlotaNext;
	int flotaPagina;
	string textoInfoFlota;
	
	CajaTexto txtBuscarPasajero;
	Boton btnBuscarPasajero;
	Boton btnVerArbolAVL;
	Boton btnPreordenAVL;
	Boton btnInordenAVL;
	Boton btnPostordenAVL;
	Boton btnNivelesAVL;
	string textoResultadoAVL;
	string textoRecorridoAVL;
	
	Boton btnPrimCosto;
	Boton btnKruskalTiempo;
	Boton btnLimpiarMST;
	Boton btnMSTPreorden;
	Boton btnMSTInorden;
	Boton btnMSTPostorden;
	Boton btnMSTNiveles;
	ResultadoMST ultimoMST;
	bool mstCalculado;
	string textoInfoMST;
	string textoRecorridoMST;
	
	Boton btnCompararEquipaje;
	Boton btnAnimarEquipaje;
	ResultadoRuta compPasajero;
	ResultadoRuta compEquipaje;
	string textoInfoEquipaje;
	string textoComparativa;
	string textoAhorro;
	
	void inicializarControles();
	string formatearRuta(const Grafo& grafo, const ResultadoRuta& ruta) const;
	
	void procesarFlota(const sf::Event& evento, App& app);
	void procesarAVL(const sf::Event& evento, App& app);
	void procesarMST(const sf::Event& evento, App& app);
	void procesarEquipaje(const sf::Event& evento, App& app);
	
	void dibujarPantallaFlota(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaAVL(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaMST(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaEquipaje(sf::RenderWindow& ventana, App& app);
	
public:
	PantallasAdmin();
	void procesarEvento(const sf::Event& evento, App& app);
	void actualizar(sf::Vector2f posMouse, App& app);
	void dibujar(sf::RenderWindow& ventana, App& app);
};

#endif
