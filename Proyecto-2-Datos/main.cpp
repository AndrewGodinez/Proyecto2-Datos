#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Aerolinea.h"

using namespace std;
using namespace sf;

int main() {
	Aerolinea sistema;
	sistema.cargarDatos();
	
	cout << "[OK] Ciudades cargadas: " << sistema.getGrafo().getCantidadCiudades() << "\n";
	cout << "[OK] Aeronaves cargadas: " << sistema.getCantidadAeronaves() << "\n";
	cout << "[OK] Tripulantes cargados: " << sistema.getCantidadTripulantes() << "\n";
	cout << "[OK] Vuelos cargados: " << sistema.getCantidadVuelos() << "\n";
	cout << "[OK] Reservas en AVL: " << sistema.getAvlPasajeros().tamanio() << "\n";
	
	ResultadoMST mstPrim = sistema.obtenerRedPrim();
	ResultadoMST mstKruskal = sistema.obtenerRedKruskal();
	cout << "[OK] MST Prim Costo Total: $" << mstPrim.costoTotal << " | Preorden: " << mstPrim.preorden << "\n";
	cout << "[OK] MST Kruskal Duracion Total: " << mstKruskal.duracionTotal << " hrs | Anchura: " << mstKruskal.anchura << "\n";
	cout << "[OK] AVL Pasajeros Inorden: " << sistema.getAvlPasajeros().inorden() << "\n";
	
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
