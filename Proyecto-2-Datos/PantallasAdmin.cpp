#include "PantallasAdmin.h"
#include "App.h"
#include "Dibujo.h"
#include "Dijkstra.h"
#include "Texto.h"
#include "Modelos.h"

PantallasAdmin::PantallasAdmin() {
	flotaPagina = 0;
	mstCalculado = false;
	ultimoMST.conectado = false;
	compPasajero.existe = false;
	compEquipaje.existe = false;
	
	textoInfoFlota = "Listado de aeronaves registradas, tripulacion activa y vuelos programados.";
	textoResultadoAVL = "Ingresa la cedula del pasajero para consultar su estado en el Arbol AVL.";
	textoRecorridoAVL = "Selecciona un recorrido para listar los pasajeros ordenados por cedula.";
	textoInfoMST = "Genera el Arbol de Expansion Minima: Prim (por Costo) o Kruskal (por Duracion).";
	textoRecorridoMST = "Recorridos del arbol de ciudades generado por Prim/Kruskal.";
	textoInfoEquipaje = "Selecciona origen y destino en el mapa para contrastar la ruta del pasajero vs maleta.";
	textoComparativa = "Pasajero: (Pendiente de calcular)";
	textoAhorro = "Ahorro estimado en equipaje: $0";
	
	inicializarControles();
}

