#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Texto.h"
#include "Modelos.h"

using namespace std;
using namespace sf;

int main() {
	string lineaAeronave = "AV01;Boeing 737-800;180;Operativo";
	string campos[10];
	int totalCampos = Texto::dividirPorPuntoYComa(lineaAeronave, campos, 10);
	
	if (totalCampos >= 4) {
		Aeronave avion = Modelos::crearAeronave(campos);
		cout << "[OK] Aeronave leida: " << avion.codigo << " | " << avion.modelo << " | Cap: " << avion.capacidad << "\n";
		cout << "[OK] Formato guardado: " << Modelos::formatearAeronave(avion) << "\n";
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
