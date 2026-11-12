#ifndef BOTON_H
#define BOTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Dibujo.h"
using namespace std;
class Boton {
private:
	sf::FloatRect limites;
	string texto;
	sf::Color colorNormal;
	sf::Color colorHover;
	sf::Color colorTexto;
	bool hover;
	bool activo;
public:
	Boton();
	Boton(float x, float y, float ancho, float alto, const string& texto,
		  sf::Color colorNormal = Dibujo::COLOR_PANEL, 
		  sf::Color colorHover = sf::Color(38, 52, 78), 
		  sf::Color colorTexto = Dibujo::COLOR_TEXTO_TITULO);
	void actualizar(sf::Vector2f posMouse);
	bool fueClickeado(const sf::Event& evento) const;
	void dibujar(sf::RenderWindow& ventana) const;
	void setActivo(bool valor);
	bool getActivo() const;
	void setTexto(const string& nuevoTexto);
	string getTexto() const;
	void setPosicion(float x, float y);
};
#endif
