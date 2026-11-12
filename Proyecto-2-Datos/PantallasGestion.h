#ifndef PANTALLASGESTION_H
#define PANTALLASGESTION_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"
#include "Boton.h"
#include "CajaTexto.h"

using namespace std;

class App;

class PantallasGestion {
private:
	CajaTexto txtCodigoAeronave;
	CajaTexto txtPlaca;
	CajaTexto txtMarca;
	CajaTexto txtModelo;
	CajaTexto txtCapacidad;
	Boton btnRegistrarAeronave;
	CajaTexto txtIdTripulante;
	CajaTexto txtNombreTripulante;
	CajaTexto txtRol;
	Boton btnRegistrarTripulante;
	CajaTexto txtAeronaveAsignar;
	Boton btnAsignar;
	Boton btnFlotaPrev;
	Boton btnFlotaNext;
	int flotaPagina;
	string textoFlota;

	CajaTexto txtCodigoCiudad;
	CajaTexto txtNombreCiudad;
	Boton btnAgregarCiudad;
	CajaTexto txtCosto;
	CajaTexto txtDuracion;
	Boton btnGuardarRuta;
	Boton btnEliminarRuta;
	string textoCiudades;

	CajaTexto txtCodigoVuelo;
	CajaTexto txtHora;
	CajaTexto txtAeronaveVuelo;
	Boton btnProgramar;
	CajaTexto txtVueloConsulta;
	Boton btnPasajeros;
	CajaTexto txtIdReserva;
	Boton btnCancelar;
	Boton btnVuelosPrev;
	Boton btnVuelosNext;
	int vuelosPagina;
	string textoVuelos;

	void inicializarControles();

	void procesarFlota(const sf::Event& evento, App& app);
	void procesarCiudades(const sf::Event& evento, App& app);
	void procesarVuelos(const sf::Event& evento, App& app);

	void dibujarPantallaFlota(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaCiudades(sf::RenderWindow& ventana, App& app);
	void dibujarPantallaVuelos(sf::RenderWindow& ventana, App& app);

public:
	PantallasGestion();
	void procesarEvento(const sf::Event& evento, App& app);
	void actualizar(sf::Vector2f posMouse, App& app);
	void dibujar(sf::RenderWindow& ventana, App& app);
};

#endif
