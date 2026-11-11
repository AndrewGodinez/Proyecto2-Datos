#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Pila.h"
#include "Cola.h"
#include "Grafo.h"

using namespace std;
using namespace sf;

int main() {
	Grafo mapa;
	int sjo = mapa.agregarCiudad("SJO", "San Jose", 220.0f, 310.0f);
	int mia = mapa.agregarCiudad("MIA", "Miami", 460.0f, 170.0f);
	int mad = mapa.agregarCiudad("MAD", "Madrid", 880.0f, 150.0f);
	
	mapa.agregarRuta(sjo, mia, 320.0, 3.0);
	mapa.agregarRuta(mia, mad, 610.0, 8.5);
	
	cout << "[OK] Ciudades en Grafo: " << mapa.getCantidadCiudades() << "\n";
	cout << "[OK] Costo SJO->MIA: $" << mapa.getCostoRuta(sjo, mia) << "\n";
	cout << "[OK] Duracion MIA->MAD: " << mapa.getDuracionRuta(mia, mad) << " hrs\n";
	
	Pila pilaCamino;
	pilaCamino.apilar(sjo);
	pilaCamino.apilar(mia);
	pilaCamino.apilar(mad);
	cout << "[OK] Tope en Pila: " << mapa.getCiudad(pilaCamino.verTope()).codigo << "\n";
	
	Cola colaAnchura;
	colaAnchura.encolar(sjo);
	colaAnchura.encolar(mia);
	cout << "[OK] Frente en Cola: " << mapa.getCiudad(colaAnchura.verFrente()).codigo << "\n";
	
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
