#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Grafo.h"
#include "Modelos.h"
#include "Persistencia.h"

using namespace std;
using namespace sf;

int main() {
	Grafo mapa;
	mapa.agregarCiudad("SJO", "San Jose", 220.0f, 310.0f);
	mapa.agregarCiudad("MIA", "Miami", 460.0f, 170.0f);
	mapa.agregarRuta(0, 1, 320.0, 3.0);
	
	Persistencia::guardarCiudades("ciudades.txt", mapa);
	Persistencia::guardarRutas("rutas.txt", mapa);
	
	Grafo mapaCargado;
	Persistencia::cargarCiudades("ciudades.txt", mapaCargado);
	Persistencia::cargarRutas("rutas.txt", mapaCargado);
	
	cout << "[OK] Ciudades cargadas desde archivo: " << mapaCargado.getCantidadCiudades() << "\n";
	cout << "[OK] Costo SJO->MIA cargado: $" << mapaCargado.getCostoRuta(0, 1) << "\n";
	
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
