#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Aerolinea.h"

using namespace std;
using namespace sf;

int main() {
	Aerolinea sistema;
	sistema.registrarCiudad("SJO", "San Jose", 220.0f, 310.0f);
	sistema.registrarCiudad("PTY", "Panama", 310.0f, 350.0f);
	sistema.registrarCiudad("MIA", "Miami", 460.0f, 170.0f);
	sistema.registrarCiudad("MAD", "Madrid", 880.0f, 150.0f);
	
	sistema.registrarAeronave("AV01", "Boeing 737", 180, "Operativo");
	sistema.registrarTripulante("TR01", "Cap. Morales", "Piloto");
	
	sistema.programarVuelo("VU101", "SJO", "MIA", "08:00", 450.0, 2.5, "AV01");
	sistema.programarVuelo("VU102", "MIA", "MAD", "12:00", 500.0, 7.5, "AV01");
	sistema.registrarRuta("SJO", "PTY", 180.0, 1.5);
	sistema.registrarRuta("PTY", "MAD", 520.0, 10.5);
	
	Reserva nuevaReserva;
	if (sistema.crearReserva(118900123, "Sem Mora", "SJO", "MAD", CRITERIO_DURACION, CRITERIO_COSTO, nuevaReserva)) {
		cout << "[OK] Reserva #" << nuevaReserva.idReserva << " creada para " << nuevaReserva.nombrePasajero << "\n";
		cout << "[OK] Ruta Pasajero: " << nuevaReserva.rutaPasajero << "\n";
		cout << "[OK] Ruta Equipaje: " << nuevaReserva.rutaEquipaje << "\n";
		cout << "[OK] AVL Pasajeros Inorden: " << sistema.getAvlPasajeros().inorden() << "\n";
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
