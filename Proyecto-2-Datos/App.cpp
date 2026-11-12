#include "App.h"
#include "Dibujo.h"
#include "PantallasCliente.h"
#include "PantallasAdmin.h"
#include "PantallasGestion.h"
#include <iostream>
#include <cmath>

static bool enPantallaCompleta = false;

static void ajustarVistaVentana(sf::RenderWindow& ventana, unsigned int ancho, unsigned int alto) {
	if (ancho == 0 || alto == 0) {
		return;
	}
	float ratioVentana = static_cast<float>(ancho) / static_cast<float>(alto);
	float ratioBase = static_cast<float>(ANCHO_VENTANA) / static_cast<float>(ALTO_VENTANA);
	
	sf::View vista(sf::FloatRect(0.0f, 0.0f, static_cast<float>(ANCHO_VENTANA), static_cast<float>(ALTO_VENTANA)));
	if (ratioVentana >= ratioBase) {
		float anchoViewport = ratioBase / ratioVentana;
		vista.setViewport(sf::FloatRect((1.0f - anchoViewport) / 2.0f, 0.0f, anchoViewport, 1.0f));
	} else {
		float altoViewport = ratioVentana / ratioBase;
		vista.setViewport(sf::FloatRect(0.0f, (1.0f - altoViewport) / 2.0f, 1.0f, altoViewport));
	}
	ventana.setView(vista);
}

