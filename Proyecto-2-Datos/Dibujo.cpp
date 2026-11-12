#include "Dibujo.h"
#include "Grafo.h"
#include <cmath>

sf::Font Dibujo::fuentePrincipal;
bool Dibujo::fuenteCargada = false;

const sf::Color Dibujo::COLOR_FONDO          = sf::Color(15, 20, 32);
const sf::Color Dibujo::COLOR_PANEL          = sf::Color(24, 32, 48);
const sf::Color Dibujo::COLOR_BORDE          = sf::Color(45, 58, 82);
const sf::Color Dibujo::COLOR_TEXTO_TITULO   = sf::Color(255, 255, 255);
const sf::Color Dibujo::COLOR_TEXTO_CUERPO   = sf::Color(220, 228, 240);
const sf::Color Dibujo::COLOR_TEXTO_MUTED    = sf::Color(140, 155, 180);
const sf::Color Dibujo::COLOR_CIAN_ACENTO    = sf::Color(56, 189, 248);
const sf::Color Dibujo::COLOR_NARANJA_EQUIPAJE = sf::Color(251, 146, 60);
const sf::Color Dibujo::COLOR_VERDE_EXITO    = sf::Color(34, 197, 94);
const sf::Color Dibujo::COLOR_ROJO_ALERTA    = sf::Color(239, 68, 68);

bool Dibujo::inicializarFuente() {
	if (fuenteCargada) {
		return true;
	}

	const string rutas[] = {
		"arial.ttf",
		"C:/Windows/Fonts/arial.ttf",
		"C:/Windows/Fonts/segoeui.ttf",
		"C:/Windows/Fonts/tahoma.ttf"
	};
	for (int i = 0; i < 4; i++) {
		if (fuentePrincipal.loadFromFile(rutas[i])) {
			fuenteCargada = true;
			return true;
		}
	}
	return false;
}

const sf::Font& Dibujo::getFuente() {
	if (!fuenteCargada) {
		inicializarFuente();
	}
	return fuentePrincipal;
}

sf::Vector2f Dibujo::proyectarCiudad(const Ciudad& ciudad, const Grafo& grafo) {
	int total = grafo.getCantidadCiudades();
	if (total <= 0) {
		return sf::Vector2f(ciudad.posX, ciudad.posY);
	}
	if (total == 1) {
		return sf::Vector2f(760.0f, 290.0f);
	}
	
	float minX = 999999.0f, maxX = -999999.0f;
	float minY = 999999.0f, maxY = -999999.0f;
	for (int i = 0; i < total; i++) {
		Ciudad c = grafo.getCiudad(i);
		if (c.posX < minX) minX = c.posX;
		if (c.posX > maxX) maxX = c.posX;
		if (c.posY < minY) minY = c.posY;
		if (c.posY > maxY) maxY = c.posY;
	}
	
	float spanX = maxX - minX;
	float spanY = maxY - minY;
	
	float normX = (spanX > 0.001f) ? ((ciudad.posX - minX) / spanX) : 0.5f;
	float normY = (spanY > 0.001f) ? ((ciudad.posY - minY) / spanY) : 0.5f;
	
	// Canvas bounds: margen horizontal [320, 1205], margen vertical [105, 480]
	// Evita colisiones con barra lateral (0-250) y panel inferior (535-715)
	float px = 320.0f + normX * 885.0f;
	float py = 105.0f + normY * 375.0f;
	
	return sf::Vector2f(px, py);
}

void Dibujo::dibujarPanel(sf::RenderWindow& ventana, float x, float y, float ancho, float alto, 
						  sf::Color fondo, sf::Color borde, float grosorBorde) {
	sf::RectangleShape panel(sf::Vector2f(ancho, alto));
	panel.setPosition(x, y);
	panel.setFillColor(fondo);
	if (borde != sf::Color::Transparent && grosorBorde > 0.0f) {
		panel.setOutlineColor(borde);
		panel.setOutlineThickness(grosorBorde);
	}
	ventana.draw(panel);
}

