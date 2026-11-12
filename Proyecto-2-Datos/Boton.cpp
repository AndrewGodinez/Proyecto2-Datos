#include "Boton.h"

Boton::Boton() {
	limites = sf::FloatRect(0, 0, 100, 30);
	texto = "";
	colorNormal = Dibujo::COLOR_PANEL;
	colorHover = sf::Color(38, 52, 78);
	colorTexto = Dibujo::COLOR_TEXTO_TITULO;
	hover = false;
	activo = false;
}

Boton::Boton(float x, float y, float ancho, float alto, const string& texto,
			 sf::Color colorNormal, sf::Color colorHover, sf::Color colorTexto) {
	this->limites = sf::FloatRect(x, y, ancho, alto);
	this->texto = texto;
	this->colorNormal = colorNormal;
	this->colorHover = colorHover;
	this->colorTexto = colorTexto;
	this->hover = false;
	this->activo = false;
}

void Boton::actualizar(sf::Vector2f posMouse) {
	hover = limites.contains(posMouse);
}

bool Boton::fueClickeado(const sf::Event& evento) const {
	if (evento.type == sf::Event::MouseButtonReleased && evento.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f punto(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
		return limites.contains(punto);
	}
	return false;
}

void Boton::dibujar(sf::RenderWindow& ventana) const {
	sf::Color fondo = colorNormal;
	sf::Color borde = Dibujo::COLOR_BORDE;
	
	if (activo) {
		fondo = Dibujo::COLOR_CIAN_ACENTO;
		borde = sf::Color::White;
	} else if (hover) {
		fondo = colorHover;
		borde = Dibujo::COLOR_CIAN_ACENTO;
	}
	
	Dibujo::dibujarPanel(ventana, limites.left, limites.top, limites.width, limites.height, fondo, borde, 1.5f);
	
	sf::Color colorLabel = (activo) ? sf::Color(10, 15, 26) : colorTexto;
	float centroX = limites.left + limites.width / 2.0f;
	float centroY = limites.top + limites.height / 2.0f;
	Dibujo::dibujarTexto(ventana, texto, centroX, centroY, 13, colorLabel, true);
}

void Boton::setActivo(bool valor) {
	activo = valor;
}

bool Boton::getActivo() const {
	return activo;
}

void Boton::setTexto(const string& nuevoTexto) {
	texto = nuevoTexto;
}

string Boton::getTexto() const {
	return texto;
}

void Boton::setPosicion(float x, float y) {
	limites.left = x;
	limites.top = y;
}
