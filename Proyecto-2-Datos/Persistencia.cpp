#include "Persistencia.h"
#include "Texto.h"
#include <fstream>

bool Persistencia::cargarCiudades(string nombreArchivo, Grafo& grafo) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	string linea;
	string campos[10];
	while (getline(archivo, linea)) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 10);
		if (total >= 4) {
			float posX = (float)Texto::aDecimal(campos[2]);
			float posY = (float)Texto::aDecimal(campos[3]);
			grafo.agregarCiudad(campos[0], campos[1], posX, posY);
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarCiudades(string nombreArchivo, const Grafo& grafo) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	int totalCiudades = grafo.getCantidadCiudades();
	for (int i = 0; i < totalCiudades; i++) {
		Ciudad ciudad = grafo.getCiudad(i);
		archivo << ciudad.codigo << ";" << ciudad.nombre << ";" << (int)ciudad.posX << ";" << (int)ciudad.posY << "\n";
	}
	archivo.close();
	return true;
}

bool Persistencia::cargarRutas(string nombreArchivo, Grafo& grafo) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	string linea;
	string campos[10];
	while (getline(archivo, linea)) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 10);
		if (total >= 4) {
			int origen = grafo.buscarIndicePorCodigo(campos[0]);
			int destino = grafo.buscarIndicePorCodigo(campos[1]);
			double costo = Texto::aDecimal(campos[2]);
			double duracion = Texto::aDecimal(campos[3]);
			if (origen != -1 && destino != -1) {
				grafo.agregarRuta(origen, destino, costo, duracion);
			}
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarRutas(string nombreArchivo, const Grafo& grafo) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	AristaRuta listaRutas[MAX_CIUDADES * MAX_CIUDADES];
	int totalRutas = grafo.obtenerTodasLasRutas(listaRutas);
	for (int i = 0; i < totalRutas; i++) {
		Ciudad orig = grafo.getCiudad(listaRutas[i].origen);
		Ciudad dest = grafo.getCiudad(listaRutas[i].destino);
		archivo << orig.codigo << ";" << dest.codigo << ";" << (int)listaRutas[i].costo << ";" << listaRutas[i].duracion << "\n";
	}
	archivo.close();
	return true;
}

bool Persistencia::cargarAeronaves(string nombreArchivo, Aeronave listaAeronaves[], int& cantidadAeronaves) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	cantidadAeronaves = 0;
	string linea;
	string campos[10];
	while (getline(archivo, linea) && cantidadAeronaves < MAX_AERONAVES) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 10);
		if (total >= 4) {
			listaAeronaves[cantidadAeronaves] = Modelos::crearAeronave(campos);
			cantidadAeronaves++;
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarAeronaves(string nombreArchivo, const Aeronave listaAeronaves[], int cantidadAeronaves) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	for (int i = 0; i < cantidadAeronaves; i++) {
		archivo << Modelos::formatearAeronave(listaAeronaves[i]) << "\n";
	}
	archivo.close();
	return true;
}

bool Persistencia::cargarTripulantes(string nombreArchivo, Tripulante listaTripulantes[], int& cantidadTripulantes) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	cantidadTripulantes = 0;
	string linea;
	string campos[10];
	while (getline(archivo, linea) && cantidadTripulantes < MAX_TRIPULANTES) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 10);
		if (total >= 5) {
			listaTripulantes[cantidadTripulantes] = Modelos::crearTripulante(campos);
			cantidadTripulantes++;
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarTripulantes(string nombreArchivo, const Tripulante listaTripulantes[], int cantidadTripulantes) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	for (int i = 0; i < cantidadTripulantes; i++) {
		archivo << Modelos::formatearTripulante(listaTripulantes[i]) << "\n";
	}
	archivo.close();
	return true;
}

bool Persistencia::cargarVuelos(string nombreArchivo, Vuelo listaVuelos[], int& cantidadVuelos) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	cantidadVuelos = 0;
	string linea;
	string campos[10];
	while (getline(archivo, linea) && cantidadVuelos < MAX_VUELOS) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 10);
		if (total >= 8) {
			listaVuelos[cantidadVuelos] = Modelos::crearVuelo(campos);
			cantidadVuelos++;
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarVuelos(string nombreArchivo, const Vuelo listaVuelos[], int cantidadVuelos) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	for (int i = 0; i < cantidadVuelos; i++) {
		archivo << Modelos::formatearVuelo(listaVuelos[i]) << "\n";
	}
	archivo.close();
	return true;
}

bool Persistencia::cargarReservas(string nombreArchivo, Reserva listaReservas[], int& cantidadReservas) {
	ifstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	cantidadReservas = 0;
	string linea;
	string campos[12];
	while (getline(archivo, linea) && cantidadReservas < MAX_RESERVAS) {
		string limpia = Texto::limpiarEspacios(linea);
		if (limpia.empty() || limpia[0] == '#') {
			continue;
		}
		int total = Texto::dividirPorPuntoYComa(limpia, campos, 12);
		if (total >= 10) {
			listaReservas[cantidadReservas] = Modelos::crearReserva(campos);
			cantidadReservas++;
		}
	}
	archivo.close();
	return true;
}

bool Persistencia::guardarReservas(string nombreArchivo, const Reserva listaReservas[], int cantidadReservas) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	for (int i = 0; i < cantidadReservas; i++) {
		archivo << Modelos::formatearReserva(listaReservas[i]) << "\n";
	}
	archivo.close();
	return true;
}
