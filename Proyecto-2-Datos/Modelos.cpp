#include "Modelos.h"
#include "Texto.h"

Aeronave Modelos::crearAeronave(string campos[]) {
	Aeronave aeronave;
	aeronave.codigo = campos[0];
	aeronave.modelo = campos[1];
	aeronave.capacidad = Texto::aEntero(campos[2]);
	aeronave.estado = campos[3];
	aeronave.placa = campos[4];
	aeronave.marca = campos[5];
	return aeronave;
}

Tripulante Modelos::crearTripulante(string campos[]) {
	Tripulante tripulante;
	tripulante.id = campos[0];
	tripulante.nombre = campos[1];
	tripulante.rol = campos[2];
	tripulante.disponible = (Texto::aEntero(campos[3]) != 0);
	tripulante.aeronaveAsignada = campos[4];
	return tripulante;
}

Vuelo Modelos::crearVuelo(string campos[]) {
	Vuelo vuelo;
	vuelo.codigo = campos[0];
	vuelo.origen = campos[1];
	vuelo.destino = campos[2];
	vuelo.fechaHora = campos[3];
	vuelo.costo = Texto::aDecimal(campos[4]);
	vuelo.duracion = Texto::aDecimal(campos[5]);
	vuelo.codigoAeronave = campos[6];
	vuelo.asientosOcupados = Texto::aEntero(campos[7]);
	return vuelo;
}

Reserva Modelos::crearReserva(string campos[]) {
	Reserva reserva;
	reserva.idReserva = Texto::aEntero(campos[0]);
	reserva.cedulaPasajero = Texto::aEntero(campos[1]);
	reserva.nombrePasajero = campos[2];
	reserva.origen = campos[3];
	reserva.destino = campos[4];
	reserva.rutaPasajero = campos[5];
	reserva.rutaEquipaje = campos[6];
	reserva.costoTotal = Texto::aDecimal(campos[7]);
	reserva.duracionTotal = Texto::aDecimal(campos[8]);
	reserva.activa = (Texto::aEntero(campos[9]) != 0);
	reserva.vuelos = campos[10];
	return reserva;
}

string Modelos::formatearAeronave(const Aeronave& aeronave) {
	return aeronave.codigo + ";" + aeronave.modelo + ";" + to_string(aeronave.capacidad) + ";" + aeronave.estado + ";" + aeronave.placa + ";" + aeronave.marca;
}

string Modelos::formatearTripulante(const Tripulante& tripulante) {
	string disp = tripulante.disponible ? "1" : "0";
	return tripulante.id + ";" + tripulante.nombre + ";" + tripulante.rol + ";" + disp + ";" + tripulante.aeronaveAsignada;
}

string Modelos::formatearVuelo(const Vuelo& vuelo) {
	return vuelo.codigo + ";" + vuelo.origen + ";" + vuelo.destino + ";" + vuelo.fechaHora + ";" + to_string((int)vuelo.costo) + ";" + to_string(vuelo.duracion) + ";" + vuelo.codigoAeronave + ";" + to_string(vuelo.asientosOcupados);
}

string Modelos::formatearReserva(const Reserva& reserva) {
	string act = reserva.activa ? "1" : "0";
	return to_string(reserva.idReserva) + ";" + to_string(reserva.cedulaPasajero) + ";" + reserva.nombrePasajero + ";" + reserva.origen + ";" + reserva.destino + ";" + reserva.rutaPasajero + ";" + reserva.rutaEquipaje + ";" + to_string((int)reserva.costoTotal) + ";" + to_string(reserva.duracionTotal) + ";" + act + ";" + reserva.vuelos;
}
