#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Pila.h"
#include "Cola.h"
#include "Grafo.h"
#include "Dijkstra.h"
#include "Ordenamiento.h"
#include "ConjuntoDisjunto.h"
#include "PrimKruskal.h"

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
	mapa.agregarRuta(pty, mia, 210.0, 2.0);
	
	ResultadoMST redPrim = PrimKruskal::calcularPrim(mapa, sjo);
	ResultadoMST redKruskal = PrimKruskal::calcularKruskal(mapa, sjo);
	
	cout << "[OK] Prim (Menor Costo): $" << redPrim.costoTotal << " | Preorden: " << redPrim.preorden << "\n";
	cout << "[OK] Kruskal (Menor Duracion): " << redKruskal.duracionTotal << " hrs | Anchura: " << redKruskal.anchura << "\n";
	
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
