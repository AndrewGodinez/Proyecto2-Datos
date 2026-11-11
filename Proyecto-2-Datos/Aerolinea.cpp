#include "Aerolinea.h"

Aerolinea::Aerolinea() {
	cantidadAeronaves = 0;
	cantidadTripulantes = 0;
	cantidadVuelos = 0;
	cantidadReservas = 0;
}

Aerolinea::~Aerolinea() {
}

string Aerolinea::convertirRutaATexto(const ResultadoRuta& ruta) const {
	string texto = "";
	for (int i = 0; i < ruta.cantidadNodos; i++) {
		if (i > 0) {
			texto += " -> ";
		}
		texto += grafo.getCiudad(ruta.nodos[i]).codigo;
	}
	return texto;
}

int Aerolinea::buscarAeronave(string codigo) const {
	for (int i = 0; i < cantidadAeronaves; i++) {
		if (aeronaves[i].codigo == codigo) {
			return i;
		}
	}
	return -1;
}

int Aerolinea::buscarVueloPorTramo(string origen, string destino) const {
	for (int i = 0; i < cantidadVuelos; i++) {
		if (vuelos[i].origen == origen && vuelos[i].destino == destino) {
			return i;
		}
	}
	return -1;
}

bool Aerolinea::cargarDatos() {
	grafo.limpiar();
	avlPasajeros.limpiar();
	Persistencia::cargarCiudades("ciudades.txt", grafo);
	Persistencia::cargarRutas("rutas.txt", grafo);
	Persistencia::cargarAeronaves("aeronaves.txt", aeronaves, cantidadAeronaves);
	Persistencia::cargarTripulantes("tripulacion.txt", tripulantes, cantidadTripulantes);
	Persistencia::cargarVuelos("vuelos.txt", vuelos, cantidadVuelos);
	Persistencia::cargarReservas("reservas.txt", reservas, cantidadReservas);
	
	for (int i = 0; i < cantidadReservas; i++) {
		if (reservas[i].activa) {
			string detalle = reservas[i].origen + "->" + reservas[i].destino;
			avlPasajeros.insertar(reservas[i].cedulaPasajero, reservas[i].nombrePasajero, detalle);
		}
	}
	return true;
}

bool Aerolinea::guardarDatos() const {
	Persistencia::guardarCiudades("ciudades.txt", grafo);
	Persistencia::guardarRutas("rutas.txt", grafo);
	Persistencia::guardarAeronaves("aeronaves.txt", aeronaves, cantidadAeronaves);
	Persistencia::guardarTripulantes("tripulacion.txt", tripulantes, cantidadTripulantes);
	Persistencia::guardarVuelos("vuelos.txt", vuelos, cantidadVuelos);
	Persistencia::guardarReservas("reservas.txt", reservas, cantidadReservas);
	return true;
}

bool Aerolinea::registrarCiudad(string codigo, string nombre, float posX, float posY) {
	return grafo.agregarCiudad(codigo, nombre, posX, posY) != -1;
}

bool Aerolinea::registrarRuta(string codigoOrigen, string codigoDestino, double costo, double duracion) {
	int origen = grafo.buscarIndicePorCodigo(codigoOrigen);
	int destino = grafo.buscarIndicePorCodigo(codigoDestino);
	if (origen == -1 || destino == -1) {
		return false;
	}
	return grafo.agregarRuta(origen, destino, costo, duracion);
}

bool Aerolinea::eliminarRuta(string codigoOrigen, string codigoDestino) {
	int origen = grafo.buscarIndicePorCodigo(codigoOrigen);
	int destino = grafo.buscarIndicePorCodigo(codigoDestino);
	if (origen == -1 || destino == -1) {
		return false;
	}
	return grafo.eliminarRuta(origen, destino);
}

bool Aerolinea::registrarAeronave(string codigo, string modelo, int capacidad, string estado) {
	if (cantidadAeronaves >= MAX_AERONAVES || buscarAeronave(codigo) != -1 || capacidad <= 0) {
		return false;
	}
	aeronaves[cantidadAeronaves] = { codigo, modelo, capacidad, estado };
	cantidadAeronaves++;
	return true;
}

bool Aerolinea::registrarTripulante(string id, string nombre, string rol) {
	if (cantidadTripulantes >= MAX_TRIPULANTES) {
		return false;
	}
	for (int i = 0; i < cantidadTripulantes; i++) {
		if (tripulantes[i].id == id) {
			return false;
		}
	}
	tripulantes[cantidadTripulantes] = { id, nombre, rol, true, "Ninguno" };
	cantidadTripulantes++;
	return true;
}

bool Aerolinea::asignarTripulanteAVuelo(string idTripulante, string codigoVuelo) {
	for (int i = 0; i < cantidadTripulantes; i++) {
		if (tripulantes[i].id == idTripulante && tripulantes[i].disponible) {
			tripulantes[i].disponible = false;
			tripulantes[i].vueloAsignado = codigoVuelo;
			return true;
		}
	}
	return false;
}

