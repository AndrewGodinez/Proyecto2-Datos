#ifndef CAJATEXTO_H
#define CAJATEXTO_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Dibujo.h"

using namespace std;

class CajaTexto {
private:
	sf::FloatRect limites;
	string texto;
	string placeholder;
	bool tieneFoco;
	int maxCaracteres;
	sf::Clock relojCursor;
	
public:
	CajaTexto();
	CajaTexto(float x, float y, float ancho, float alto, 
			  const string& placeholder = "", int maxCaracteres = 28);
	
	void procesarEvento(const sf::Event& evento);
	void dibujar(sf::RenderWindow& ventana);
	
	string getTexto() const;
	void setTexto(const string& nuevoTexto);
	void limpiar();
	bool getTieneFoco() const;
	void setFoco(bool foco);
};

#endif
