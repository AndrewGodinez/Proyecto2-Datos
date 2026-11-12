#include "Animacion.h"
#include "Dibujo.h"
#include <cmath>

Animacion::Animacion() {
	detener();
	detenerRecorridoArbol();
}

void Animacion::detener() {
	animandoRutas = false;
	pausado = false;
	avionPasajero.activo = false;
	avionPasajero.finalizado = true;
	avionEquipaje.activo = false;
	avionEquipaje.finalizado = true;
}

void Animacion::alternarPausa() {
	if (animandoRutas || animandoArbol) {
		pausado = !pausado;
	}
}

void Animacion::iniciarVuelo(const ResultadoRuta& rutaPasajero, const ResultadoRuta& rutaEquipaje, const Grafo& grafo) {
	detener();
	pausado = false;
	
	if (rutaPasajero.existe && rutaPasajero.cantidadNodos >= 2) {
		avionPasajero.activo = true;
		avionPasajero.finalizado = false;
		avionPasajero.cantidadNodos = rutaPasajero.cantidadNodos;
		for (int i = 0; i < rutaPasajero.cantidadNodos; i++) {
			avionPasajero.nodos[i] = rutaPasajero.nodos[i];
		}
		avionPasajero.tramoActual = 0;
		avionPasajero.progresoTramo = 0.0f;
		avionPasajero.velocidad = 0.55f;
		avionPasajero.color = Dibujo::COLOR_CIAN_ACENTO;
		avionPasajero.etiqueta = "Vuelo";
		
		Ciudad inicio = grafo.getCiudad(avionPasajero.nodos[0]);
		avionPasajero.posActual = Dibujo::proyectarCiudad(inicio, grafo);
		avionPasajero.angulo = 0.0f;
		animandoRutas = true;
	}
	
	if (rutaEquipaje.existe && rutaEquipaje.cantidadNodos >= 2) {
		avionEquipaje.activo = true;
		avionEquipaje.finalizado = false;
		avionEquipaje.cantidadNodos = rutaEquipaje.cantidadNodos;
		for (int i = 0; i < rutaEquipaje.cantidadNodos; i++) {
			avionEquipaje.nodos[i] = rutaEquipaje.nodos[i];
		}
		avionEquipaje.tramoActual = 0;
		avionEquipaje.progresoTramo = 0.0f;
		avionEquipaje.velocidad = 0.50f;
		avionEquipaje.color = Dibujo::COLOR_NARANJA_EQUIPAJE;
		avionEquipaje.etiqueta = "Equipaje";
		
		Ciudad inicio = grafo.getCiudad(avionEquipaje.nodos[0]);
		avionEquipaje.posActual = Dibujo::proyectarCiudad(inicio, grafo);
		avionEquipaje.angulo = 0.0f;
		animandoRutas = true;
	}
}

void Animacion::iniciarRecorridoArbol(const int orden[], int cantidadNodos, float intervaloSegundos) {
	detenerRecorridoArbol();
	if (cantidadNodos <= 0) return;
	for (int i = 0; i < cantidadNodos && i < MAX_CIUDADES * 2; i++) {
		ordenArbol[i] = orden[i];
	}
	animandoArbol = true;
	totalNodosArbol = cantidadNodos;
	nodoActivoArbol = 0;
	tiempoPasoArbol = intervaloSegundos;
	acumuladorTiempoArbol = 0.0f;
}

void Animacion::detenerRecorridoArbol() {
	animandoArbol = false;
	totalNodosArbol = 0;
	nodoActivoArbol = -1;
	acumuladorTiempoArbol = 0.0f;
}

int Animacion::getNodoActivoArbol() const {
	if (nodoActivoArbol < 0) {
		return -1;
	}
	return ordenArbol[nodoActivoArbol];
}

bool Animacion::getAnimandoArbol() const {
	return animandoArbol;
}

