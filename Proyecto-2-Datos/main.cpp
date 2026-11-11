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
#include "ArbolAVL.h"

using namespace std;
using namespace sf;

int main() {
	ArbolAVL avlPasajeros;
	avlPasajeros.insertar(10, "Carlos", "Vuelo SJO-MIA");
	avlPasajeros.insertar(20, "Ana", "Vuelo MIA-MAD");
	avlPasajeros.insertar(30, "Luis", "Vuelo SJO-PTY");
	avlPasajeros.insertar(40, "Sofia", "Vuelo PTY-MAD");
	avlPasajeros.insertar(50, "Elena", "Vuelo SJO-MIA");
	
	cout << "[OK] AVL Inorden: " << avlPasajeros.inorden() << "\n";
	cout << "[OK] AVL Preorden (Raiz balanceada): " << avlPasajeros.preorden() << "\n";
	cout << "[OK] AVL Anchura: " << avlPasajeros.anchura() << "\n";
	
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
