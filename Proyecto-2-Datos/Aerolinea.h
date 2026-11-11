#ifndef AEROLINEA_H
#define AEROLINEA_H

#include "Constantes.h"
#include "Grafo.h"
#include "Dijkstra.h"
#include "PrimKruskal.h"
#include "ArbolAVL.h"
#include "Modelos.h"
#include "Persistencia.h"

class Aerolinea {
private:
	Grafo grafo;
	ArbolAVL avlPasajeros;
	Aeronave aeronaves[MAX_AERONAVES];
	int cantidadAeronaves;
	Tripulante tripulantes[MAX_TRIPULANTES];
	int cantidadTripulantes;
	Vuelo vuelos[MAX_VUELOS];
	int cantidadVuelos;
	Reserva reservas[MAX_RESERVAS];
	int cantidadReservas;
	
	string convertirRutaATexto(const ResultadoRuta& ruta) const;
	int buscarAeronave(string codigo) const;
	int buscarVueloPorTramo(string origen, string destino) const;
	
public:
	Aerolinea();
	~Aerolinea();
	
	bool cargarDatos();
	bool guardarDatos() const;
	
	bool registrarCiudad(string codigo, string nombre, float posX, float posY);
	bool registrarRuta(string codigoOrigen, string codigoDestino, double costo, double duracion);
	bool eliminarRuta(string codigoOrigen, string codigoDestino);
	
	bool registrarAeronave(string codigo, string modelo, int capacidad, string estado);
	bool registrarTripulante(string id, string nombre, string rol);
	bool asignarTripulanteAVuelo(string idTripulante, string codigoVuelo);
	bool programarVuelo(string codigo, string origen, string destino, string fechaHora, double costo, double duracion, string codigoAeronave);
	
	bool crearReserva(int cedula, string nombre, string codigoOrigen, string codigoDestino, int criterioPasajero, int criterioEquipaje, Reserva& reservaCreada);
	bool cancelarReserva(int idReserva);
	
	ResultadoRuta buscarRutaDijkstra(string codigoOrigen, string codigoDestino, int criterio) const;
	ResultadoMST obtenerRedPrim() const;
	ResultadoMST obtenerRedKruskal() const;
	
	const Grafo& getGrafo() const;
	const ArbolAVL& getAvlPasajeros() const;
	int getCantidadAeronaves() const;
	Aeronave getAeronave(int indice) const;
	int getCantidadTripulantes() const;
	Tripulante getTripulante(int indice) const;
	int getCantidadVuelos() const;
	Vuelo getVuelo(int indice) const;
	int getCantidadReservas() const;
	Reserva getReserva(int indice) const;
};

#endif
