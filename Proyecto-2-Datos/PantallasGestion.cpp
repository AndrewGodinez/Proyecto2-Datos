#include "PantallasGestion.h"
#include "App.h"
#include "Dibujo.h"
#include "Texto.h"
#include "Modelos.h"

PantallasGestion::PantallasGestion() {
	flotaPagina = 0;
	vuelosPagina = 0;
	textoFlota = "Registra aeronaves y tripulantes, o asigna un tripulante (ID) a una aeronave.";
	textoCiudades = "Clic en zona vacia del mapa para ubicar una ciudad nueva, o en dos ciudades para su ruta.";
	textoVuelos = "Selecciona origen y destino en el mapa para programar un vuelo en esa ruta.";
	inicializarControles();
}

void PantallasGestion::inicializarControles() {
	sf::Color fondo(24, 34, 52);
	sf::Color hover(38, 52, 78);
	sf::Color fondoVerde(16, 50, 36);
	sf::Color hoverVerde(22, 75, 52);
	sf::Color fondoRojo(60, 22, 26);
	sf::Color hoverRojo(90, 30, 36);

	txtCodigoAeronave = CajaTexto(270.0f, 572.0f, 70.0f, 28.0f, "Codigo", 6);
	txtPlaca = CajaTexto(345.0f, 572.0f, 80.0f, 28.0f, "Placa", 8);
	txtMarca = CajaTexto(430.0f, 572.0f, 95.0f, 28.0f, "Marca", 12);
	txtModelo = CajaTexto(530.0f, 572.0f, 130.0f, 28.0f, "Modelo", 20);
	txtCapacidad = CajaTexto(665.0f, 572.0f, 75.0f, 28.0f, "Asientos", 4);
	btnRegistrarAeronave = Boton(745.0f, 572.0f, 160.0f, 28.0f, "Registrar Aeronave", fondoVerde, hoverVerde, Dibujo::COLOR_VERDE_EXITO);
	txtIdTripulante = CajaTexto(270.0f, 606.0f, 70.0f, 28.0f, "ID", 6);
	txtNombreTripulante = CajaTexto(345.0f, 606.0f, 160.0f, 28.0f, "Nombre", 22);
	txtRol = CajaTexto(510.0f, 606.0f, 110.0f, 28.0f, "Rol", 16);
	btnRegistrarTripulante = Boton(625.0f, 606.0f, 160.0f, 28.0f, "Registrar Tripulante", fondoVerde, hoverVerde, Dibujo::COLOR_VERDE_EXITO);
	txtAeronaveAsignar = CajaTexto(790.0f, 606.0f, 90.0f, 28.0f, "Aeronave", 6);
	btnAsignar = Boton(885.0f, 606.0f, 170.0f, 28.0f, "Asignar ID a Aeronave", fondo, hover);
	btnFlotaPrev = Boton(1150.0f, 606.0f, 36.0f, 28.0f, "<", fondo, hover);
	btnFlotaNext = Boton(1192.0f, 606.0f, 36.0f, 28.0f, ">", fondo, hover);

	txtCodigoCiudad = CajaTexto(270.0f, 572.0f, 90.0f, 28.0f, "Codigo", 4);
	txtNombreCiudad = CajaTexto(370.0f, 572.0f, 200.0f, 28.0f, "Nombre de la ciudad", 24);
	btnAgregarCiudad = Boton(580.0f, 572.0f, 230.0f, 28.0f, "Agregar Ciudad en el punto +", fondoVerde, hoverVerde, Dibujo::COLOR_VERDE_EXITO);
	txtCosto = CajaTexto(270.0f, 606.0f, 110.0f, 28.0f, "Costo $", 8);
	txtDuracion = CajaTexto(390.0f, 606.0f, 110.0f, 28.0f, "Duracion h", 6);
	btnGuardarRuta = Boton(510.0f, 606.0f, 200.0f, 28.0f, "Guardar Ruta Origen->Destino", fondoVerde, hoverVerde, Dibujo::COLOR_VERDE_EXITO);
	btnEliminarRuta = Boton(720.0f, 606.0f, 200.0f, 28.0f, "Eliminar Ruta Origen->Destino", fondoRojo, hoverRojo, Dibujo::COLOR_ROJO_ALERTA);

	txtCodigoVuelo = CajaTexto(270.0f, 572.0f, 90.0f, 28.0f, "Codigo", 6);
	txtHora = CajaTexto(365.0f, 572.0f, 80.0f, 28.0f, "Hora", 5);
	txtAeronaveVuelo = CajaTexto(450.0f, 572.0f, 95.0f, 28.0f, "Aeronave", 6);
	btnProgramar = Boton(550.0f, 572.0f, 230.0f, 28.0f, "Programar Vuelo Origen->Destino", fondoVerde, hoverVerde, Dibujo::COLOR_VERDE_EXITO);
	txtVueloConsulta = CajaTexto(270.0f, 606.0f, 90.0f, 28.0f, "Vuelo", 6);
	btnPasajeros = Boton(365.0f, 606.0f, 140.0f, 28.0f, "Ver Pasajeros", fondo, hover);
	txtIdReserva = CajaTexto(515.0f, 606.0f, 100.0f, 28.0f, "N. reserva", 5);
	btnCancelar = Boton(620.0f, 606.0f, 150.0f, 28.0f, "Cancelar Reserva", fondoRojo, hoverRojo, Dibujo::COLOR_ROJO_ALERTA);
	btnVuelosPrev = Boton(1150.0f, 606.0f, 36.0f, 28.0f, "<", fondo, hover);
	btnVuelosNext = Boton(1192.0f, 606.0f, 36.0f, 28.0f, ">", fondo, hover);
}

