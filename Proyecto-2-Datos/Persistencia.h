#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "Constantes.h"
#include "Grafo.h"
#include "Modelos.h"

class Persistencia {
public:
	static bool cargarCiudades(string nombreArchivo, Grafo& grafo);
	static bool guardarCiudades(string nombreArchivo, const Grafo& grafo);
	
	static bool cargarRutas(string nombreArchivo, Grafo& grafo);
	static bool guardarRutas(string nombreArchivo, const Grafo& grafo);
	
	static bool cargarAeronaves(string nombreArchivo, Aeronave listaAeronaves[], int& cantidadAeronaves);
	static bool guardarAeronaves(string nombreArchivo, const Aeronave listaAeronaves[], int cantidadAeronaves);
	
	static bool cargarTripulantes(string nombreArchivo, Tripulante listaTripulantes[], int& cantidadTripulantes);
	static bool guardarTripulantes(string nombreArchivo, const Tripulante listaTripulantes[], int cantidadTripulantes);
	
	static bool cargarVuelos(string nombreArchivo, Vuelo listaVuelos[], int& cantidadVuelos);
	static bool guardarVuelos(string nombreArchivo, const Vuelo listaVuelos[], int cantidadVuelos);
	
	static bool cargarReservas(string nombreArchivo, Reserva listaReservas[], int& cantidadReservas);
	static bool guardarReservas(string nombreArchivo, const Reserva listaReservas[], int cantidadReservas);
};

#endif
