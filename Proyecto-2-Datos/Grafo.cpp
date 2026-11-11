#include "Grafo.h"

Grafo::Grafo() {
	limpiar();
}

Grafo::~Grafo() {
}

void Grafo::limpiar() {
	cantidadCiudades = 0;
	for (int i = 0; i < MAX_CIUDADES; i++) {
		ciudades[i].id = -1;
		ciudades[i].codigo = "";
		ciudades[i].nombre = "";
		ciudades[i].posX = 0.0f;
		ciudades[i].posY = 0.0f;
		for (int j = 0; j < MAX_CIUDADES; j++) {
			matriz[i][j].existe = false;
			matriz[i][j].costo = 0.0;
			matriz[i][j].duracion = 0.0;
		}
	}
}

int Grafo::agregarCiudad(string codigo, string nombre, float posX, float posY) {
	if (cantidadCiudades >= MAX_CIUDADES) {
		return -1;
	}
	int Existente = buscarIndicePorCodigo(codigo);
	if (Existente != -1) {
		return Existente;
	}
	int id = cantidadCiudades;
	ciudades[id].id = id;
	ciudades[id].codigo = codigo;
	ciudades[id].nombre = nombre;
	ciudades[id].posX = posX;
	ciudades[id].posY = posY;
	cantidadCiudades++;
	return id;
}

bool Grafo::agregarRuta(int origen, int destino, double costo, double duracion) {
	if (origen < 0 || origen >= cantidadCiudades || destino < 0 || destino >= cantidadCiudades) {
		return false;
	}
	if (origen == destino) {
		return false;
	}
	matriz[origen][destino].existe = true;
	matriz[origen][destino].costo = costo;
	matriz[origen][destino].duracion = duracion;
	return true;
}

bool Grafo::eliminarRuta(int origen, int destino) {
	if (origen < 0 || origen >= cantidadCiudades || destino < 0 || destino >= cantidadCiudades) {
		return false;
	}
	if (!matriz[origen][destino].existe) {
		return false;
	}
	matriz[origen][destino].existe = false;
	matriz[origen][destino].costo = 0.0;
	matriz[origen][destino].duracion = 0.0;
	return true;
}

int Grafo::buscarIndicePorCodigo(string codigo) const {
	for (int i = 0; i < cantidadCiudades; i++) {
		if (ciudades[i].codigo == codigo) {
			return i;
		}
	}
	return -1;
}

int Grafo::buscarIndicePorNombre(string nombre) const {
	for (int i = 0; i < cantidadCiudades; i++) {
		if (ciudades[i].nombre == nombre) {
			return i;
		}
	}
	return -1;
}

int Grafo::getCantidadCiudades() const {
	return cantidadCiudades;
}

Ciudad Grafo::getCiudad(int indice) const {
	if (indice < 0 || indice >= cantidadCiudades) {
		Ciudad vacia = { -1, "", "", 0.0f, 0.0f };
		return vacia;
	}
	return ciudades[indice];
}

bool Grafo::existeRuta(int origen, int destino) const {
	if (origen < 0 || origen >= cantidadCiudades || destino < 0 || destino >= cantidadCiudades) {
		return false;
	}
	return matriz[origen][destino].existe;
}

double Grafo::getCostoRuta(int origen, int destino) const {
	if (!existeRuta(origen, destino)) {
		return 0.0;
	}
	return matriz[origen][destino].costo;
}

double Grafo::getDuracionRuta(int origen, int destino) const {
	if (!existeRuta(origen, destino)) {
		return 0.0;
	}
	return matriz[origen][destino].duracion;
}

int Grafo::obtenerTodasLasRutas(AristaRuta listaRutas[]) const {
	int total = 0;
	for (int i = 0; i < cantidadCiudades; i++) {
		for (int j = 0; j < cantidadCiudades; j++) {
			if (matriz[i][j].existe) {
				listaRutas[total].origen = i;
				listaRutas[total].destino = j;
				listaRutas[total].costo = matriz[i][j].costo;
				listaRutas[total].duracion = matriz[i][j].duracion;
				listaRutas[total].activa = true;
				total++;
			}
		}
	}
	return total;
}
