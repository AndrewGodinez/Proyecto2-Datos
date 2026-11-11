#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "PilaEnteros.h"
#include "ColaEnteros.h"

using namespace std;
using namespace sf;

int main() {
	Ciudad c1 = { 0, "SJO", "San Jose", 220.0f, 310.0f };
	Ciudad c2 = { 1, "MIA", "Miami", 460.0f, 170.0f };
	cout << "[OK] Ruta inicial: " << c1.codigo << " -> " << c2.codigo << "\n";
	
	PilaEnteros pilaCamino;
	pilaCamino.apilar(0);
	pilaCamino.apilar(1);
	pilaCamino.apilar(2);
	cout << "[OK] Tope en PilaEnteros: " << pilaCamino.verTope() << "\n";
	cout << "[OK] Desapilando: " << pilaCamino.desapilar() << "\n";
	
	ColaEnteros colaAnchura;
	colaAnchura.encolar(10);
	colaAnchura.encolar(20);
	colaAnchura.encolar(30);
	cout << "[OK] Frente en ColaEnteros: " << colaAnchura.verFrente() << "\n";
	cout << "[OK] Desencolando: " << colaAnchura.desencolar() << "\n";
	
	RenderWindow ventana(VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Aerolinea UNA - EIF207");
	ventana.setFramerateLimit(60);
	
	while (ventana.isOpen()) {
		Event evento;
		while (ventana.pollEvent(evento)) {
			if (evento.type == Event::Closed) {
				ventana.close();
			}
		}
		
		ventana.clear(Color(15, 20, 32));
		ventana.display();
	}
	
	return 0;
}