void PantallasAdmin::inicializarControles() {
	btnFlotaPrev = Boton(270.0f, 570.0f, 36.0f, 28.0f, "<", sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnFlotaNext = Boton(315.0f, 570.0f, 36.0f, 28.0f, ">", sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	
	txtBuscarPasajero = CajaTexto(270.0f, 572.0f, 190.0f, 28.0f, "Cedula pasajero...", 15);
	btnBuscarPasajero = Boton(470.0f, 572.0f, 90.0f, 28.0f, "Buscar", 
							  sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnVerArbolAVL = Boton(570.0f, 572.0f, 130.0f, 28.0f, "Ver / Ocultar AVL", 
						   sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
	btnPreordenAVL = Boton(710.0f, 572.0f, 115.0f, 28.0f, "Preorden");
	btnInordenAVL = Boton(835.0f, 572.0f, 115.0f, 28.0f, "Inorden");
	btnPostordenAVL = Boton(960.0f, 572.0f, 115.0f, 28.0f, "Postorden");
	btnNivelesAVL = Boton(1085.0f, 572.0f, 115.0f, 28.0f, "Por Niveles");
	
	btnPrimCosto = Boton(270.0f, 570.0f, 160.0f, 28.0f, "Prim (Menor Costo)", 
						 sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnKruskalTiempo = Boton(440.0f, 570.0f, 170.0f, 28.0f, "Kruskal (Menor Tiempo)", 
							 sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
	btnLimpiarMST = Boton(620.0f, 570.0f, 110.0f, 28.0f, "Limpiar Mapa", 
						  sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnMSTPreorden = Boton(740.0f, 570.0f, 110.0f, 28.0f, "Preorden");
	btnMSTInorden = Boton(860.0f, 570.0f, 110.0f, 28.0f, "Inorden");
	btnMSTPostorden = Boton(980.0f, 570.0f, 110.0f, 28.0f, "Postorden");
	btnMSTNiveles = Boton(1100.0f, 570.0f, 110.0f, 28.0f, "Por Niveles");
	
	btnCompararEquipaje = Boton(270.0f, 570.0f, 160.0f, 28.0f, "Comparar Rutas", 
								sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnAnimarEquipaje = Boton(440.0f, 570.0f, 140.0f, 28.0f, "Animar Ambos", 
							  sf::Color(16, 50, 36), sf::Color(22, 75, 52), Dibujo::COLOR_VERDE_EXITO);
}

string PantallasAdmin::formatearRuta(const Grafo& grafo, const ResultadoRuta& ruta) const {
	if (!ruta.existe || ruta.cantidadNodos <= 0) return "Sin ruta disponible";
	string s = "";
	for (int i = 0; i < ruta.cantidadNodos; i++) {
		if (i > 0) s += " -> ";
		s += grafo.getCiudad(ruta.nodos[i]).codigo;
	}
	return s;
}

void PantallasAdmin::procesarFlota(const sf::Event& evento, App& app) {
	if (btnFlotaPrev.fueClickeado(evento)) {
		if (flotaPagina > 0) flotaPagina--;
	} else if (btnFlotaNext.fueClickeado(evento)) {
		int maxAero = app.getSistema().getCantidadAeronaves();
		if ((flotaPagina + 1) * 3 < maxAero) flotaPagina++;
	}
}

void PantallasAdmin::procesarAVL(const sf::Event& evento, App& app) {
	txtBuscarPasajero.procesarEvento(evento);
	
	if (btnBuscarPasajero.fueClickeado(evento)) {
		string cedStr = txtBuscarPasajero.getTexto();
		if (cedStr.empty()) {
			textoResultadoAVL = "Ingresa la cedula del pasajero.";
			return;
		}
		int cedula = Texto::aEntero(cedStr);
		ElementoAVL resultado;
		if (app.getSistema().getAvlPasajeros().buscar(cedula, resultado)) {
			textoResultadoAVL = "PASAJERO REGISTRADO: " + resultado.nombre + " (Cedula: " + to_string(resultado.id) + ") | Detalle: " + resultado.detalle;
		} else {
			textoResultadoAVL = "El pasajero con cedula " + cedStr + " NO se encuentra en el Arbol AVL.";
		}
	}  else if (btnVerArbolAVL.fueClickeado(evento)) {
		bool visible = !app.getMostrarVistaArbol();
		app.setMostrarVistaArbol(visible);
		if (visible) {
			NodoVisual nodos[MAX_RESERVAS];
			int raiz = 0;
			int cant = app.getSistema().getAvlPasajeros().exportarVisual(nodos, MAX_RESERVAS, raiz);
			app.getVistaArbol().cargarArbol(nodos, cant, raiz, "Arbol AVL de Pasajeros Registrados (Balanceado)", true);
		}
	} else if (btnPreordenAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Preorden: " + app.getSistema().getAvlPasajeros().preorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(app.getSistema().getAvlPasajeros().tamanio(), 0.5f);
		}
	} else if (btnInordenAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Inorden: " + app.getSistema().getAvlPasajeros().inorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(app.getSistema().getAvlPasajeros().tamanio(), 0.5f);
		}
	} else if (btnPostordenAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Postorden: " + app.getSistema().getAvlPasajeros().postorden();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(app.getSistema().getAvlPasajeros().tamanio(), 0.5f);
		}
	} else if (btnNivelesAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Por Niveles (Anchura): " + app.getSistema().getAvlPasajeros().anchura();
		if (app.getMostrarVistaArbol()) {
			app.getAnimacion().iniciarRecorridoArbol(app.getSistema().getAvlPasajeros().tamanio(), 0.5f);
		}
	}
}

void PantallasAdmin::procesarMST(const sf::Event& evento, App& app) {
	if (btnPrimCosto.fueClickeado(evento)) {
		ultimoMST = app.getSistema().obtenerRedPrim();
		mstCalculado = true;
		app.setMostrarVistaArbol(false);
		app.getVistaMapa().setMST(ultimoMST);
		textoInfoMST = "Prim (Minimo Costo): Costo Total $" + to_string((int)ultimoMST.costoTotal) + 
			" | Duracion Red: " + to_string((int)ultimoMST.duracionTotal) + " min | Conexiones: " + to_string(ultimoMST.cantidadAristas);
		textoRecorridoMST = "Inorden Prim: " + ultimoMST.inorden;
	} else if (btnKruskalTiempo.fueClickeado(evento)) {
		ultimoMST = app.getSistema().obtenerRedKruskal();
		mstCalculado = true;
		app.setMostrarVistaArbol(false);
		app.getVistaMapa().setMST(ultimoMST);
		textoInfoMST = "Kruskal (Minimo Tiempo): Duracion Total " + to_string((int)ultimoMST.duracionTotal) + 
			" min | Costo Red: $" + to_string((int)ultimoMST.costoTotal) + " | Conexiones: " + to_string(ultimoMST.cantidadAristas);
		textoRecorridoMST = "Inorden Kruskal: " + ultimoMST.inorden;
	} else if (btnLimpiarMST.fueClickeado(evento)) {
		app.getVistaMapa().limpiarRutas();
		mstCalculado = false;
		textoInfoMST = "Mapa limpiado. Selecciona Prim o Kruskal para trazar el arbol de expansion minima.";
		textoRecorridoMST = "";
	} else if (btnMSTPreorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Preorden MST: " + ultimoMST.preorden;
	} else if (btnMSTInorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Inorden MST: " + ultimoMST.inorden;
	} else if (btnMSTPostorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Postorden MST: " + ultimoMST.postorden;
	} else if (btnMSTNiveles.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Por Niveles MST: " + ultimoMST.anchura;
	}
}

void PantallasAdmin::procesarEquipaje(const sf::Event& evento, App& app) {
	if (btnCompararEquipaje.fueClickeado(evento)) {
		int origen = app.getVistaMapa().getOrigen();
		int destino = app.getVistaMapa().getDestino();
		const Grafo& grafo = app.getSistema().getGrafo();
		
		if (origen == -1 || destino == -1) {
			textoInfoEquipaje = "Selecciona dos ciudades en el mapa (clic en origen y destino) para comparar.";
			return;
		}
		
		compPasajero = Dijkstra::calcularRuta(grafo, origen, destino, 1);
		compEquipaje = Dijkstra::calcularRutaEquipaje(grafo, origen, destino, 0, compPasajero);
		app.getVistaMapa().setRutas(compPasajero, compEquipaje);
		
		Ciudad cO = grafo.getCiudad(origen);
		Ciudad cD = grafo.getCiudad(destino);
		textoInfoEquipaje = "Comparativa: " + cO.nombre + " -> " + cD.nombre + " | Pasajero por Menor Tiempo vs Equipaje por Menor Costo";
		
		if (compPasajero.existe) {
			textoComparativa = "Pasajero (Cian): " + formatearRuta(grafo, compPasajero) + 
				" | " + to_string((int)compPasajero.duracionTotal) + " min ($" + to_string((int)compPasajero.costoTotal) + ")\n" +
				"Equipaje (Naranja): " + formatearRuta(grafo, compEquipaje) + 
				" | $" + to_string((int)compEquipaje.costoTotal) + " (" + to_string((int)compEquipaje.duracionTotal) + " min)";
			
			double ahorro = compPasajero.costoTotal - compEquipaje.costoTotal;
			if (ahorro > 0.0) {
				textoAhorro = "Ahorro para la aerolinea al enviar maletas por ruta economica: $" + to_string((int)ahorro);
			} else {
				textoAhorro = "La ruta mas rapida coincide con la mas economica (sin escalas adicionales).";
			}
		}
	} else if (btnAnimarEquipaje.fueClickeado(evento)) {
		if (compPasajero.existe) {
			app.getAnimacion().iniciarVuelo(compPasajero, compEquipaje, app.getSistema().getGrafo());
		}
	}
}

void PantallasAdmin::procesarEvento(const sf::Event& evento, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		procesarFlota(evento, app);
	} else if (tab == PESTANA_AVL_PASAJEROS) {
		procesarAVL(evento, app);
	} else if (tab == PESTANA_MST_EXPANSION) {
		procesarMST(evento, app);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		procesarEquipaje(evento, app);
	}
}

void PantallasAdmin::actualizar(sf::Vector2f posMouse, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		btnFlotaPrev.actualizar(posMouse);
		btnFlotaNext.actualizar(posMouse);
	} else if (tab == PESTANA_AVL_PASAJEROS) {
		btnBuscarPasajero.actualizar(posMouse);
		btnVerArbolAVL.actualizar(posMouse);
		btnPreordenAVL.actualizar(posMouse);
		btnInordenAVL.actualizar(posMouse);
		btnPostordenAVL.actualizar(posMouse);
		btnNivelesAVL.actualizar(posMouse);
	} else if (tab == PESTANA_MST_EXPANSION) {
		btnPrimCosto.actualizar(posMouse);
		btnKruskalTiempo.actualizar(posMouse);
		btnLimpiarMST.actualizar(posMouse);
		btnMSTPreorden.actualizar(posMouse);
		btnMSTInorden.actualizar(posMouse);
		btnMSTPostorden.actualizar(posMouse);
		btnMSTNiveles.actualizar(posMouse);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		btnCompararEquipaje.actualizar(posMouse);
		btnAnimarEquipaje.actualizar(posMouse);
	}
}

void PantallasAdmin::dibujarPantallaFlota(sf::RenderWindow& ventana, App& app) {
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: GESTION DE FLOTA, TRIPULACION Y VUELOS", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	btnFlotaPrev.dibujar(ventana);
	btnFlotaNext.dibujar(ventana);
	Dibujo::dibujarTexto(ventana, textoInfoFlota, 365.0f, 577.0f, 11, Dibujo::COLOR_TEXTO_MUTED);
	
	Dibujo::dibujarTexto(ventana, "AERONAVES ACTIVAS:", 270.0f, 610.0f, 11, Dibujo::COLOR_CIAN_ACENTO);
	int cantAero = app.getSistema().getCantidadAeronaves();
	int startAero = flotaPagina * 3;
	for (int i = 0; i < 3 && (startAero + i) < cantAero; i++) {
		Aeronave a = app.getSistema().getAeronave(startAero + i);
		string info = "[" + a.codigo + "] " + a.modelo + " (" + to_string(a.capacidad) + " pas)";
		Dibujo::dibujarTexto(ventana, info, 270.0f, 630.0f + (i * 20.0f), 10, Dibujo::COLOR_TEXTO_CUERPO);
	}
	
	Dibujo::dibujarTexto(ventana, "TRIPULACION DESTACADA:", 570.0f, 610.0f, 11, Dibujo::COLOR_VERDE_EXITO);
	int cantTrip = app.getSistema().getCantidadTripulantes();
	for (int i = 0; i < 3 && i < cantTrip; i++) {
		Tripulante t = app.getSistema().getTripulante(i);
		string info = t.nombre + " - " + t.rol;
		Dibujo::dibujarTexto(ventana, info, 570.0f, 630.0f + (i * 20.0f), 10, Dibujo::COLOR_TEXTO_CUERPO);
	}
	
	Dibujo::dibujarTexto(ventana, "VUELOS PROGRAMADOS:", 870.0f, 610.0f, 11, sf::Color(192, 132, 252));
	int cantVuel = app.getSistema().getCantidadVuelos();
	for (int i = 0; i < 3 && i < cantVuel; i++) {
		Vuelo v = app.getSistema().getVuelo(i);
		string info = "[" + v.codigo + "] " + v.origen + " -> " + v.destino + " ($" + to_string((int)v.costo) + ")";
		Dibujo::dibujarTexto(ventana, info, 870.0f, 630.0f + (i * 20.0f), 10, Dibujo::COLOR_TEXTO_CUERPO);
	}
}

void PantallasAdmin::dibujarPantallaAVL(sf::RenderWindow& ventana, App& /*app*/) {
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: ARBOL AVL DE PASAJEROS REGISTRADOS", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	txtBuscarPasajero.dibujar(ventana);
	btnBuscarPasajero.dibujar(ventana);
	btnVerArbolAVL.dibujar(ventana);
	
	btnPreordenAVL.dibujar(ventana);
	btnInordenAVL.dibujar(ventana);
	btnPostordenAVL.dibujar(ventana);
	btnNivelesAVL.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoResultadoAVL, 270.0f, 615.0f, 12, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, textoRecorridoAVL, 270.0f, 645.0f, 11, sf::Color(192, 132, 252));
	Dibujo::dibujarTexto(ventana, "Tip: El arbol AVL garantiza balance automatico O(log n) con rotaciones simples y dobles.", 270.0f, 685.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasAdmin::dibujarPantallaMST(sf::RenderWindow& ventana, App& /*app*/) {
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: ARBOLES DE EXPANSION MINIMA (PRIM Y KRUSKAL)", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	btnPrimCosto.dibujar(ventana);
	btnKruskalTiempo.dibujar(ventana);
	btnLimpiarMST.dibujar(ventana);
	
	btnMSTPreorden.dibujar(ventana);
	btnMSTInorden.dibujar(ventana);
	btnMSTPostorden.dibujar(ventana);
	btnMSTNiveles.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoInfoMST, 270.0f, 615.0f, 12, sf::Color(192, 132, 252));
	Dibujo::dibujarTexto(ventana, textoRecorridoMST, 270.0f, 645.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	Dibujo::dibujarTexto(ventana, "Tip: La red morada en el mapa muestra todas las conexiones optimas sin ciclos conectando las ciudades.", 270.0f, 685.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasAdmin::dibujarPantallaEquipaje(sf::RenderWindow& ventana, App& /*app*/) {
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: COMPARATIVA LOGISTICA DE EQUIPAJE VS TIEMPO", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	btnCompararEquipaje.dibujar(ventana);
	btnAnimarEquipaje.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoInfoEquipaje, 600.0f, 577.0f, 11, Dibujo::COLOR_TEXTO_MUTED);
	Dibujo::dibujarTexto(ventana, textoComparativa, 270.0f, 615.0f, 11, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, textoAhorro, 270.0f, 665.0f, 12, Dibujo::COLOR_VERDE_EXITO);
	Dibujo::dibujarTexto(ventana, "Tip: El avion cian vuela por la ruta rapida; el naranja transporta las maletas por menor costo.", 270.0f, 688.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasAdmin::dibujar(sf::RenderWindow& ventana, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		dibujarPantallaFlota(ventana, app);
	} else if (tab == PESTANA_AVL_PASAJEROS) {
		dibujarPantallaAVL(ventana, app);
	} else if (tab == PESTANA_MST_EXPANSION) {
		dibujarPantallaMST(ventana, app);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		dibujarPantallaEquipaje(ventana, app);
	}
}
