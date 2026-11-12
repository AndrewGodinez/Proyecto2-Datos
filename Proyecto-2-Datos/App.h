#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include "Constantes.h"
#include "Aerolinea.h"
#include "VistaMapa.h"
#include "VistaArbol.h"
#include "Animacion.h"
#include "Boton.h"
#include "CajaTexto.h"

enum PestanaSistema {
	PESTANA_DIJKSTRA = 0,
	PESTANA_BELLMAN_FORD,
	PESTANA_ABB_CIUDADES,
	PESTANA_RESERVA_VUELO,
	PESTANA_FLOTA_ADMIN,
	PESTANA_AVL_PASAJEROS,
	PESTANA_MST_EXPANSION,
	PESTANA_EQUIPAJE_COMPARATIVA,
	TOTAL_PESTANAS
};

class PantallasCliente;
class PantallasAdmin;

class App {
private:
	sf::RenderWindow ventana;
	Aerolinea& sistema;
	VistaMapa vistaMapa;
	VistaArbol vistaArbol;
	Animacion animacion;
	sf::Clock relojFrame;
	
	PestanaSistema pestanaActual;
	Boton botonesMenu[TOTAL_PESTANAS];
	Boton btnGuardarDatos;
	bool mostrarVistaArbol;
	
	PantallasCliente* pantallasCliente;
	PantallasAdmin* pantallasAdmin;
	
	void inicializarMenuLateral();
	void dibujarBarraSuperior();
	void dibujarMenuLateral();
	
public:
	App(Aerolinea& aerolinea);
	~App();
	void ejecutar();
	void procesarEventos();
	void actualizar(float dt);
	void dibujar();
	
	void cambiarPestana(PestanaSistema nuevaPestana);
	PestanaSistema getPestanaActual() const;
	VistaMapa& getVistaMapa();
	VistaArbol& getVistaArbol();
	Animacion& getAnimacion();
	Aerolinea& getSistema();
	sf::RenderWindow& getVentana();
	
	bool getMostrarVistaArbol() const { return mostrarVistaArbol; }
	void setMostrarVistaArbol(bool mostrar) { mostrarVistaArbol = mostrar; }
};

#endif
