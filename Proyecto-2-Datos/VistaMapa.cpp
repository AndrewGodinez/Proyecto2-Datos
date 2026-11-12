#include "VistaMapa.h"
#include "Dibujo.h"
#include <cmath>

VistaMapa::VistaMapa() {
	area = sf::FloatRect(260.0f, 60.0f, 1000.0f, 480.0f);
	origenSeleccionado = -1;
	destinoSeleccionado = -1;
	ciudadHover = -1;
	mostrarRutasAlgoritmo = false;
	mostrarMST = false;
	limpiarRutas();
}

VistaMapa::VistaMapa(float x, float y, float ancho, float alto) {
	this->area = sf::FloatRect(x, y, ancho, alto);
	this->origenSeleccionado = -1;
	this->destinoSeleccionado = -1;
	this->ciudadHover = -1;
	this->mostrarRutasAlgoritmo = false;
	this->mostrarMST = false;
	limpiarRutas();
}

void VistaMapa::limpiarRutas() {
	rutaPasajero.existe = false;
	rutaPasajero.cantidadNodos = 0;
	rutaEquipaje.existe = false;
	rutaEquipaje.cantidadNodos = 0;
	redMST.conectado = false;
	redMST.cantidadAristas = 0;
	mostrarRutasAlgoritmo = false;
	mostrarMST = false;
}

void VistaMapa::setRutas(const ResultadoRuta& pasajero, const ResultadoRuta& equipaje) {
	limpiarRutas();
	this->rutaPasajero = pasajero;
	this->rutaEquipaje = equipaje;
	this->mostrarRutasAlgoritmo = true;
}

void VistaMapa::setMST(const ResultadoMST& mst) {
	limpiarRutas();
	this->redMST = mst;
	this->mostrarMST = true;
}

void VistaMapa::actualizarHover(sf::Vector2f posMouse, const Grafo& grafo) {
	ciudadHover = -1;
	if (!area.contains(posMouse)) return;
	
	float radioDeteccion = 18.0f;
	int total = grafo.getCantidadCiudades();
	for (int i = 0; i < total; i++) {
		Ciudad c = grafo.getCiudad(i);
		sf::Vector2f pos = Dibujo::proyectarCiudad(c, grafo);
		float dx = posMouse.x - pos.x;
		float dy = posMouse.y - pos.y;
		if (std::sqrt(dx * dx + dy * dy) <= radioDeteccion) {
			ciudadHover = i;
			break;
		}
	}
}

int VistaMapa::procesarEvento(const sf::Event& evento, const Grafo& grafo) {
	if (evento.type == sf::Event::MouseButtonPressed && evento.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f click(static_cast<float>(evento.mouseButton.x), static_cast<float>(evento.mouseButton.y));
		if (!area.contains(click)) return -1;
		
		float radioDeteccion = 18.0f;
		int total = grafo.getCantidadCiudades();
		for (int i = 0; i < total; i++) {
			Ciudad c = grafo.getCiudad(i);
			sf::Vector2f pos = Dibujo::proyectarCiudad(c, grafo);
			float dx = click.x - pos.x;
			float dy = click.y - pos.y;
			if (std::sqrt(dx * dx + dy * dy) <= radioDeteccion) {
				if (origenSeleccionado == -1 || (origenSeleccionado != -1 && destinoSeleccionado != -1)) {
					origenSeleccionado = i;
					destinoSeleccionado = -1;
				} else if (destinoSeleccionado == -1 && i != origenSeleccionado) {
					destinoSeleccionado = i;
				}
				return i;
			}
		}
	}
	return -1;
}

void VistaMapa::dibujarRutasBase(sf::RenderWindow& ventana, const Grafo& grafo) const {
	AristaRuta rutas[MAX_CIUDADES * MAX_CIUDADES];
	int total = grafo.obtenerTodasLasRutas(rutas);
	sf::Color colorRutaInactiva(32, 44, 68);
	
	for (int i = 0; i < total; i++) {
		Ciudad origen  = grafo.getCiudad(rutas[i].origen);
		Ciudad destino = grafo.getCiudad(rutas[i].destino);
		sf::Vector2f posO = Dibujo::proyectarCiudad(origen, grafo);
		sf::Vector2f posD = Dibujo::proyectarCiudad(destino, grafo);
		Dibujo::dibujarFlechaDirigida(ventana, posO.x, posO.y, posD.x, posD.y, 
									  colorRutaInactiva, 1.2f, "", 16.0f);
	}
}

