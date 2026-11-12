#include "VistaArbol.h"
#include "Dibujo.h"
#include <cmath>

VistaArbol::VistaArbol() {
	area = sf::FloatRect(260.0f, 60.0f, 1000.0f, 480.0f);
	totalNodos = 0;
	raiz = -1;
	titulo = "";
	esAVL = false;
	limpiar();
}

VistaArbol::VistaArbol(float x, float y, float ancho, float alto) {
	this->area = sf::FloatRect(x, y, ancho, alto);
	this->totalNodos = 0;
	this->raiz = -1;
	this->titulo = "";
	this->esAVL = false;
	limpiar();
}

void VistaArbol::limpiar() {
	totalNodos = 0;
	raiz = -1;
	titulo = "";
	esAVL = false;
	for (int i = 0; i < MAX_CIUDADES * 2; i++) {
		posiciones[i].x = 0.0f;
		posiciones[i].y = 0.0f;
		posiciones[i].calculada = false;
	}
}

void VistaArbol::calcularPosiciones(int idx, float xMin, float xMax, float y, float separacionY) {
	if (idx < 0 || idx >= totalNodos) return;
	
	float centroX = (xMin + xMax) / 2.0f;
	posiciones[idx].x = centroX;
	posiciones[idx].y = y;
	posiciones[idx].calculada = true;
	
	int izq = nodos[idx].izq;
	int der = nodos[idx].der;
	
	if (izq != -1) {
		calcularPosiciones(izq, xMin, centroX, y + separacionY, separacionY);
	}
	if (der != -1) {
		calcularPosiciones(der, centroX, xMax, y + separacionY, separacionY);
	}
}

void VistaArbol::cargarArbol(const NodoVisual listaNodos[], int cantidad, int indiceRaiz, 
							 const string& tituloArbol, bool esArbolAVL) {
	limpiar();
	if (cantidad <= 0 || indiceRaiz < 0) return;
	
	this->totalNodos = (cantidad > MAX_CIUDADES * 2) ? MAX_CIUDADES * 2 : cantidad;
	this->raiz = indiceRaiz;
	this->titulo = tituloArbol;
	this->esAVL = esArbolAVL;
	
	for (int i = 0; i < totalNodos; i++) {
		nodos[i] = listaNodos[i];
	}
	
	float separacionY = 65.0f;
	float inicioY = area.top + 50.0f;
	calcularPosiciones(raiz, area.left + 20.0f, area.left + area.width - 20.0f, inicioY, separacionY);
}

void VistaArbol::dibujarConectores(sf::RenderWindow& ventana) const {
	sf::Color colorLinea(50, 68, 98);
	
	for (int i = 0; i < totalNodos; i++) {
		if (!posiciones[i].calculada) continue;
		
		float px = posiciones[i].x;
		float py = posiciones[i].y;
		
		int izq = nodos[i].izq;
		if (izq != -1 && posiciones[izq].calculada) {
			float cx = posiciones[izq].x;
			float cy = posiciones[izq].y;
			Dibujo::dibujarFlechaDirigida(ventana, px, py, cx, cy, colorLinea, 1.8f, "", 18.0f);
		}
		
		int der = nodos[i].der;
		if (der != -1 && posiciones[der].calculada) {
			float cx = posiciones[der].x;
			float cy = posiciones[der].y;
			Dibujo::dibujarFlechaDirigida(ventana, px, py, cx, cy, colorLinea, 1.8f, "", 18.0f);
		}
	}
}

void VistaArbol::dibujarNodos(sf::RenderWindow& ventana, int nodoResaltado) const {
	float radio = 18.0f;
	
	for (int i = 0; i < totalNodos; i++) {
		if (!posiciones[i].calculada) continue;
		
		float x = posiciones[i].x;
		float y = posiciones[i].y;
		
		bool resaltado = (i == nodoResaltado);
		
		sf::CircleShape circulo(radio);
		circulo.setOrigin(radio, radio);
		circulo.setPosition(x, y);
		
		if (resaltado) {
			circulo.setFillColor(Dibujo::COLOR_VERDE_EXITO);
			circulo.setOutlineColor(sf::Color::White);
			circulo.setOutlineThickness(3.0f);
		} else {
			circulo.setFillColor(Dibujo::COLOR_PANEL);
			circulo.setOutlineColor(Dibujo::COLOR_BORDE);
			circulo.setOutlineThickness(1.8f);
		}
		ventana.draw(circulo);
		
		sf::Color colorTexto = resaltado ? sf::Color(10, 15, 26) : Dibujo::COLOR_TEXTO_TITULO;
		string textoInterno = to_string(i + 1);
		Dibujo::dibujarTexto(ventana, textoInterno, x, y, 11, colorTexto, true);
		
		Dibujo::dibujarTexto(ventana, nodos[i].etiqueta, x, y + radio + 3.0f, 10, Dibujo::COLOR_TEXTO_MUTED, true);
		
		if (esAVL) {
			string feStr = "FE:" + to_string(nodos[i].factorEquilibrio);
			sf::Color feColor = (abs(nodos[i].factorEquilibrio) > 1) ? Dibujo::COLOR_ROJO_ALERTA : Dibujo::COLOR_CIAN_ACENTO;
			Dibujo::dibujarTexto(ventana, feStr, x, y - radio - 13.0f, 9, feColor, true);
		}
	}
}

void VistaArbol::dibujar(sf::RenderWindow& ventana, int nodoResaltado) const {
	Dibujo::dibujarPanel(ventana, area.left, area.top, area.width, area.height, 
						 sf::Color(12, 16, 26), Dibujo::COLOR_BORDE, 1.0f);
	
	if (!titulo.empty()) {
		Dibujo::dibujarTexto(ventana, titulo, area.left + 20.0f, area.top + 14.0f, 15, Dibujo::COLOR_TEXTO_TITULO);
	}
	
	if (totalNodos <= 0 || raiz == -1) {
		float centroX = area.left + area.width / 2.0f;
		float centroY = area.top + area.height / 2.0f;
		Dibujo::dibujarTexto(ventana, "Arbol no generado o vacio", centroX, centroY, 14, Dibujo::COLOR_TEXTO_MUTED, true);
		return;
	}
	
	dibujarConectores(ventana);
	
	dibujarNodos(ventana, nodoResaltado);
}

int VistaArbol::getTotalNodos() const { return totalNodos; }
bool VistaArbol::estaVacio() const { return totalNodos <= 0; }
