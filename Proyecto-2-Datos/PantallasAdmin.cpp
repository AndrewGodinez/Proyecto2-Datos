#include "PantallasAdmin.h"
#include "App.h"
#include "Dibujo.h"
#include "Dijkstra.h"
#include "Texto.h"
#include "Modelos.h"

PantallasAdmin::PantallasAdmin() {
	mstCalculado = false;
	ultimoMST.conectado = false;
	compPasajero.existe = false;
	compEquipaje.existe = false;
	
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
	txtBuscarPasajero = CajaTexto(270.0f, 572.0f, 190.0f, 28.0f, "Cedula pasajero...", 15);
	btnBuscarPasajero = Boton(470.0f, 572.0f, 90.0f, 28.0f, "Buscar", 
							  sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnVerArbolAVL = Boton(570.0f, 572.0f, 130.0f, 28.0f, "Ver / Ocultar AVL", 
						   sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
	btnPreordenAVL = Boton(710.0f, 572.0f, 115.0f, 28.0f, "Preorden");
	btnInordenAVL = Boton(835.0f, 572.0f, 115.0f, 28.0f, "Inorden");
	btnPostordenAVL = Boton(960.0f, 572.0f, 115.0f, 28.0f, "Postorden");
	btnNivelesAVL = Boton(1085.0f, 572.0f, 115.0f, 28.0f, "Por Niveles");
	txtVueloAVL = CajaTexto(270.0f, 606.0f, 190.0f, 26.0f, "Codigo vuelo (ej. VU101)", 10);
	btnVerificarVuelo = Boton(470.0f, 606.0f, 150.0f, 26.0f, "Esta en el vuelo?",
							  sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	
	btnPrimCosto = Boton(270.0f, 570.0f, 160.0f, 28.0f, "Prim (Menor Costo)", 
						 sf::Color(14, 55, 75), sf::Color(20, 80, 110), Dibujo::COLOR_CIAN_ACENTO);
	btnKruskalTiempo = Boton(440.0f, 570.0f, 170.0f, 28.0f, "Kruskal (Menor Tiempo)", 
							 sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
	btnLimpiarMST = Boton(620.0f, 570.0f, 110.0f, 28.0f, "Limpiar Mapa", 
						  sf::Color(24, 34, 52), sf::Color(38, 52, 78));
	btnVerArbolMST = Boton(270.0f, 604.0f, 160.0f, 26.0f, "Ver / Ocultar Arbol",
						   sf::Color(36, 26, 60), sf::Color(55, 40, 90), sf::Color(192, 132, 252));
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

void PantallasAdmin::procesarAVL(const sf::Event& evento, App& app) {
	txtBuscarPasajero.procesarEvento(evento);
	txtVueloAVL.procesarEvento(evento);
	
	if (btnBuscarPasajero.fueClickeado(evento)) {
		string cedStr = txtBuscarPasajero.getTexto();
		if (cedStr.empty()) {
			textoResultadoAVL = "Ingresa la cedula del pasajero.";
			return;
		}
		int cedula = Texto::aEntero(cedStr);
		ElementoAVL resultado;
		if (app.getSistema().getAvlPasajeros().buscar(cedula, resultado)) {
			textoResultadoAVL = "PASAJERO: " + resultado.nombre + " (Cedula: " + to_string(resultado.id) + ") | Reservas: " + app.getSistema().getAvlPasajeros().reservasDe(cedula);
		} else {
			textoResultadoAVL = "El pasajero con cedula " + cedStr + " NO se encuentra en el Arbol AVL.";
		}
	} else if (btnVerificarVuelo.fueClickeado(evento)) {
		int cedula = Texto::aEntero(txtBuscarPasajero.getTexto());
		string vuelo = Texto::mayusculas(Texto::limpiarEspacios(txtVueloAVL.getTexto()));
		if (cedula == 0 || vuelo.empty()) {
			textoResultadoAVL = "Ingresa la cedula y el codigo del vuelo.";
		} else if (app.getSistema().getAvlPasajeros().estaEnVuelo(cedula, vuelo)) {
			textoResultadoAVL = "SI: la cedula " + to_string(cedula) + " esta asignada al vuelo " + vuelo + ".";
		} else {
			textoResultadoAVL = "NO: la cedula " + to_string(cedula) + " no esta asignada al vuelo " + vuelo + ".";
		}
	} else if (btnVerArbolAVL.fueClickeado(evento)) {
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
		app.animarRecorridoArbol(RECORRIDO_PREORDEN);
	} else if (btnInordenAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Inorden: " + app.getSistema().getAvlPasajeros().inorden();
		app.animarRecorridoArbol(RECORRIDO_INORDEN);
	} else if (btnPostordenAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Postorden: " + app.getSistema().getAvlPasajeros().postorden();
		app.animarRecorridoArbol(RECORRIDO_POSTORDEN);
	} else if (btnNivelesAVL.fueClickeado(evento)) {
		textoRecorridoAVL = "Por Niveles (Anchura): " + app.getSistema().getAvlPasajeros().anchura();
		app.animarRecorridoArbol(RECORRIDO_NIVELES);
	}
}

void PantallasAdmin::procesarMST(const sf::Event& evento, App& app) {
	int raizMST = app.getVistaMapa().getOrigen();
	if (raizMST == -1) {
		raizMST = 0;
	}
	if (btnPrimCosto.fueClickeado(evento)) {
		ultimoMST = app.getSistema().obtenerRedPrim(raizMST);
		mstCalculado = true;
		app.setMostrarVistaArbol(false);
		app.getVistaMapa().setMST(ultimoMST);
		textoInfoMST = "Prim (Minimo Costo): Costo Total $" + to_string((int)ultimoMST.costoTotal) + 
			" | Duracion Red: " + Texto::formatoHoras(ultimoMST.duracionTotal) + " | Conexiones: " + to_string(ultimoMST.cantidadAristas);
		textoRecorridoMST = "Inorden Prim: " + ultimoMST.inorden;
	} else if (btnKruskalTiempo.fueClickeado(evento)) {
		ultimoMST = app.getSistema().obtenerRedKruskal(raizMST);
		mstCalculado = true;
		app.setMostrarVistaArbol(false);
		app.getVistaMapa().setMST(ultimoMST);
		textoInfoMST = "Kruskal (Minimo Tiempo): Duracion Total " + Texto::formatoHoras(ultimoMST.duracionTotal) +
			" | Costo Red: $" + to_string((int)ultimoMST.costoTotal) + " | Conexiones: " + to_string(ultimoMST.cantidadAristas);
		textoRecorridoMST = "Inorden Kruskal: " + ultimoMST.inorden;
	} else if (btnLimpiarMST.fueClickeado(evento)) {
		app.getVistaMapa().limpiarRutas();
		app.setMostrarVistaArbol(false);
		mstCalculado = false;
		textoInfoMST = "Mapa limpiado. Selecciona Prim o Kruskal para trazar el arbol de expansion minima.";
		textoRecorridoMST = "";
	} else if (btnVerArbolMST.fueClickeado(evento)) {
		if (mstCalculado && ultimoMST.conectado) {
			bool visible = !app.getMostrarVistaArbol();
			app.setMostrarVistaArbol(visible);
			if (visible) {
				int cantidad = app.getSistema().getGrafo().getCantidadCiudades();
				app.getVistaArbol().cargarArbol(ultimoMST.visual, cantidad, ultimoMST.raiz, "Arbol de Expansion Minima (raiz: " + ultimoMST.visual[ultimoMST.raiz].etiqueta + ")", false, true);
			}
		}
	} else if (btnMSTPreorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Preorden MST: " + ultimoMST.preorden;
		if (mstCalculado) app.animarRecorridoArbol(RECORRIDO_PREORDEN);
	} else if (btnMSTInorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Inorden MST: " + ultimoMST.inorden;
		if (mstCalculado) app.animarRecorridoArbol(RECORRIDO_INORDEN);
	} else if (btnMSTPostorden.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Postorden MST: " + ultimoMST.postorden;
		if (mstCalculado) app.animarRecorridoArbol(RECORRIDO_POSTORDEN);
	} else if (btnMSTNiveles.fueClickeado(evento)) {
		if (mstCalculado) textoRecorridoMST = "Por Niveles MST: " + ultimoMST.anchura;
		if (mstCalculado) app.animarRecorridoArbol(RECORRIDO_NIVELES);
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
		
		compPasajero = Dijkstra::calcularRuta(grafo, origen, destino, CRITERIO_DURACION);
		compEquipaje = Dijkstra::calcularRutaEquipaje(grafo, origen, destino, CRITERIO_COSTO, compPasajero);
		app.getVistaMapa().setRutas(compPasajero, compEquipaje);
		
		Ciudad cO = grafo.getCiudad(origen);
		Ciudad cD = grafo.getCiudad(destino);
		textoInfoEquipaje = "Comparativa: " + cO.nombre + " -> " + cD.nombre + " | Pasajero por Menor Tiempo vs Equipaje por Menor Costo";
		
		if (compPasajero.existe) {
			textoComparativa = "Pasajero (Cian): " + formatearRuta(grafo, compPasajero) + 
				" | " + Texto::formatoHoras(compPasajero.duracionTotal) + " ($" + to_string((int)compPasajero.costoTotal) + ")\n" +
				"Equipaje (Naranja): " + formatearRuta(grafo, compEquipaje) + 
				" | $" + to_string((int)compEquipaje.costoTotal) + " (" + Texto::formatoHoras(compEquipaje.duracionTotal) + ")";
			
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
	if (tab == PESTANA_AVL_PASAJEROS) {
		procesarAVL(evento, app);
	} else if (tab == PESTANA_MST_EXPANSION) {
		procesarMST(evento, app);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		procesarEquipaje(evento, app);
	}
}

void PantallasAdmin::actualizar(sf::Vector2f posMouse, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_AVL_PASAJEROS) {
		btnBuscarPasajero.actualizar(posMouse);
		btnVerArbolAVL.actualizar(posMouse);
		btnPreordenAVL.actualizar(posMouse);
		btnInordenAVL.actualizar(posMouse);
		btnPostordenAVL.actualizar(posMouse);
		btnNivelesAVL.actualizar(posMouse);
		btnVerificarVuelo.actualizar(posMouse);
	} else if (tab == PESTANA_MST_EXPANSION) {
		btnPrimCosto.actualizar(posMouse);
		btnKruskalTiempo.actualizar(posMouse);
		btnLimpiarMST.actualizar(posMouse);
		btnVerArbolMST.actualizar(posMouse);
		btnMSTPreorden.actualizar(posMouse);
		btnMSTInorden.actualizar(posMouse);
		btnMSTPostorden.actualizar(posMouse);
		btnMSTNiveles.actualizar(posMouse);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		btnCompararEquipaje.actualizar(posMouse);
		btnAnimarEquipaje.actualizar(posMouse);
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
	txtVueloAVL.dibujar(ventana);
	btnVerificarVuelo.dibujar(ventana);

	Dibujo::dibujarTexto(ventana, textoResultadoAVL, 270.0f, 640.0f, 12, Dibujo::COLOR_TEXTO_TITULO);
	Dibujo::dibujarTexto(ventana, textoRecorridoAVL, 270.0f, 664.0f, 11, sf::Color(192, 132, 252));
	Dibujo::dibujarTexto(ventana, "Tip: El arbol AVL garantiza balance automatico O(log n) con rotaciones simples y dobles.", 270.0f, 685.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasAdmin::dibujarPantallaMST(sf::RenderWindow& ventana, App& /*app*/) {
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: ARBOLES DE EXPANSION MINIMA (PRIM Y KRUSKAL)", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	
	btnPrimCosto.dibujar(ventana);
	btnKruskalTiempo.dibujar(ventana);
	btnLimpiarMST.dibujar(ventana);
	btnVerArbolMST.dibujar(ventana);
		
	btnMSTPreorden.dibujar(ventana);
	btnMSTInorden.dibujar(ventana);
	btnMSTPostorden.dibujar(ventana);
	btnMSTNiveles.dibujar(ventana);
	
	Dibujo::dibujarTexto(ventana, textoInfoMST, 270.0f, 640.0f, 12, sf::Color(192, 132, 252));
	Dibujo::dibujarTexto(ventana, textoRecorridoMST, 270.0f, 664.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
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
	if (tab == PESTANA_AVL_PASAJEROS) {
		dibujarPantallaAVL(ventana, app);
	} else if (tab == PESTANA_MST_EXPANSION) {
		dibujarPantallaMST(ventana, app);
	} else if (tab == PESTANA_EQUIPAJE_COMPARATIVA) {
		dibujarPantallaEquipaje(ventana, app);
	}
}