void VistaMapa::dibujarRutasResaltadas(sf::RenderWindow& ventana, const Grafo& grafo) const {
	if (!mostrarRutasAlgoritmo) return;
	
	if (rutaEquipaje.existe && rutaEquipaje.cantidadNodos >= 2) {
		for (int i = 0; i < rutaEquipaje.cantidadNodos - 1; i++) {
			Ciudad a = grafo.getCiudad(rutaEquipaje.nodos[i]);
			Ciudad b = grafo.getCiudad(rutaEquipaje.nodos[i + 1]);
			sf::Vector2f posA = Dibujo::proyectarCiudad(a, grafo);
			sf::Vector2f posB = Dibujo::proyectarCiudad(b, grafo);
			Dibujo::dibujarFlechaDirigida(ventana, posA.x, posA.y, posB.x, posB.y, 
										  Dibujo::COLOR_NARANJA_EQUIPAJE, 2.5f, "", 16.0f);
		}
	}
	
	if (rutaPasajero.existe && rutaPasajero.cantidadNodos >= 2) {
		for (int i = 0; i < rutaPasajero.cantidadNodos - 1; i++) {
			Ciudad a = grafo.getCiudad(rutaPasajero.nodos[i]);
			Ciudad b = grafo.getCiudad(rutaPasajero.nodos[i + 1]);
			sf::Vector2f posA = Dibujo::proyectarCiudad(a, grafo);
			sf::Vector2f posB = Dibujo::proyectarCiudad(b, grafo);
			Dibujo::dibujarFlechaDirigida(ventana, posA.x, posA.y, posB.x, posB.y, 
										  Dibujo::COLOR_CIAN_ACENTO, 3.2f, "", 16.0f);
		}
	}
}

void VistaMapa::dibujarRedMST(sf::RenderWindow& ventana, const Grafo& grafo) const {
	if (!mostrarMST || !redMST.conectado) return;
	sf::Color colorMST = sf::Color(168, 85, 247);
	
	for (int i = 0; i < redMST.cantidadAristas; i++) {
		Ciudad a = grafo.getCiudad(redMST.aristas[i].origen);
		Ciudad b = grafo.getCiudad(redMST.aristas[i].destino);
		sf::Vector2f posA = Dibujo::proyectarCiudad(a, grafo);
		sf::Vector2f posB = Dibujo::proyectarCiudad(b, grafo);
		Dibujo::dibujarFlechaDirigida(ventana, posA.x, posA.y, posB.x, posB.y, colorMST, 2.8f, "", 16.0f);
	}
}

void VistaMapa::dibujarCiudades(sf::RenderWindow& ventana, const Grafo& grafo) const {
	int total = grafo.getCantidadCiudades();
	for (int i = 0; i < total; i++) {
		Ciudad c = grafo.getCiudad(i);
		sf::Vector2f pos = Dibujo::proyectarCiudad(c, grafo);
		bool seleccionada = (i == origenSeleccionado || i == destinoSeleccionado);
		bool hover = (i == ciudadHover);
		Dibujo::dibujarVerticeCiudad(ventana, c, pos, seleccionada, hover);
		
		if (i == origenSeleccionado) {
			Dibujo::dibujarTexto(ventana, "ORIGEN", pos.x, pos.y - 26.0f, 10, Dibujo::COLOR_VERDE_EXITO, true);
		} else if (i == destinoSeleccionado) {
			Dibujo::dibujarTexto(ventana, "DESTINO", pos.x, pos.y - 26.0f, 10, Dibujo::COLOR_ROJO_ALERTA, true);
		}
	}
}

void VistaMapa::dibujar(sf::RenderWindow& ventana, const Grafo& grafo, const Animacion& animacion) const {
	Dibujo::dibujarPanel(ventana, area.left, area.top, area.width, area.height, 
						 sf::Color(12, 16, 26), Dibujo::COLOR_BORDE, 1.0f);
	
	dibujarRutasBase(ventana, grafo);
	dibujarRedMST(ventana, grafo);
	dibujarRutasResaltadas(ventana, grafo);
	
	animacion.dibujar(ventana);
	
	dibujarCiudades(ventana, grafo);
}

int VistaMapa::getOrigen() const { return origenSeleccionado; }
int VistaMapa::getDestino() const { return destinoSeleccionado; }
void VistaMapa::setOrigen(int id) { origenSeleccionado = id; }
void VistaMapa::setDestino(int id) { destinoSeleccionado = id; }
void VistaMapa::limpiarSeleccion() { origenSeleccionado = -1; destinoSeleccionado = -1; }