App::App(Aerolinea& aerolinea) 
	: ventana(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Aerolinea UNA - Plataforma de Gestion y Rutas (EIF207)"),
	sistema(aerolinea),
	vistaMapa(255.0f, 55.0f, 1015.0f, 475.0f),
	vistaArbol(255.0f, 55.0f, 1015.0f, 475.0f) {
	
	ventana.setFramerateLimit(60);
	ajustarVistaVentana(ventana, ventana.getSize().x, ventana.getSize().y);
	Dibujo::inicializarFuente();
	pestanaActual = PESTANA_DIJKSTRA;
	mostrarVistaArbol = false;
	pantallasCliente = new PantallasCliente();
	pantallasAdmin = new PantallasAdmin();
	pantallasGestion = new PantallasGestion();
	
	inicializarMenuLateral();
}

App::~App() {
	if (pantallasCliente != nullptr) {
		delete pantallasCliente;
		pantallasCliente = nullptr;
	}
	if (pantallasAdmin != nullptr) {
		delete pantallasAdmin;
		pantallasAdmin = nullptr;
	}
	if (pantallasGestion != nullptr) {
		delete pantallasGestion;
		pantallasGestion = nullptr;
	}
}

void App::inicializarMenuLateral() {
	const string nombresMenu[TOTAL_PESTANAS] = {
		"1. Rutas (Dijkstra)",
			"2. Destinos (Bellman-Ford)",
			"3. Ciudades (ABB)",
			"4. Reservar Vuelo",
			"5. Flota y Tripulacion",
			"6. Pasajeros (AVL)",
			"7. Minimos (Prim/Kruskal)",
			"8. Equipaje vs Tiempo",
			"9. Ciudades y Rutas",
			"10. Vuelos y Pasajeros"
	};
	
	float inicioY = 90.0f;
	float espaciado = 42.0f;
	
	for (int i = 0; i < TOTAL_PESTANAS; i++) {
		float offsetY = (i >= PESTANA_FLOTA_ADMIN) ? 22.0f : 0.0f;
		float y = inicioY + (i * espaciado) + offsetY;
		botonesMenu[i] = Boton(12.0f, y, 228.0f, 36.0f, nombresMenu[i], 
							   sf::Color(28, 28, 34), sf::Color(44, 44, 52), Dibujo::COLOR_TEXTO_TITULO);
	}
	botonesMenu[PESTANA_DIJKSTRA].setActivo(true);
	
	btnGuardarDatos = Boton(12.0f, ALTO_VENTANA - 48.0f, 228.0f, 36.0f, "Guardar Datos TXT",
							sf::Color(16, 50, 36), sf::Color(22, 75, 52), Dibujo::COLOR_VERDE_EXITO);
}

void App::cambiarPestana(PestanaSistema nuevaPestana) {
	pestanaActual = nuevaPestana;
	for (int i = 0; i < TOTAL_PESTANAS; i++) {
		botonesMenu[i].setActivo(i == pestanaActual);
	}
	
	mostrarVistaArbol = false;
	
	vistaMapa.limpiarRutas();
	animacion.detener();
	animacion.detenerRecorridoArbol();
	CajaTexto::quitarFocoActivo();
}

void App::procesarEventos() {
	sf::Event evento;
	
	while (ventana.pollEvent(evento)) {
		if (evento.type == sf::Event::Closed) {
			ventana.close();
		}
		
		if (evento.type == sf::Event::Resized) {
			ajustarVistaVentana(ventana, evento.size.width, evento.size.height);
		}
		
		if (evento.type == sf::Event::MouseButtonPressed || evento.type == sf::Event::MouseButtonReleased) {
			sf::Vector2f coords = ventana.mapPixelToCoords(sf::Vector2i(evento.mouseButton.x, evento.mouseButton.y));
			evento.mouseButton.x = static_cast<int>(std::floor(coords.x + 0.5f));
			evento.mouseButton.y = static_cast<int>(std::floor(coords.y + 0.5f));
		} else if (evento.type == sf::Event::MouseMoved) {
			sf::Vector2f coords = ventana.mapPixelToCoords(sf::Vector2i(evento.mouseMove.x, evento.mouseMove.y));
			evento.mouseMove.x = static_cast<int>(std::floor(coords.x + 0.5f));
			evento.mouseMove.y = static_cast<int>(std::floor(coords.y + 0.5f));
		}
		
		if (evento.type == sf::Event::KeyPressed && !CajaTexto::hayCajaActiva()) {
			if (evento.key.code == sf::Keyboard::Escape) {
				vistaMapa.limpiarSeleccion();
				vistaMapa.limpiarRutas();
				animacion.detener();
			} else if (evento.key.code == sf::Keyboard::Space) {
				animacion.alternarPausa();
			} else if (evento.key.code == sf::Keyboard::F11) {
				enPantallaCompleta = !enPantallaCompleta;
				if (enPantallaCompleta) {
					sf::VideoMode modo = sf::VideoMode::getDesktopMode();
					ventana.create(modo, "Aerolinea UNA - Plataforma de Gestion y Rutas (EIF207)", sf::Style::Fullscreen);
					ajustarVistaVentana(ventana, modo.width, modo.height);
				} else {
					ventana.create(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Aerolinea UNA - Plataforma de Gestion y Rutas (EIF207)", sf::Style::Default);
					ajustarVistaVentana(ventana, ANCHO_VENTANA, ALTO_VENTANA);
				}
				ventana.setFramerateLimit(60);
				continue;
			}
		}
		
		for (int i = 0; i < TOTAL_PESTANAS; i++) {
			if (botonesMenu[i].fueClickeado(evento)) {
				cambiarPestana(static_cast<PestanaSistema>(i));
				break;
			}
		}
		
		if (btnGuardarDatos.fueClickeado(evento)) {
			sistema.guardarDatos();
			std::cout << "[SISTEMA] Datos exportados exitosamente a archivos TXT.\n";
		}
		
		if (!mostrarVistaArbol) {
			vistaMapa.procesarEvento(evento, sistema.getGrafo());
		}
		
		if (pestanaActual <= PESTANA_RESERVA_VUELO && pantallasCliente != nullptr) {
			pantallasCliente->procesarEvento(evento, *this);
		} else if ((pestanaActual == PESTANA_FLOTA_ADMIN || pestanaActual >= PESTANA_CIUDADES_RUTAS) && pantallasGestion != nullptr) {
			pantallasGestion->procesarEvento(evento, *this);
		} else if (pantallasAdmin != nullptr) {
			pantallasAdmin->procesarEvento(evento, *this);
		}
	}
	
	sf::Vector2f posMouse = ventana.mapPixelToCoords(sf::Mouse::getPosition(ventana));
	
	for (int i = 0; i < TOTAL_PESTANAS; i++) {
		botonesMenu[i].actualizar(posMouse);
	}
	btnGuardarDatos.actualizar(posMouse);
	
	if (!mostrarVistaArbol) {
		vistaMapa.actualizarHover(posMouse, sistema.getGrafo());
	}
	
	if (pestanaActual <= PESTANA_RESERVA_VUELO && pantallasCliente != nullptr) {
		pantallasCliente->actualizar(posMouse, *this);
	} else if ((pestanaActual == PESTANA_FLOTA_ADMIN || pestanaActual >= PESTANA_CIUDADES_RUTAS) && pantallasGestion != nullptr) {
		pantallasGestion->actualizar(posMouse, *this);
	} else if (pantallasAdmin != nullptr) {
		pantallasAdmin->actualizar(posMouse, *this);
	}
}

void App::actualizar(float dt) {
	animacion.actualizar(dt, sistema.getGrafo());
}

void App::dibujarBarraSuperior() {
	Dibujo::dibujarPanel(ventana, 0.0f, 0.0f, ANCHO_VENTANA, 50.0f, 
						 sf::Color(24, 24, 28), Dibujo::COLOR_BORDE, 1.0f);
	
	Dibujo::dibujarTexto(ventana, "AEROLINEA UNA - GESTION Y RUTAS AEREAS", 16.0f, 15.0f, 16, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, "EIF207 Estructuras de Datos", 440.0f, 18.0f, 12, Dibujo::COLOR_TEXTO_MUTED);
	
	string telemetria = "Ciudades: " + to_string(sistema.getGrafo().getCantidadCiudades()) + 
		"  |  Vuelos: " + to_string(sistema.getCantidadVuelos()) +
		"  |  Pasajeros AVL: " + to_string(sistema.getAvlPasajeros().tamanio());
	Dibujo::dibujarTexto(ventana, telemetria, ANCHO_VENTANA - 320.0f, 17.0f, 12, Dibujo::COLOR_CIAN_ACENTO);
}

void App::dibujarMenuLateral() {
	Dibujo::dibujarPanel(ventana, 0.0f, 50.0f, 250.0f, ALTO_VENTANA - 50.0f, 
						 sf::Color(22, 22, 26), Dibujo::COLOR_BORDE, 1.0f);
	
	Dibujo::dibujarTexto(ventana, "MODULO DEL CLIENTE", 16.0f, 68.0f, 11, Dibujo::COLOR_CIAN_ACENTO);
	
	float ySeccionAdmin = 90.0f + (PESTANA_FLOTA_ADMIN * 42.0f) + 4.0f;
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO", 16.0f, ySeccionAdmin, 11, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	for (int i = 0; i < TOTAL_PESTANAS; i++) {
		botonesMenu[i].dibujar(ventana);
	}
	btnGuardarDatos.dibujar(ventana);
}

void App::dibujar() {
	ventana.clear(Dibujo::COLOR_FONDO);
	
	dibujarBarraSuperior();
	dibujarMenuLateral();
	
	if (mostrarVistaArbol) {
		int nodoResaltado = animacion.getNodoActivoArbol();
		vistaArbol.dibujar(ventana, nodoResaltado);
	} else {
		vistaMapa.dibujar(ventana, sistema.getGrafo(), animacion);
	}
	
	Dibujo::dibujarPanel(ventana, 255.0f, 535.0f, 1015.0f, 180.0f, 
						 sf::Color(26, 26, 30), Dibujo::COLOR_BORDE, 1.0f);
	
	if (pestanaActual <= PESTANA_RESERVA_VUELO && pantallasCliente != nullptr) {
		pantallasCliente->dibujar(ventana, *this);
	} else if ((pestanaActual == PESTANA_FLOTA_ADMIN || pestanaActual >= PESTANA_CIUDADES_RUTAS) && pantallasGestion != nullptr) {
		pantallasGestion->dibujar(ventana, *this);
	} else if (pantallasAdmin != nullptr) {
		pantallasAdmin->dibujar(ventana, *this);
	}
	
	ventana.display();
}

void App::ejecutar() {
	while (ventana.isOpen()) {
		float dt = relojFrame.restart().asSeconds();
		procesarEventos();
		actualizar(dt);
		dibujar();
	}
}

void App::animarRecorridoArbol(int recorrido) {
	if (!mostrarVistaArbol) {
		return;
	}
	int orden[MAX_CIUDADES * 2];
	int cantidad = vistaArbol.calcularOrden(recorrido, orden);
	animacion.iniciarRecorridoArbol(orden, cantidad, 0.5f);
}

PestanaSistema App::getPestanaActual() const { return pestanaActual; }
VistaMapa& App::getVistaMapa() { return vistaMapa; }
VistaArbol& App::getVistaArbol() { return vistaArbol; }
Animacion& App::getAnimacion() { return animacion; }
Aerolinea& App::getSistema() { return sistema; }
sf::RenderWindow& App::getVentana() { return ventana; }