bool Aerolinea::programarVuelo(string codigo, string origen, string destino, string fechaHora, double costo, double duracion, string codigoAeronave) {
	if (cantidadVuelos >= MAX_VUELOS) {
		return false;
	}
	int indiceAvion = buscarAeronave(codigoAeronave);
	if (indiceAvion == -1 || aeronaves[indiceAvion].estado == "Mantenimiento") {
		return false;
	}
	if (!registrarRuta(origen, destino, costo, duracion)) {
		return false;
	}
	vuelos[cantidadVuelos] = { codigo, origen, destino, fechaHora, costo, duracion, codigoAeronave, 0 };
	cantidadVuelos++;
	return true;
}

bool Aerolinea::crearReserva(int cedula, string nombre, string codigoOrigen, string codigoDestino, int criterioPasajero, int criterioEquipaje, Reserva& reservaCreada) {
	if (cantidadReservas >= MAX_RESERVAS) {
		return false;
	}
	int origen = grafo.buscarIndicePorCodigo(codigoOrigen);
	int destino = grafo.buscarIndicePorCodigo(codigoDestino);
	if (origen == -1 || destino == -1) {
		return false;
	}
	
	int indiceVuelo = buscarVueloPorTramo(codigoOrigen, codigoDestino);
	if (indiceVuelo != -1) {
		int indiceAvion = buscarAeronave(vuelos[indiceVuelo].codigoAeronave);
		if (indiceAvion != -1 && vuelos[indiceVuelo].asientosOcupados >= aeronaves[indiceAvion].capacidad) {
			return false;
		}
	}
	
	ResultadoRuta rutaPasajero = Dijkstra::calcularRuta(grafo, origen, destino, criterioPasajero);
	if (!rutaPasajero.existe) {
		return false;
	}
	ResultadoRuta rutaMaleta = Dijkstra::calcularRutaEquipaje(grafo, origen, destino, criterioEquipaje, rutaPasajero);
	
	if (indiceVuelo != -1) {
		vuelos[indiceVuelo].asientosOcupados++;
	}
	
	Reserva nueva;
	nueva.idReserva = 100 + cantidadReservas + 1;
	nueva.cedulaPasajero = cedula;
	nueva.nombrePasajero = nombre;
	nueva.origen = codigoOrigen;
	nueva.destino = codigoDestino;
	nueva.rutaPasajero = convertirRutaATexto(rutaPasajero);
	nueva.rutaEquipaje = convertirRutaATexto(rutaMaleta);
	nueva.costoTotal = rutaPasajero.costoTotal;
	nueva.duracionTotal = rutaPasajero.duracionTotal;
	nueva.activa = true;
	
	reservas[cantidadReservas] = nueva;
	cantidadReservas++;
	avlPasajeros.insertar(cedula, nombre, codigoOrigen + "->" + codigoDestino);
	reservaCreada = nueva;
	return true;
}

bool Aerolinea::cancelarReserva(int idReserva) {
	for (int i = 0; i < cantidadReservas; i++) {
		if (reservas[i].idReserva == idReserva && reservas[i].activa) {
			reservas[i].activa = false;
			avlPasajeros.eliminar(reservas[i].cedulaPasajero);
			return true;
		}
	}
	return false;
}

ResultadoRuta Aerolinea::buscarRutaDijkstra(string codigoOrigen, string codigoDestino, int criterio) const {
	int origen = grafo.buscarIndicePorCodigo(codigoOrigen);
	int destino = grafo.buscarIndicePorCodigo(codigoDestino);
	return Dijkstra::calcularRuta(grafo, origen, destino, criterio);
}

ResultadoMST Aerolinea::obtenerRedPrim() const {
	return PrimKruskal::calcularPrim(grafo, 0);
}

ResultadoMST Aerolinea::obtenerRedKruskal() const {
	return PrimKruskal::calcularKruskal(grafo, 0);
}

const Grafo& Aerolinea::getGrafo() const { 
	return grafo; 
}

const ArbolAVL& Aerolinea::getAvlPasajeros() const {
	return avlPasajeros; 
}

int Aerolinea::getCantidadAeronaves() const { 
	return cantidadAeronaves; 
}

Aeronave Aerolinea::getAeronave(int indice) const { 
	return aeronaves[indice]; 
}

int Aerolinea::getCantidadTripulantes() const { 
	return cantidadTripulantes; 
}

Tripulante Aerolinea::getTripulante(int indice) const {
	return tripulantes[indice]; 
}

int Aerolinea::getCantidadVuelos() const { 
	return cantidadVuelos; 
}

Vuelo Aerolinea::getVuelo(int indice) const {
	return vuelos[indice]; 
}

int Aerolinea::getCantidadReservas() const { 
	return cantidadReservas; 
}

Reserva getReservaVacia() {
	Reserva vacia = { 0, 0, "", "", "", "", "", 0.0, 0.0, false }; return vacia; 
}
Reserva Aerolinea::getReserva(int indice) const {
	return (indice >= 0 && indice < cantidadReservas) ? reservas[indice] : getReservaVacia(); 
}