void PantallasGestion::procesarFlota(const sf::Event& evento, App& app) {
	txtCodigoAeronave.procesarEvento(evento);
	txtPlaca.procesarEvento(evento);
	txtMarca.procesarEvento(evento);
	txtModelo.procesarEvento(evento);
	txtCapacidad.procesarEvento(evento);
	txtIdTripulante.procesarEvento(evento);
	txtNombreTripulante.procesarEvento(evento);
	txtRol.procesarEvento(evento);
	txtAeronaveAsignar.procesarEvento(evento);
	Aerolinea& sistema = app.getSistema();

	if (btnRegistrarAeronave.fueClickeado(evento)) {
		string codigo = Texto::mayusculas(Texto::limpiarEspacios(txtCodigoAeronave.getTexto()));
		string placa = Texto::mayusculas(Texto::limpiarEspacios(txtPlaca.getTexto()));
		if (codigo.empty() || placa.empty() || txtMarca.getTexto().empty() || txtModelo.getTexto().empty()) {
			textoFlota = "Completa codigo, placa, marca, modelo y asientos.";
		} else if (sistema.registrarAeronave(codigo, placa, txtMarca.getTexto(), txtModelo.getTexto(), Texto::aEntero(txtCapacidad.getTexto()), "Operativo")) {
			textoFlota = "Aeronave " + codigo + " registrada.";
			txtCodigoAeronave.limpiar();
			txtPlaca.limpiar();
			txtMarca.limpiar();
			txtModelo.limpiar();
			txtCapacidad.limpiar();
		} else {
			textoFlota = "No se pudo registrar: codigo repetido o asientos invalidos.";
		}
	} else if (btnRegistrarTripulante.fueClickeado(evento)) {
		string id = Texto::mayusculas(Texto::limpiarEspacios(txtIdTripulante.getTexto()));
		if (id.empty() || txtNombreTripulante.getTexto().empty() || txtRol.getTexto().empty()) {
			textoFlota = "Completa ID, nombre y rol del tripulante.";
		} else if (sistema.registrarTripulante(id, txtNombreTripulante.getTexto(), txtRol.getTexto())) {
			textoFlota = "Tripulante " + id + " registrado.";
			txtNombreTripulante.limpiar();
			txtRol.limpiar();
		} else {
			textoFlota = "No se pudo registrar: el ID ya existe.";
		}
	} else if (btnAsignar.fueClickeado(evento)) {
		string id = Texto::mayusculas(Texto::limpiarEspacios(txtIdTripulante.getTexto()));
		string aeronave = Texto::mayusculas(Texto::limpiarEspacios(txtAeronaveAsignar.getTexto()));
		if (sistema.asignarTripulanteAAeronave(id, aeronave)) {
			textoFlota = "Tripulante " + id + " asignado a la aeronave " + aeronave + ".";
		} else {
			textoFlota = "No se pudo asignar: revisa que existan el tripulante y la aeronave.";
		}
	} else if (btnFlotaPrev.fueClickeado(evento)) {
		if (flotaPagina > 0) flotaPagina--;
	} else if (btnFlotaNext.fueClickeado(evento)) {
		if ((flotaPagina + 1) * 2 < sistema.getCantidadAeronaves()) flotaPagina++;
	}
}

