#ifndef TEXTO_H
#define TEXTO_H

#include "Constantes.h"

class Texto {
public:
	static string limpiarEspacios(string texto);
	static int dividirPorPuntoYComa(string linea, string campos[], int maxCampos);
	static int aEntero(string texto);
	static double aDecimal(string texto);
	static string minusculas(string texto);
	static string mayusculas(string texto);
	static string formatoHoras(double horas);
	static bool listaContiene(string lista, string codigo);
};

#endif
