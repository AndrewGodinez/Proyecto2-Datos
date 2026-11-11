#include "Texto.h"
#include <cstdlib>

string Texto::limpiarEspacios(string texto) {
	int inicio = 0;
	int fin = (int)texto.length() - 1;
	
	while (inicio <= fin && (texto[inicio] == ' ' || texto[inicio] == '\t' || texto[inicio] == '\r' || texto[inicio] == '\n')) {
		inicio++;
	}
	while (fin >= inicio && (texto[fin] == ' ' || texto[fin] == '\t' || texto[fin] == '\r' || texto[fin] == '\n')) {
		fin--;
	}
	if (inicio > fin) {
		return "";
	}
	return texto.substr(inicio, fin - inicio + 1);
}

int Texto::dividirPorPuntoYComa(string linea, string campos[], int maxCampos) {
	int cantidadCampos = 0;
	string actual = "";
	
	for (size_t i = 0; i < linea.length(); i++) {
		if (linea[i] == ';') {
			if (cantidadCampos < maxCampos) {
				campos[cantidadCampos] = limpiarEspacios(actual);
				cantidadCampos++;
			}
			actual = "";
		} else {
			actual += linea[i];
		}
	}
	
	if (cantidadCampos < maxCampos) {
		campos[cantidadCampos] = limpiarEspacios(actual);
		cantidadCampos++;
	}
	return cantidadCampos;
}

int Texto::aEntero(string texto) {
	string limpio = limpiarEspacios(texto);
	if (limpio.empty()) {
		return 0;
	}
	return atoi(limpio.c_str());
}

double Texto::aDecimal(string texto) {
	string limpio = limpiarEspacios(texto);
	if (limpio.empty()) {
		return 0.0;
	}
	return atof(limpio.c_str());
}