void Dibujo::dibujarTexto(sf::RenderWindow& ventana, const string& texto, float x, float y, 
						  unsigned int tam, sf::Color color, bool centrado) {
	if (!inicializarFuente()) return;
	sf::Text txt;
	txt.setFont(getFuente());
	txt.setString(sf::String::fromUtf8(texto.begin(), texto.end()));
	txt.setCharacterSize(tam);
	txt.setFillColor(color);
	
	if (centrado) {
		sf::FloatRect bounds = txt.getLocalBounds();
		txt.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	}
	txt.setPosition(x, y);
	ventana.draw(txt);
}

void Dibujo::dibujarVerticeCiudad(sf::RenderWindow& ventana, const Ciudad& ciudad, 
								  sf::Vector2f pos, bool seleccionada, bool hover) {
	float radio = 16.0f;
	sf::CircleShape circulo(radio);
	circulo.setOrigin(radio, radio);
	circulo.setPosition(pos.x, pos.y);
	
	if (seleccionada) {
		circulo.setFillColor(COLOR_CIAN_ACENTO);
		circulo.setOutlineColor(sf::Color::White);
		circulo.setOutlineThickness(3.0f);
	} else if (hover) {
		circulo.setFillColor(sf::Color(38, 52, 78));
		circulo.setOutlineColor(COLOR_CIAN_ACENTO);
		circulo.setOutlineThickness(2.0f);
	} else {
		circulo.setFillColor(COLOR_PANEL);
		circulo.setOutlineColor(COLOR_BORDE);
		circulo.setOutlineThickness(2.0f);
	}
	ventana.draw(circulo);
	
	sf::Color colorTexto = seleccionada ? sf::Color(10, 15, 26) : COLOR_TEXTO_TITULO;
	dibujarTexto(ventana, ciudad.codigo, pos.x, pos.y, 11, colorTexto, true);
	dibujarTexto(ventana, ciudad.nombre, pos.x, pos.y + radio + 3.0f, 10, COLOR_TEXTO_MUTED, true);
}

void Dibujo::dibujarVerticeCiudad(sf::RenderWindow& ventana, const Ciudad& ciudad, 
								  bool seleccionada, bool hover) {
	dibujarVerticeCiudad(ventana, ciudad, sf::Vector2f(ciudad.posX, ciudad.posY), seleccionada, hover);
}

void Dibujo::dibujarFlechaDirigida(sf::RenderWindow& ventana, float x1, float y1, float x2, float y2, 
								   sf::Color color, float grosor, const string& etiqueta, float radioNodo) {
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dist = std::sqrt(dx * dx + dy * dy);
	if (dist < radioNodo * 2.0f) {
		return;
	}
	
	float ux = dx / dist;
	float uy = dy / dist;
	const float PI = 3.14159265f;
	float anguloGrados = std::atan2(dy, dx) * 180.0f / PI;
	
	float startX = x1 + ux * radioNodo;
	float startY = y1 + uy * radioNodo;
	float endX   = x2 - ux * radioNodo;
	float endY   = y2 - uy * radioNodo;
	float longSegmento = dist - (radioNodo * 2.0f);
	
	sf::RectangleShape linea(sf::Vector2f(longSegmento, grosor));
	linea.setOrigin(0.0f, grosor / 2.0f);
	linea.setPosition(startX, startY);
	linea.setRotation(anguloGrados);
	linea.setFillColor(color);
	ventana.draw(linea);
	
	float tamPunta = 10.0f;
	sf::ConvexShape punta(3);
	punta.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	punta.setPoint(1, sf::Vector2f(-tamPunta, -tamPunta * 0.55f));
	punta.setPoint(2, sf::Vector2f(-tamPunta,  tamPunta * 0.55f));
	punta.setPosition(endX, endY);
	punta.setRotation(anguloGrados);
	punta.setFillColor(color);
	ventana.draw(punta);
	
	if (!etiqueta.empty()) {
		float midX = (startX + endX) * 0.5f;
		float midY = (startY + endY) * 0.5f - 10.0f;
		dibujarTexto(ventana, etiqueta, midX, midY, 11, color, true);
	}
}
