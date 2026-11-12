#ifndef DIBUJO_H
#define DIBUJO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Constantes.h"

using namespace std;

class Dibujo {
private:
	static sf::Font fuentePrincipal;
	static bool fuenteCargada;
	
public:
	static const sf::Color COLOR_FONDO;
	static const sf::Color COLOR_PANEL;
	static const sf::Color COLOR_BORDE;
	static const sf::Color COLOR_TEXTO_TITULO;
	static const sf::Color COLOR_TEXTO_CUERPO;
	static const sf::Color COLOR_TEXTO_MUTED;
	static const sf::Color COLOR_CIAN_ACENTO;
	static const sf::Color COLOR_NARANJA_EQUIPAJE;
	static const sf::Color COLOR_VERDE_EXITO;
	static const sf::Color COLOR_ROJO_ALERTA;
	
	static bool inicializarFuente();
	static const sf::Font& getFuente();
	

	static void dibujarPanel(sf::RenderWindow& ventana, float x, float y, float ancho, float alto, 
							 sf::Color fondo, sf::Color borde = sf::Color::Transparent, float grosorBorde = 1.0f);
	
	static void dibujarTexto(sf::RenderWindow& ventana, const string& texto, float x, float y, 
							 unsigned int tam, sf::Color color, bool centrado = false);

	static void dibujarVerticeCiudad(sf::RenderWindow& ventana, const Ciudad& ciudad, 
									 bool seleccionada = false, bool hover = false);
	
	static void dibujarFlechaDirigida(sf::RenderWindow& ventana, float x1, float y1, float x2, float y2, 
									  sf::Color color, float grosor = 2.0f, const string& etiqueta = "",
									  float radioNodo = 16.0f);
};

#endif
