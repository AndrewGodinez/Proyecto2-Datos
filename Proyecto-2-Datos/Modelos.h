#ifndef MODELOS_H
#define MODELOS_H

#include "Constantes.h"

const int MAX_AERONAVES = 40;
const int MAX_TRIPULANTES = 80;
const int MAX_VUELOS = 120;
const int MAX_RESERVAS = 200;

struct Aeronave {
	string codigo;
	string modelo;
	int capacidad;
	string estado;
	string placa;
	string marca;
};

struct Tripulante {
	string id;
	string nombre;
	string rol;
	bool disponible;
	string aeronaveAsignada;
};

struct Vuelo {
	string codigo;
	string origen;
	string destino;
	string fechaHora;
	double costo;
	double duracion;
	string codigoAeronave;
	int asientosOcupados;
};

struct Reserva {
	int idReserva;
	int cedulaPasajero;
	string nombrePasajero;
	string origen;
	string destino;
	string rutaPasajero;
	string rutaEquipaje;
	double costoTotal;
	double duracionTotal;
	bool activa;
	string vuelos;
};

class Modelos {
public:
	static Aeronave crearAeronave(string campos[]);
	static Tripulante crearTripulante(string campos[]);
	static Vuelo crearVuelo(string campos[]);
	static Reserva crearReserva(string campos[]);
	
	static string formatearAeronave(const Aeronave& aeronave);
	static string formatearTripulante(const Tripulante& tripulante);
	static string formatearVuelo(const Vuelo& vuelo);
	static string formatearReserva(const Reserva& reserva);
};

#endif
