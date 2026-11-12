#include "PantallasCliente.h"
#include "App.h"
#include "Dibujo.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
#include "Texto.h"

PantallasCliente::PantallasCliente() {
	dijkstraPorTiempo = false;
	bfPorTiempo = false;
	bfPaginaActual = 0;
	bfTotalDestinos = 0;
	abbCargado = false;
	
	textoInfoDijkstra = "Haz clic en dos ciudades del mapa para definir ORIGEN y DESTINO.";
	textoRutaPasajero = "Ruta de pasajero: (Pendiente de calcular)";
	textoRutaEquipaje = "Ruta de equipaje: (Pendiente de calcular)";
	textoInfoBF = "Selecciona una ciudad ORIGEN en el mapa y presiona 'Calcular Destinos'.";
	textoResultadoABB = "Ingresa el nombre de una ciudad para verificar si esta en la red.";
	textoRecorridoABB = "Selecciona un recorrido para listar las ciudades ordenadas.";
	textoResultadoReserva = "Selecciona ruta en el mapa, ingresa los datos y presiona 'Confirmar Reserva'.";
	textoDetalleReserva = "";
	
	ultimaRutaPasajero.existe = false;
	ultimaRutaEquipaje.existe = false;
	
	inicializarControles();
}

void PantallasCliente::inicializarControles() {
	btnCriterioCosto = Boton(270.0f, 570.0f, 150.0f, 28.0f, "Menor Costo ($)", 
							 sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnCriterioCosto.setActivo(true);
	btnCriterioTiempo = Boton(430.0f, 570.0f, 150.0f, 28.0f, "Menor Tiempo (min)", 
							  sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnCalcularDijkstra = Boton(590.0f, 570.0f, 130.0f, 28.0f, "Calcular Ruta", 
								sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnAnimarDijkstra = Boton(730.0f, 570.0f, 120.0f, 28.0f, "Animar Vuelo", 
							  sf::Color(16, 50, 36), sf::Color(22, 75, 52), Dibujo::COLOR_VERDE_EXITO);
	
	btnBFCriterio = Boton(270.0f, 570.0f, 170.0f, 28.0f, "Criterio: Menor Costo", 
						  sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnCalcularBF = Boton(450.0f, 570.0f, 160.0f, 28.0f, "Calcular Destinos", 
						  sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnBFPrev = Boton(620.0f, 570.0f, 32.0f, 28.0f, "<", sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnBFNext = Boton(660.0f, 570.0f, 32.0f, 28.0f, ">", sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	
	txtBuscarABB = CajaTexto(270.0f, 572.0f, 200.0f, 28.0f, "Nombre de ciudad...", 24);
	btnBuscarABB = Boton(480.0f, 572.0f, 100.0f, 28.0f, "Buscar", 
						 sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnVerArbolABB = Boton(590.0f, 572.0f, 130.0f, 28.0f, "Ver / Ocultar Arbol", 
						   sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
	btnPreorden = Boton(735.0f, 572.0f, 115.0f, 28.0f, "Preorden");
	btnInorden = Boton(860.0f, 572.0f, 115.0f, 28.0f, "Inorden (A-Z)");
	btnPostorden = Boton(985.0f, 572.0f, 115.0f, 28.0f, "Postorden");
	btnNiveles = Boton(1110.0f, 572.0f, 115.0f, 28.0f, "Por Niveles");
	
	txtCedula = CajaTexto(270.0f, 572.0f, 180.0f, 28.0f, "Cedula (ej. 102340567)", 15);
	txtNombre = CajaTexto(460.0f, 572.0f, 230.0f, 28.0f, "Nombre Pasajero", 25);
	btnConfirmarReserva = Boton(700.0f, 572.0f, 160.0f, 28.0f, "Confirmar Reserva", 
								sf::Color(16, 50, 36), sf::Color(22, 75, 52), Dibujo::COLOR_VERDE_EXITO);
	btnLimpiarReserva = Boton(870.0f, 572.0f, 110.0f, 28.0f, "Limpiar", 
							  sf::Color(24, 34, 52), sf::Color(38, 52, 78));
}

void PantallasCliente::construirABB(App& app) {
	abbCiudades.limpiar();
	const Grafo& grafo = app.getSistema().getGrafo();
	int total = grafo.getCantidadCiudades();
	for (int i = 0; i < total; i++) {
		Ciudad c = grafo.getCiudad(i);
		abbCiudades.insertar(c.codigo, c.nombre);
	}
	abbCargado = true;
}

string PantallasCliente::formatearRuta(const Grafo& grafo, const ResultadoRuta& ruta) const {
	if (!ruta.existe || ruta.cantidadNodos <= 0) return "Sin ruta disponible";
	string s = "";
	for (int i = 0; i < ruta.cantidadNodos; i++) {
		if (i > 0) s += " -> ";
		s += grafo.getCiudad(ruta.nodos[i]).codigo;
	}
	return s;
}

void PantallasCliente::procesarDijkstra(const sf::Event& evento, App& app) {
	if (btnCriterioCosto.fueClickeado(evento)) {
		dijkstraPorTiempo = false;
		btnCriterioCosto.setActivo(true);
		btnCriterioTiempo.setActivo(false);
	} else if (btnCriterioTiempo.fueClickeado(evento)) {
		dijkstraPorTiempo = true;
		btnCriterioTiempo.setActivo(true);
		btnCriterioCosto.setActivo(false);
	} else if (btnCalcularDijkstra.fueClickeado(evento)) {
		int origen = app.getVistaMapa().getOrigen();
		int destino = app.getVistaMapa().getDestino();
		const Grafo& grafo = app.getSistema().getGrafo();
		
		if (origen == -1 || destino == -1) {
			textoInfoDijkstra = "Debes seleccionar una ciudad ORIGEN y una DESTINO haciendo clic en el mapa.";
			return;
		}
		
		ultimaRutaPasajero = Dijkstra::calcularRuta(grafo, origen, destino, dijkstraPorTiempo ? 1 : 0);
		ultimaRutaEquipaje = Dijkstra::calcularRutaEquipaje(grafo, origen, destino, 0, ultimaRutaPasajero);
		app.getVistaMapa().setRutas(ultimaRutaPasajero, ultimaRutaEquipaje);
		
		Ciudad cO = grafo.getCiudad(origen);
		Ciudad cD = grafo.getCiudad(destino);
		textoInfoDijkstra = "Origen: " + cO.nombre + " [" + cO.codigo + "] -> Destino: " + cD.nombre + " [" + cD.codigo + "] | Criterio: " + (dijkstraPorTiempo ? "Menor Tiempo" : "Menor Costo");
		
		if (ultimaRutaPasajero.existe) {
			textoRutaPasajero = "Pasajero (Cian): " + formatearRuta(grafo, ultimaRutaPasajero) + 
				" | Costo: $" + to_string((int)ultimaRutaPasajero.costoTotal) + 
				" | Duracion: " + to_string((int)ultimaRutaPasajero.duracionTotal) + " min | Escalas: " + to_string(ultimaRutaPasajero.escalas);
			textoRutaEquipaje = "Equipaje (Naranja - mas barata): " + formatearRuta(grafo, ultimaRutaEquipaje) + 
				" | Costo: $" + to_string((int)ultimaRutaEquipaje.costoTotal) + " | Escalas: " + to_string(ultimaRutaEquipaje.escalas);
		} else {
			textoRutaPasajero = "No existe ruta aerea directa o indirecta disponible entre ambas ciudades.";
			textoRutaEquipaje = "Sin conexion de equipaje.";
		}
	} else if (btnAnimarDijkstra.fueClickeado(evento)) {
		if (ultimaRutaPasajero.existe) {
			app.getAnimacion().iniciarVuelo(ultimaRutaPasajero, ultimaRutaEquipaje, app.getSistema().getGrafo());
		}
	}
}

void PantallasCliente::procesarBellmanFord(const sf::Event& evento, App& app) {
	if (btnBFCriterio.fueClickeado(evento)) {
		bfPorTiempo = !bfPorTiempo;
		btnBFCriterio.setTexto(bfPorTiempo ? "Criterio: Menor Tiempo" : "Criterio: Menor Costo");
	} else if (btnCalcularBF.fueClickeado(evento)) {
		int origen = app.getVistaMapa().getOrigen();
		const Grafo& grafo = app.getSistema().getGrafo();
		if (origen == -1) {
			origen = 0;
			app.getVistaMapa().setOrigen(0);
		}
		bfTotalDestinos = BellmanFord::calcularTodosLosDestinos(grafo, origen, bfPorTiempo ? 1 : 0, bfResultados);
		bfPaginaActual = 0;
		
		Ciudad cO = grafo.getCiudad(origen);
		bool cicloNeg = (bfTotalDestinos > 0 && bfResultados[0].cicloNegativo);
		textoInfoBF = "Origen: " + cO.nombre + " [" + cO.codigo + "] | Destinos alcanzables: " + to_string(bfTotalDestinos) + 
			" | Ciclo Negativo: " + (cicloNeg ? "DETECTADO!" : "Ninguno (Grafo consistente)");
	} else if (btnBFPrev.fueClickeado(evento)) {
		if (bfPaginaActual > 0) bfPaginaActual--;
	} else if (btnBFNext.fueClickeado(evento)) {
		int maxPag = (bfTotalDestinos > 0) ? (bfTotalDestinos - 1) / 6 : 0;
		if (bfPaginaActual < maxPag) bfPaginaActual++;
	}
}

void PantallasCliente::procesarABB(const sf::Event& evento, App& app) {
	if (!abbCargado) {
		construirABB(app);
	}
	
	txtBuscarABB.procesarEvento(evento);
	
	if (btnBuscarABB.fueClickeado(evento)) {
		string q = txtBuscarABB.getTexto();
		if (q.empty()) {
			textoResultadoABB = "Ingresa el nombre o codigo de una ciudad a buscar.";
			return;
		}
		ElementoABB elem;
		if (abbCiudades.buscar(q, elem)) {
			textoResultadoABB = "EXITO: " + elem.nombre + " [" + elem.codigo + "] esta registrada en el ABB de la aerolinea.";
			int idx = app.getSistema().getGrafo().buscarIndicePorCodigo(elem.codigo);
			if (idx != -1) {
				app.getVistaMapa().setOrigen(idx);
			}
		} else {
			textoResultadoABB = "La ciudad '" + q + "' NO pertenece a la red de rutas de la aerolinea.";
		}
	} else if (btnVerArbolABB.fueClickeado(evento)) {
		bool visible = !app.getMostrarVistaArbol();
		app.setMostrarVistaArbol(visible);
		if (visible) {
			NodoVisual nodos[MAX_CIUDADES * 2];
			int raiz = 0;
			int cant = abbCiudades.exportarVisual(nodos, MAX_CIUDADES * 2, raiz);
			app.getVistaArbol().cargarArbol(nodos, cant, raiz, "Arbol Binario de Busqueda (ABB) - Ciudades de la Red", false);
		}
	} else if (btnPreorden.fueClickeado(evento)) {
		textoRecorridoABB = "Preorden: " + abbCiudades.preorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(abbCiudades.tamanio(), 0.5f);
		}
	} else if (btnInorden.fueClickeado(evento)) {
		textoRecorridoABB = "Inorden (Alfabetico): " + abbCiudades.inorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(abbCiudades.tamanio(), 0.5f);
		}
	} else if (btnPostorden.fueClickeado(evento)) {
		textoRecorridoABB = "Postorden: " + abbCiudades.postorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(abbCiudades.tamanio(), 0.5f);
		}
	} else if (btnNiveles.fueClickeado(evento)) {
		textoRecorridoABB = "Por Niveles (Anchura): " + abbCiudades.porNiveles();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(abbCiudades.tamanio(), 0.5f);
		}
	}
}

void PantallasCliente::procesarReserva(const sf::Event& evento, App& app) {
	txtCedula.procesarEvento(evento);
	txtNombre.procesarEvento(evento);
	
	if (btnConfirmarReserva.fueClickeado(evento)) {
		string cedStr = txtCedula.getTexto();
		string nomStr = txtNombre.getTexto();
		int origen = app.getVistaMapa().getOrigen();
		int destino = app.getVistaMapa().getDestino();
		
		if (cedStr.empty() || nomStr.empty()) {
			textoResultadoReserva = "Error: Debes ingresar la cedula y el nombre completo del pasajero.";
			return;
		}
		if (origen == -1 || destino == -1) {
			textoResultadoReserva = "Error: Debes seleccionar origen y destino en el mapa para reservar.";
			return;
		}
		
		int cedula = Texto::aEntero(cedStr);
		string codO = app.getSistema().getGrafo().getCiudad(origen).codigo;
		string codD = app.getSistema().getGrafo().getCiudad(destino).codigo;
		
		Reserva rCreada;
		bool ok = app.getSistema().crearReserva(cedula, nomStr, codO, codD, 0, 0, rCreada);
		if (ok) {
			textoResultadoReserva = "¡Reserva #" + to_string(rCreada.idReserva) + " confirmada exitosamente!";
			textoDetalleReserva = "Pasajero: " + nomStr + " (Ced: " + to_string(cedula) + ") | Ruta: " + codO + " -> " + codD + " | Insertado en Arbol AVL Pasajeros.";
			txtCedula.limpiar();
			txtNombre.limpiar();
		} else {
			textoResultadoReserva = "No se pudo realizar la reserva. Verifica que exista conexion aerea o disponibilidad.";
		}
	} else if (btnLimpiarReserva.fueClickeado(evento)) {
		txtCedula.limpiar();
		txtNombre.limpiar();
		textoResultadoReserva = "Formulario limpiado. Listo para nueva reserva.";
		textoDetalleReserva = "";
	}
}

void PantallasCliente::procesarEvento(const sf::Event& evento, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_DIJKSTRA) {
		procesarDijkstra(evento, app);
	} else if (tab == PESTANA_BELLMAN_FORD) {
		procesarBellmanFord(evento, app);
	} else if (tab == PESTANA_ABB_CIUDADES) {
		procesarABB(evento, app);
	} else if (tab == PESTANA_RESERVA_VUELO) {
		procesarReserva(evento, app);
	}
}

void PantallasCliente::actualizar(sf::Vector2f posMouse, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_DIJKSTRA) {
		btnCriterioCosto.actualizar(posMouse);
		btnCriterioTiempo.actualizar(posMouse);
		btnCalcularDijkstra.actualizar(posMouse);
		btnAnimarDijkstra.actualizar(posMouse);
	} else if (tab == PESTANA_BELLMAN_FORD) {
		btnBFCriterio.actualizar(posMouse);
		btnCalcularBF.actualizar(posMouse);
		btnBFPrev.actualizar(posMouse);
		btnBFNext.actualizar(posMouse);
	} else if (tab == PESTANA_ABB_CIUDADES) {
		btnBuscarABB.actualizar(posMouse);
		btnVerArbolABB.actualizar(posMouse);
		btnPreorden.actualizar(posMouse);
		btnInorden.actualizar(posMouse);
		btnPostorden.actualizar(posMouse);
		btnNiveles.actualizar(posMouse);
	} else if (tab == PESTANA_RESERVA_VUELO) {
		btnConfirmarReserva.actualizar(posMouse);
		btnLimpiarReserva.actualizar(posMouse);
	}
}

void PantallasCliente::dibujarPantallaDijkstra(sf::RenderWindow& ventana, App& /*app*/) {
	Dibujo::dibujarTexto(ventana, "MODULO CLIENTE: BUSQUEDA DE RUTAS CON DIJKSTRA O(V^2)", 270.0f, 545.0f, 13, Dibujo::COLOR_CIAN_ACENTO);
	
	btnCriterioCosto.dibujar(ventana);
	btnCriterioTiempo.dibujar(ventana);
	btnCalcularDijkstra.dibujar(ventana);
	btnAnimarDijkstra.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoInfoDijkstra, 270.0f, 612.0f, 12, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, textoRutaPasajero, 270.0f, 638.0f, 11, Dibujo::COLOR_CIAN_ACENTO);
	Dibujo::dibujarTexto(ventana, textoRutaEquipaje, 270.0f, 662.0f, 11, Dibujo::COLOR_NARANJA_EQUIPAJE);
	Dibujo::dibujarTexto(ventana, "Tip: Haz clic en dos ciudades del mapa superior para fijar origen y destino.", 270.0f, 688.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasCliente::dibujarPantallaBellmanFord(sf::RenderWindow& ventana, App& app) {
	Dibujo::dibujarTexto(ventana, "MODULO CLIENTE: DESTINOS ALCANZABLES CON BELLMAN-FORD O(V*E)", 270.0f, 545.0f, 13, Dibujo::COLOR_CIAN_ACENTO);
	
	btnBFCriterio.dibujar(ventana);
	btnCalcularBF.dibujar(ventana);
	btnBFPrev.dibujar(ventana);
	btnBFNext.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoInfoBF, 705.0f, 577.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	
	if (bfTotalDestinos == 0) {
		Dibujo::dibujarTexto(ventana, "Presiona 'Calcular Destinos' para calcular todas las rutas minimas desde el origen.", 270.0f, 630.0f, 12, Dibujo::COLOR_TEXTO_MUTED);
		return;
	}
	
	int inicio = bfPaginaActual * 6;
	int fin = inicio + 6;
	if (fin > bfTotalDestinos) fin = bfTotalDestinos;
	
	const Grafo& grafo = app.getSistema().getGrafo();
	for (int i = inicio; i < fin; i++) {
		int col = (i - inicio) % 3;
		int row = (i - inicio) / 3;
		float posX = 270.0f + col * 330.0f;
		float posY = 615.0f + row * 45.0f;
		
		Ciudad dest = grafo.getCiudad(bfResultados[i].nodos[bfResultados[i].cantidadNodos - 1]);
		string valorMetrica = bfPorTiempo ? (to_string((int)bfResultados[i].duracionTotal) + " min") : ("$" + to_string((int)bfResultados[i].costoTotal));
		string linea = "[" + dest.codigo + "] " + dest.nombre + " (" + valorMetrica + ")";
		string escala = "Ruta: " + formatearRuta(grafo, bfResultados[i]);
		
		Dibujo::dibujarTexto(ventana, linea, posX, posY, 11, Dibujo::COLOR_VERDE_EXITO);
		Dibujo::dibujarTexto(ventana, escala, posX, posY + 16.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
	}
}

void PantallasCliente::dibujarPantallaABB(sf::RenderWindow& ventana, App& app) {
	Dibujo::dibujarTexto(ventana, "MODULO CLIENTE: CONSULTA Y RECORRIDOS EN ARBOL DE BUSQUEDA BINARIA (ABB)", 270.0f, 545.0f, 13, Dibujo::COLOR_CIAN_ACENTO);
	
	txtBuscarABB.dibujar(ventana);
	btnBuscarABB.dibujar(ventana);
	btnVerArbolABB.dibujar(ventana);
	
	btnPreorden.dibujar(ventana);
	btnInorden.dibujar(ventana);
	btnPostorden.dibujar(ventana);
	btnNiveles.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoResultadoABB, 270.0f, 615.0f, 12, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, textoRecorridoABB, 270.0f, 645.0f, 11, sf::Color(192, 132, 252));
	Dibujo::dibujarTexto(ventana, "Tip: Al presionar un recorrido, los nodos se iluminan en la vista visual del arbol.", 270.0f, 685.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasCliente::dibujarPantallaReserva(sf::RenderWindow& ventana, App& app) {
	Dibujo::dibujarTexto(ventana, "MODULO CLIENTE: RESERVA DE VUELO Y REGISTRO EN ARBOL AVL", 270.0f, 545.0f, 13, Dibujo::COLOR_CIAN_ACENTO);
	
	txtCedula.dibujar(ventana);
	txtNombre.dibujar(ventana);
	btnConfirmarReserva.dibujar(ventana);
	btnLimpiarReserva.dibujar(ventana);
	
	int origen = app.getVistaMapa().getOrigen();
	int destino = app.getVistaMapa().getDestino();
	string rutaSeleccionada = "Ruta seleccionada: ";
	if (origen != -1 && destino != -1) {
		const Grafo& grafo = app.getSistema().getGrafo();
		rutaSeleccionada += grafo.getCiudad(origen).nombre + " [" + grafo.getCiudad(origen).codigo + "] -> " + 
			grafo.getCiudad(destino).nombre + " [" + grafo.getCiudad(destino).codigo + "]";
	} else {
		rutaSeleccionada += "(Selecciona origen y destino haciendo clic en el mapa)";
	}
	
	Dibujo::dibujarTexto(ventana, rutaSeleccionada, 270.0f, 612.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	Dibujo::dibujarTexto(ventana, textoResultadoReserva, 270.0f, 638.0f, 12, Dibujo::COLOR_VERDE_EXITO);
	if (!textoDetalleReserva.empty()) {
		Dibujo::dibujarTexto(ventana, textoDetalleReserva, 270.0f, 664.0f, 11, Dibujo::COLOR_CIAN_ACENTO);
	}
}

void PantallasCliente::dibujar(sf::RenderWindow& ventana, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_DIJKSTRA) {
		dibujarPantallaDijkstra(ventana, app);
	} else if (tab == PESTANA_BELLMAN_FORD) {
		dibujarPantallaBellmanFord(ventana, app);
	} else if (tab == PESTANA_ABB_CIUDADES) {
		dibujarPantallaABB(ventana, app);
	} else if (tab == PESTANA_RESERVA_VUELO) {
		dibujarPantallaReserva(ventana, app);
	}
}