void PantallasGestion::procesarCiudades(const sf::Event& evento, App& app) {
	txtCodigoCiudad.procesarEvento(evento);
	txtNombreCiudad.procesarEvento(evento);
	txtCosto.procesarEvento(evento);
	txtDuracion.procesarEvento(evento);
	Aerolinea& sistema = app.getSistema();
	VistaMapa& mapa = app.getVistaMapa();
	const Grafo& grafo = sistema.getGrafo();

	if (btnAgregarCiudad.fueClickeado(evento)) {
		float x = 0.0f;
		float y = 0.0f;
		string codigo = Texto::mayusculas(Texto::limpiarEspacios(txtCodigoCiudad.getTexto()));
		string nombre = Texto::limpiarEspacios(txtNombreCiudad.getTexto());
		if (!mapa.getPuntoNuevo(grafo, x, y)) {
			textoCiudades = "Primero haz clic en una zona vacia del mapa para ubicar la ciudad.";
		} else if (codigo.empty() || nombre.empty()) {
			textoCiudades = "Ingresa el codigo y el nombre de la ciudad.";
		} else if (sistema.registrarCiudad(codigo, nombre, x, y)) {
			textoCiudades = "Ciudad " + nombre + " [" + codigo + "] agregada al grafo.";
			txtCodigoCiudad.limpiar();
			txtNombreCiudad.limpiar();
			mapa.limpiarSeleccion();
		} else {
			textoCiudades = "No se pudo agregar: el codigo ya existe o el grafo esta lleno.";
		}
	} else if (btnGuardarRuta.fueClickeado(evento) || btnEliminarRuta.fueClickeado(evento)) {
		int origen = mapa.getOrigen();
		int destino = mapa.getDestino();
		if (origen == -1 || destino == -1) {
			textoCiudades = "Selecciona ORIGEN y DESTINO en el mapa.";
			return;
		}
		string codO = grafo.getCiudad(origen).codigo;
		string codD = grafo.getCiudad(destino).codigo;
		if (btnGuardarRuta.fueClickeado(evento)) {
			if (sistema.registrarRuta(codO, codD, Texto::aDecimal(txtCosto.getTexto()), Texto::aDecimal(txtDuracion.getTexto()))) {
				textoCiudades = "Ruta " + codO + " -> " + codD + " guardada.";
			} else {
				textoCiudades = "Costo y duracion deben ser mayores que 0.";
			}
		} else if (sistema.eliminarRuta(codO, codD)) {
			textoCiudades = "Ruta " + codO + " -> " + codD + " eliminada.";
		} else {
			textoCiudades = "La ruta " + codO + " -> " + codD + " no existe.";
		}
	}
}

void PantallasGestion::procesarVuelos(const sf::Event& evento, App& app) {
	txtCodigoVuelo.procesarEvento(evento);
	txtHora.procesarEvento(evento);
	txtAeronaveVuelo.procesarEvento(evento);
	txtVueloConsulta.procesarEvento(evento);
	txtIdReserva.procesarEvento(evento);
	Aerolinea& sistema = app.getSistema();
	const Grafo& grafo = sistema.getGrafo();

	if (btnProgramar.fueClickeado(evento)) {
		int origen = app.getVistaMapa().getOrigen();
		int destino = app.getVistaMapa().getDestino();
		string codigo = Texto::mayusculas(Texto::limpiarEspacios(txtCodigoVuelo.getTexto()));
		if (origen == -1 || destino == -1 || !grafo.existeRuta(origen, destino)) {
			textoVuelos = "Selecciona en el mapa un origen y un destino que tengan ruta.";
			return;
		}
		if (codigo.empty()) {
			textoVuelos = "Ingresa el codigo del vuelo.";
			return;
		}
		string codO = grafo.getCiudad(origen).codigo;
		string codD = grafo.getCiudad(destino).codigo;
		string aeronave = Texto::mayusculas(Texto::limpiarEspacios(txtAeronaveVuelo.getTexto()));
		if (sistema.programarVuelo(codigo, codO, codD, txtHora.getTexto(), grafo.getCostoRuta(origen, destino), grafo.getDuracionRuta(origen, destino), aeronave)) {
			textoVuelos = "Vuelo " + codigo + " programado: " + codO + " -> " + codD + " con " + aeronave + ".";
			txtCodigoVuelo.limpiar();
			txtHora.limpiar();
		} else {
			textoVuelos = "No se pudo programar: codigo repetido, aeronave inexistente o en mantenimiento.";
		}
	} else if (btnPasajeros.fueClickeado(evento)) {
		string codigo = Texto::mayusculas(Texto::limpiarEspacios(txtVueloConsulta.getTexto()));
		if (sistema.buscarVuelo(codigo) == -1) {
			textoVuelos = "No existe el vuelo " + codigo + ".";
			return;
		}
		string pasajeros = sistema.pasajerosDeVuelo(codigo);
		if (pasajeros.empty()) {
			pasajeros = "sin pasajeros con reserva";
		}
		textoVuelos = "Pasajeros de " + codigo + ": " + pasajeros;
	} else if (btnCancelar.fueClickeado(evento)) {
		int idReserva = Texto::aEntero(txtIdReserva.getTexto());
		if (sistema.cancelarReserva(idReserva)) {
			textoVuelos = "Reserva #" + to_string(idReserva) + " cancelada. Se liberaron sus asientos.";
		} else {
			textoVuelos = "No existe una reserva activa con ese numero.";
		}
	} else if (btnVuelosPrev.fueClickeado(evento)) {
		if (vuelosPagina > 0) vuelosPagina--;
	} else if (btnVuelosNext.fueClickeado(evento)) {
		if ((vuelosPagina + 1) * 6 < sistema.getCantidadVuelos()) vuelosPagina++;
	}
}

