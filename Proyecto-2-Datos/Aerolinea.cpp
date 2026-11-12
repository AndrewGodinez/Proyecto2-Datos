#include "Aerolinea.h"
#include "Texto.h"

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
			int indiceAvion = buscarAeronave(vuelos[i].codigoAeronave);
			if (indiceAvion == -1 || vuelos[i].asientosOcupados < aeronaves[indiceAvion].capacidad) {
				return i;
			}
		}
	}
	return -1;
}

int Aerolinea::buscarVuelo(string codigo) const {
	for (int i = 0; i < cantidadVuelos; i++) {
		if (vuelos[i].codigo == codigo) {
			return i;
		}
	}
	return -1;
}

string Aerolinea::vuelosDeRuta(const ResultadoRuta& ruta) const {
	string lista = "";
	for (int i = 0; i < ruta.cantidadNodos - 1; i++) {
		string origen = grafo.getCiudad(ruta.nodos[i]).codigo;
		string destino = grafo.getCiudad(ruta.nodos[i + 1]).codigo;
		int indiceVuelo = buscarVueloPorTramo(origen, destino);
		if (indiceVuelo == -1) {
			return "";
		}
		if (!lista.empty()) {
			lista += ",";
		}
		lista += vuelos[indiceVuelo].codigo;
	}
	return lista;
}

string Aerolinea::pasajerosDeVuelo(string codigoVuelo) const {
	string texto = "";
	for (int i = 0; i < cantidadReservas; i++) {
		if (reservas[i].activa && Texto::listaContiene(reservas[i].vuelos, codigoVuelo)) {
			if (!texto.empty()) {
				texto += ", ";
			}
			texto += reservas[i].nombrePasajero + " (" + to_string(reservas[i].cedulaPasajero) + ")";
		}
	}
	return texto;
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
			avlPasajeros.agregarReserva(reservas[i].cedulaPasajero, reservas[i].nombrePasajero, reservas[i].idReserva, reservas[i].vuelos);
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
	if (origen == -1 || destino == -1 || costo <= 0.0 || duracion <= 0.0) {
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

bool Aerolinea::registrarAeronave(string codigo, string placa, string marca, string modelo, int capacidad, string estado) {
	if (cantidadAeronaves >= MAX_AERONAVES || buscarAeronave(codigo) != -1 || capacidad <= 0) {
		return false;
	}
	aeronaves[cantidadAeronaves] = { codigo, modelo, capacidad, estado, placa, marca };
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

bool Aerolinea::asignarTripulanteAAeronave(string idTripulante, string codigoAeronave) {
	if (buscarAeronave(codigoAeronave) == -1) {
		return false;
	}
	for (int i = 0; i < cantidadTripulantes; i++) {
		if (tripulantes[i].id == idTripulante) {
			tripulantes[i].disponible = false;
			tripulantes[i].aeronaveAsignada = codigoAeronave;
			return true;
		}
	}
	return false;
}

bool Aerolinea::programarVuelo(string codigo, string origen, string destino, string fechaHora, double costo, double duracion, string codigoAeronave) {
	if (cantidadVuelos >= MAX_VUELOS || buscarVuelo(codigo) != -1) {
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
	
	ResultadoRuta rutaPasajero = Dijkstra::calcularRuta(grafo, origen, destino, criterioPasajero);
	if (!rutaPasajero.existe) {
		return false;
	}
	string listaVuelos = vuelosDeRuta(rutaPasajero);
	if (listaVuelos.empty()) {
		return false;
	}
	ResultadoRuta rutaMaleta = Dijkstra::calcularRutaEquipaje(grafo, origen, destino, criterioEquipaje, rutaPasajero);
	
	for (int i = 0; i < cantidadVuelos; i++) {
		if (Texto::listaContiene(listaVuelos, vuelos[i].codigo)) {
			vuelos[i].asientosOcupados++;
		}
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
	nueva.vuelos = listaVuelos;
	
	reservas[cantidadReservas] = nueva;
	cantidadReservas++;
	avlPasajeros.agregarReserva(cedula, nombre, nueva.idReserva, listaVuelos);
	reservaCreada = nueva;
	return true;
}

bool Aerolinea::cancelarReserva(int idReserva) {
	for (int i = 0; i < cantidadReservas; i++) {
		if (reservas[i].idReserva == idReserva && reservas[i].activa) {
			reservas[i].activa = false;
			for (int j = 0; j < cantidadVuelos; j++) {
				if (Texto::listaContiene(reservas[i].vuelos, vuelos[j].codigo) && vuelos[j].asientosOcupados > 0) {
					vuelos[j].asientosOcupados--;
				}
			}
			avlPasajeros.quitarReserva(reservas[i].cedulaPasajero, idReserva);
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

ResultadoMST Aerolinea::obtenerRedPrim(int ciudadInicial) const {
	return PrimKruskal::calcularPrim(grafo, ciudadInicial);
}

ResultadoMST Aerolinea::obtenerRedKruskal(int ciudadInicial) const {
	return PrimKruskal::calcularKruskal(grafo, ciudadInicial);
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

#if __has_include("BellmanFord.h")
#include "BellmanFord.h"
#endif
#if __has_include("ArbolABB.h")
#include "ArbolABB.h"
#endif

ResultadoRuta Aerolinea::buscarRutaBellmanFord(string codigoOrigen, string codigoDestino, int criterio) const {
	int origen = grafo.buscarIndicePorCodigo(codigoOrigen);
	int destino = grafo.buscarIndicePorCodigo(codigoDestino);
#if __has_include("BellmanFord.h")
	return BellmanFord::calcularRuta(grafo, origen, destino, criterio);
#else
	return Dijkstra::calcularRuta(grafo, origen, destino, criterio);
#endif
}

string Aerolinea::obtenerCiudadesABBInorden() const {
#if __has_include("ArbolABB.h")
	ArbolABB abb;
	for (int i = 0; i < grafo.getCantidadCiudades(); i++) {
		Ciudad ciudad = grafo.getCiudad(i);
		abb.insertar(ciudad.codigo, ciudad.nombre);
	}
	return abb.inorden();
#else
	string texto = "";
	for (int i = 0; i < grafo.getCantidadCiudades(); i++) {
		if (i > 0) {
			texto += " -> ";
		}
		texto += grafo.getCiudad(i).codigo;
	}
	return texto;
#endif
}
