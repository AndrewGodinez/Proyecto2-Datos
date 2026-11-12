#include "VistaArbol.h"
#include "Dibujo.h"
#include "Cola.h"
#include <cmath>

VistaArbol::VistaArbol() {
	area = sf::FloatRect(260.0f, 60.0f, 1000.0f, 480.0f);
	totalNodos = 0;
	raiz = -1;
	titulo = "";
	esAVL = false;
	esGeneral = false;
	limpiar();
}

VistaArbol::VistaArbol(float x, float y, float ancho, float alto) {
	this->area = sf::FloatRect(x, y, ancho, alto);
	this->totalNodos = 0;
	this->raiz = -1;
	this->titulo = "";
	this->esAVL = false;
	this->esGeneral = false;
	limpiar();
}

void VistaArbol::limpiar() {
	totalNodos = 0;
	raiz = -1;
	titulo = "";
	esAVL = false;
	esGeneral = false;
	for (int i = 0; i < MAX_CIUDADES * 2; i++) {
		posiciones[i].x = 0.0f;
		posiciones[i].y = 0.0f;
		posiciones[i].calculada = false;
	}
}

int VistaArbol::contarNiveles(int idx) const {
	if (idx < 0 || idx >= totalNodos) return 0;
	int mayor = 0;
	if (esGeneral) {
		for (int hijo = nodos[idx].izq; hijo != -1; hijo = nodos[hijo].der) {
			int niveles = contarNiveles(hijo);
			if (niveles > mayor) mayor = niveles;
		}
		return mayor + 1;
	}
	int nivelesIzq = contarNiveles(nodos[idx].izq);
	int nivelesDer = contarNiveles(nodos[idx].der);
	mayor = (nivelesIzq > nivelesDer) ? nivelesIzq : nivelesDer;
	return mayor + 1;
}

int VistaArbol::contarHojas(int idx) const {
	if (nodos[idx].izq == -1) return 1;
	int total = 0;
	for (int hijo = nodos[idx].izq; hijo != -1; hijo = nodos[hijo].der) {
		total += contarHojas(hijo);
	}
	return total;
}

void VistaArbol::posicionarBinario(int idx, int profundidad, int& columna, float separacionY) {
	if (idx < 0 || idx >= totalNodos) return;
	posicionarBinario(nodos[idx].izq, profundidad + 1, columna, separacionY);
	float anchoColumna = (area.width - 40.0f) / totalNodos;
	posiciones[idx].x = area.left + 20.0f + (columna + 0.5f) * anchoColumna;
	posiciones[idx].y = area.top + 50.0f + profundidad * separacionY;
	posiciones[idx].calculada = true;
	columna++;
	posicionarBinario(nodos[idx].der, profundidad + 1, columna, separacionY);
}

void VistaArbol::posicionarGeneral(int idx, float xMin, float xMax, float y, float separacionY) {
	posiciones[idx].x = (xMin + xMax) / 2.0f;
	posiciones[idx].y = y;
	posiciones[idx].calculada = true;
	float hojasTotales = (float)contarHojas(idx);
	float x = xMin;
	for (int hijo = nodos[idx].izq; hijo != -1; hijo = nodos[hijo].der) {
		float anchoHijo = (xMax - xMin) * contarHojas(hijo) / hojasTotales;
		posicionarGeneral(hijo, x, x + anchoHijo, y + separacionY, separacionY);
		x += anchoHijo;
	}
}

void VistaArbol::ordenRecursivo(int idx, int recorrido, int orden[], int& cantidad) const {
	if (idx < 0 || idx >= totalNodos) return;
	if (recorrido == RECORRIDO_PREORDEN) {
		orden[cantidad++] = idx;
	}
	if (esGeneral) {
		int primerHijo = nodos[idx].izq;
		ordenRecursivo(primerHijo, recorrido, orden, cantidad);
		if (recorrido == RECORRIDO_INORDEN) {
			orden[cantidad++] = idx;
		}
		for (int hijo = (primerHijo == -1) ? -1 : nodos[primerHijo].der; hijo != -1; hijo = nodos[hijo].der) {
			ordenRecursivo(hijo, recorrido, orden, cantidad);
		}
		if (recorrido == RECORRIDO_POSTORDEN) {
			orden[cantidad++] = idx;
		}
		return;
	}
	ordenRecursivo(nodos[idx].izq, recorrido, orden, cantidad);
	if (recorrido == RECORRIDO_INORDEN) {
		orden[cantidad++] = idx;
	}
	ordenRecursivo(nodos[idx].der, recorrido, orden, cantidad);
	if (recorrido == RECORRIDO_POSTORDEN) {
		orden[cantidad++] = idx;
	}
}

int VistaArbol::calcularOrden(int recorrido, int orden[]) const {
	int cantidad = 0;
	if (raiz == -1) return 0;
	if (recorrido != RECORRIDO_NIVELES) {
		ordenRecursivo(raiz, recorrido, orden, cantidad);
		return cantidad;
	}
	Cola cola;
	cola.encolar(raiz);
	while (!cola.estaVacia()) {
		int actual = cola.desencolar();
		orden[cantidad++] = actual;
		if (esGeneral) {
			for (int hijo = nodos[actual].izq; hijo != -1; hijo = nodos[hijo].der) {
				cola.encolar(hijo);
			}
		} else {
			if (nodos[actual].izq != -1) cola.encolar(nodos[actual].izq);
			if (nodos[actual].der != -1) cola.encolar(nodos[actual].der);
		}
	}
	return cantidad;
}

void VistaArbol::cargarArbol(const NodoVisual listaNodos[], int cantidad, int indiceRaiz, 
							 const string& tituloArbol, bool esArbolAVL, bool esArbolGeneral) {
	limpiar();
	if (cantidad <= 0 || indiceRaiz < 0) return;
	
	this->totalNodos = (cantidad > MAX_CIUDADES * 2) ? MAX_CIUDADES * 2 : cantidad;
	this->raiz = indiceRaiz;
	this->titulo = tituloArbol;
	this->esAVL = esArbolAVL;
	this->esGeneral = esArbolGeneral;
	
	for (int i = 0; i < totalNodos; i++) {
		nodos[i] = listaNodos[i];
	}
	
	float separacionY = 65.0f;
	int niveles = contarNiveles(raiz);
	if (niveles > 1 && (area.height - 90.0f) / (niveles - 1) < separacionY) {
		separacionY = (area.height - 90.0f) / (niveles - 1);
	}
	float inicioY = area.top + 50.0f;
	if (esGeneral) {
		posicionarGeneral(raiz, area.left + 20.0f, area.left + area.width - 20.0f, inicioY, separacionY);
	} else {
		int columna = 0;
		posicionarBinario(raiz, 0, columna, separacionY);
	}
}

void VistaArbol::dibujarConectores(sf::RenderWindow& ventana) const {
	sf::Color colorLinea(50, 68, 98);
	
	for (int i = 0; i < totalNodos; i++) {
		if (!posiciones[i].calculada) continue;
		
		float px = posiciones[i].x;
		float py = posiciones[i].y;
		
		if (esGeneral) {
			for (int hijo = nodos[i].izq; hijo != -1; hijo = nodos[hijo].der) {
				Dibujo::dibujarFlechaDirigida(ventana, px, py, posiciones[hijo].x, posiciones[hijo].y, colorLinea, 1.8f, "", 18.0f);
			}
			continue;
		}
		
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
