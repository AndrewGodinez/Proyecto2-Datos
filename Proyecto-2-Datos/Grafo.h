#ifndef GRAFO_H
#define GRAFO_H

#include "Constantes.h"

struct CeldaMatriz {
	bool existe;
	double costo;
	double duracion;
};

class Grafo {
private:
	Ciudad ciudades[MAX_CIUDADES];
	CeldaMatriz matriz[MAX_CIUDADES][MAX_CIUDADES];
	int cantidadCiudades;
	
public:
	Grafo();
	~Grafo();
	
	int agregarCiudad(string codigo, string nombre, float posX, float posY);
	bool agregarRuta(int origen, int destino, double costo, double duracion);
	bool eliminarRuta(int origen, int destino);
	
	int buscarIndicePorCodigo(string codigo) const;
	int buscarIndicePorNombre(string nombre) const;
	
	int getCantidadCiudades() const;
	Ciudad getCiudad(int indice) const;
	bool existeRuta(int origen, int destino) const;
	double getCostoRuta(int origen, int destino) const;
	double getDuracionRuta(int origen, int destino) const;
	
	int obtenerTodasLasRutas(AristaRuta listaRutas[]) const;
	void limpiar();
};

#endif