void PantallasGestion::procesarEvento(const sf::Event& evento, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		procesarFlota(evento, app);
	} else if (tab == PESTANA_CIUDADES_RUTAS) {
		procesarCiudades(evento, app);
	} else if (tab == PESTANA_VUELOS_PASAJEROS) {
		procesarVuelos(evento, app);
	}
}

void PantallasGestion::actualizar(sf::Vector2f posMouse, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		btnRegistrarAeronave.actualizar(posMouse);
		btnRegistrarTripulante.actualizar(posMouse);
		btnAsignar.actualizar(posMouse);
		btnFlotaPrev.actualizar(posMouse);
		btnFlotaNext.actualizar(posMouse);
	} else if (tab == PESTANA_CIUDADES_RUTAS) {
		btnAgregarCiudad.actualizar(posMouse);
		btnGuardarRuta.actualizar(posMouse);
		btnEliminarRuta.actualizar(posMouse);
	} else if (tab == PESTANA_VUELOS_PASAJEROS) {
		btnProgramar.actualizar(posMouse);
		btnPasajeros.actualizar(posMouse);
		btnCancelar.actualizar(posMouse);
		btnVuelosPrev.actualizar(posMouse);
		btnVuelosNext.actualizar(posMouse);
	}
}

void PantallasGestion::dibujarPantallaFlota(sf::RenderWindow& ventana, App& app) {
	Aerolinea& sistema = app.getSistema();
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: AERONAVES Y TRIPULACION", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	txtCodigoAeronave.dibujar(ventana);
	txtPlaca.dibujar(ventana);
	txtMarca.dibujar(ventana);
	txtModelo.dibujar(ventana);
	txtCapacidad.dibujar(ventana);
	btnRegistrarAeronave.dibujar(ventana);
	txtIdTripulante.dibujar(ventana);
	txtNombreTripulante.dibujar(ventana);
	txtRol.dibujar(ventana);
	btnRegistrarTripulante.dibujar(ventana);
	txtAeronaveAsignar.dibujar(ventana);
	btnAsignar.dibujar(ventana);
	btnFlotaPrev.dibujar(ventana);
	btnFlotaNext.dibujar(ventana);
	Dibujo::dibujarTexto(ventana, textoFlota, 270.0f, 642.0f, 12, Dibujo::COLOR_VERDE_EXITO);

	int inicio = flotaPagina * 2;
	for (int i = inicio; i < inicio + 2 && i < sistema.getCantidadAeronaves(); i++) {
		Aeronave a = sistema.getAeronave(i);
		string tripulacion = "";
		for (int j = 0; j < sistema.getCantidadTripulantes(); j++) {
			Tripulante t = sistema.getTripulante(j);
			if (t.aeronaveAsignada == a.codigo) {
				tripulacion += (tripulacion.empty() ? "" : ", ") + t.nombre + " (" + t.rol + ")";
			}
		}
		if (tripulacion.empty()) {
			tripulacion = "sin asignar";
		}
		string info = "[" + a.codigo + "] " + a.placa + " " + a.marca + " " + a.modelo + " | " + to_string(a.capacidad) +
			" asientos | " + a.estado + " | Tripulacion: " + tripulacion;
		Dibujo::dibujarTexto(ventana, info, 270.0f, 666.0f + (i - inicio) * 22.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	}
}

void PantallasGestion::dibujarPantallaCiudades(sf::RenderWindow& ventana, App& app) {
	const Grafo& grafo = app.getSistema().getGrafo();
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: CIUDADES Y RUTAS DEL GRAFO", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	txtCodigoCiudad.dibujar(ventana);
	txtNombreCiudad.dibujar(ventana);
	btnAgregarCiudad.dibujar(ventana);
	txtCosto.dibujar(ventana);
	txtDuracion.dibujar(ventana);
	btnGuardarRuta.dibujar(ventana);
	btnEliminarRuta.dibujar(ventana);

	int origen = app.getVistaMapa().getOrigen();
	int destino = app.getVistaMapa().getDestino();
	string seleccion = "Ruta seleccionada: haz clic en una ciudad origen y luego en una destino.";
	if (origen != -1 && destino != -1) {
		string tramo = grafo.getCiudad(origen).codigo + " -> " + grafo.getCiudad(destino).codigo;
		if (grafo.existeRuta(origen, destino)) {
			seleccion = "Ruta " + tramo + ": $" + to_string((int)grafo.getCostoRuta(origen, destino)) + " | " +
				Texto::formatoHoras(grafo.getDuracionRuta(origen, destino)) + " (Guardar la modifica)";
		} else {
			seleccion = "Ruta " + tramo + ": no existe todavia (Guardar la crea)";
		}
	}
	Dibujo::dibujarTexto(ventana, seleccion, 270.0f, 645.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	Dibujo::dibujarTexto(ventana, textoCiudades, 270.0f, 667.0f, 12, Dibujo::COLOR_VERDE_EXITO);
	Dibujo::dibujarTexto(ventana, "Tip: la ciudad nueva aparece al instante en el mapa, el ABB y todos los algoritmos.", 270.0f, 692.0f, 10, Dibujo::COLOR_TEXTO_MUTED);
}

void PantallasGestion::dibujarPantallaVuelos(sf::RenderWindow& ventana, App& app) {
	Aerolinea& sistema = app.getSistema();
	Dibujo::dibujarTexto(ventana, "MODULO ADMINISTRATIVO: VUELOS, PASAJEROS Y RESERVAS", 270.0f, 545.0f, 13, Dibujo::COLOR_NARANJA_EQUIPAJE);
	txtCodigoVuelo.dibujar(ventana);
	txtHora.dibujar(ventana);
	txtAeronaveVuelo.dibujar(ventana);
	btnProgramar.dibujar(ventana);
	txtVueloConsulta.dibujar(ventana);
	btnPasajeros.dibujar(ventana);
	txtIdReserva.dibujar(ventana);
	btnCancelar.dibujar(ventana);
	btnVuelosPrev.dibujar(ventana);
	btnVuelosNext.dibujar(ventana);
	Dibujo::dibujarTexto(ventana, textoVuelos, 270.0f, 642.0f, 12, Dibujo::COLOR_VERDE_EXITO);

	int inicio = vuelosPagina * 6;
	for (int i = inicio; i < inicio + 6 && i < sistema.getCantidadVuelos(); i++) {
		Vuelo v = sistema.getVuelo(i);
		int capacidad = 0;
		for (int j = 0; j < sistema.getCantidadAeronaves(); j++) {
			if (sistema.getAeronave(j).codigo == v.codigoAeronave) {
				capacidad = sistema.getAeronave(j).capacidad;
			}
		}
		string info = "[" + v.codigo + "] " + v.origen + " -> " + v.destino + " " + v.fechaHora + " " + v.codigoAeronave +
			" " + to_string(v.asientosOcupados) + "/" + to_string(capacidad);
		int posicion = i - inicio;
		Dibujo::dibujarTexto(ventana, info, 270.0f + (posicion % 3) * 330.0f, 666.0f + (posicion / 3) * 22.0f, 11, Dibujo::COLOR_TEXTO_CUERPO);
	}
}

void PantallasGestion::dibujar(sf::RenderWindow& ventana, App& app) {
	PestanaSistema tab = app.getPestanaActual();
	if (tab == PESTANA_FLOTA_ADMIN) {
		dibujarPantallaFlota(ventana, app);
	} else if (tab == PESTANA_CIUDADES_RUTAS) {
		dibujarPantallaCiudades(ventana, app);
	} else if (tab == PESTANA_VUELOS_PASAJEROS) {
		dibujarPantallaVuelos(ventana, app);
	}
}
