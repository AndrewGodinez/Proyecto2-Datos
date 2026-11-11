#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constantes.h"
#include "Aerolinea.h"
#include "Reporte.h"

#if __has_include("Pantallas.h")
#include "Pantallas.h"
#endif

using namespace std;
using namespace sf;

int main() {
	Aerolinea sistema;
	sistema.cargarDatos();
	
	Reporte::mostrarDiagnosticoConsola(sistema);
	Reporte::exportarReporteTxt("reporte_sistema.txt", sistema);
	
#if __has_include("Pantallas.h")
	Pantallas gui(sistema);
	gui.ejecutar();
#else
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
#endif
	
	return 0;
}
