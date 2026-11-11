#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Pila.h"
#include "Cola.h"
#include "Grafo.h"
#include "Dijkstra.h"

using namespace std;
using namespace sf;

int main() {
	Grafo mapa;
	int sjo = mapa.agregarCiudad("SJO", "San Jose", 220.0f, 310.0f);
	int pty = mapa.agregarCiudad("PTY", "Panama", 310.0f, 350.0f);
	int mia = mapa.agregarCiudad("MIA", "Miami", 460.0f, 170.0f);
	int mad = mapa.agregarCiudad("MAD", "Madrid", 880.0f, 150.0f);
	
	mapa.agregarRuta(sjo, mia, 450.0, 2.5);
	mapa.agregarRuta(mia, mad, 500.0, 7.5);
	mapa.agregarRuta(sjo, pty, 180.0, 1.5);
	mapa.agregarRuta(pty, mad, 520.0, 10.5);
	
	ResultadoRuta rutaPasajero = Dijkstra::calcularRuta(mapa, sjo, mad, CRITERIO_DURACION);
	ResultadoRuta rutaMaleta = Dijkstra::calcularRutaEquipaje(mapa, sjo, mad, CRITERIO_COSTO, rutaPasajero);
	
	if (rutaPasajero.existe) {
		cout << "[OK] Ruta Pasajero (mas rapida): ";
		for (int i = 0; i < rutaPasajero.cantidadNodos; i++) {
			cout << mapa.getCiudad(rutaPasajero.nodos[i]).codigo << " ";
		}
		cout << "| $" << rutaPasajero.costoTotal << " | " << rutaPasajero.duracionTotal << " hrs\n";
	}
	
	if (rutaMaleta.existe) {
		cout << "[OK] Ruta Equipaje (mas barata): ";
		for (int i = 0; i < rutaMaleta.cantidadNodos; i++) {
			cout << mapa.getCiudad(rutaMaleta.nodos[i]).codigo << " ";
		}
		cout << "| $" << rutaMaleta.costoTotal << " | " << rutaMaleta.duracionTotal << " hrs\n";
	}
	
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