void Animacion::actualizarAvion(AvionAnimado& avion, float dt, const Grafo& grafo) {
	if (!avion.activo || avion.finalizado) return;
	
	if (avion.tramoActual >= avion.cantidadNodos - 1) {
		avion.finalizado = true;
		return;
	}
	
	Ciudad origen  = grafo.getCiudad(avion.nodos[avion.tramoActual]);
	Ciudad destino = grafo.getCiudad(avion.nodos[avion.tramoActual + 1]);
	
	sf::Vector2f posO = Dibujo::proyectarCiudad(origen, grafo);
	sf::Vector2f posD = Dibujo::proyectarCiudad(destino, grafo);
	
	float dx = posD.x - posO.x;
	float dy = posD.y - posO.y;
	const float PI = 3.14159265f;
	avion.angulo = std::atan2(dy, dx) * 180.0f / PI;
	
	avion.progresoTramo += avion.velocidad * dt;
	
	if (avion.progresoTramo >= 1.0f) {
		avion.progresoTramo = 0.0f;
		avion.tramoActual++;
		if (avion.tramoActual >= avion.cantidadNodos - 1) {
			avion.posActual = posD;
			avion.finalizado = true;
			return;
		}
	}
	
	float t = avion.progresoTramo;
	avion.posActual.x = posO.x + dx * t;
	avion.posActual.y = posO.y + dy * t;
}

void Animacion::actualizar(float dt, const Grafo& grafo) {
	if (pausado) return;
	
	if (animandoRutas) {
		actualizarAvion(avionPasajero, dt, grafo);
		actualizarAvion(avionEquipaje, dt, grafo);
		
		if (avionPasajero.finalizado && avionEquipaje.finalizado) {
			animandoRutas = false;
		}
	}
	
	if (animandoArbol) {
		acumuladorTiempoArbol += dt;
		if (acumuladorTiempoArbol >= tiempoPasoArbol) {
			acumuladorTiempoArbol = 0.0f;
			nodoActivoArbol++;
			if (nodoActivoArbol >= totalNodosArbol) {
				animandoArbol = false;
				nodoActivoArbol = -1;
			}
		}
	}
}

void Animacion::dibujarAvion(sf::RenderWindow& ventana, const AvionAnimado& avion) const {
	if (!avion.activo || avion.finalizado) return;
	
	sf::CircleShape estela(5.0f);
	estela.setOrigin(5.0f, 5.0f);
	estela.setPosition(avion.posActual);
	estela.setFillColor(sf::Color(avion.color.r, avion.color.g, avion.color.b, 90));
	ventana.draw(estela);
	
	sf::ConvexShape avionGeom(5);
	avionGeom.setPoint(0, sf::Vector2f( 14.0f,   0.0f)); 
	avionGeom.setPoint(1, sf::Vector2f( -4.0f,  11.0f)); 
	avionGeom.setPoint(2, sf::Vector2f( -8.0f,   3.0f)); 
	avionGeom.setPoint(3, sf::Vector2f( -8.0f,  -3.0f)); 
	avionGeom.setPoint(4, sf::Vector2f( -4.0f, -11.0f)); 
	
	avionGeom.setPosition(avion.posActual);
	avionGeom.setRotation(avion.angulo);
	avionGeom.setFillColor(avion.color);
	avionGeom.setOutlineColor(sf::Color::White);
	avionGeom.setOutlineThickness(1.2f);
	ventana.draw(avionGeom);
	
	Dibujo::dibujarTexto(ventana, avion.etiqueta, avion.posActual.x, avion.posActual.y - 18.0f, 10, avion.color, true);
}

void Animacion::dibujar(sf::RenderWindow& ventana) const {
	if (animandoRutas) {
		dibujarAvion(ventana, avionEquipaje);
		dibujarAvion(ventana, avionPasajero);
	}
}

bool Animacion::estaActiva() const {
	return animandoRutas || animandoArbol;
}

bool Animacion::estaPausada() const {
	return pausado;
}
