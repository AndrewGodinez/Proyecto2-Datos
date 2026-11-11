#ifndef TEXTO_H
#define TEXTO_H

#include "Constantes.h"

class Texto {
public:
	static string limpiarEspacios(string texto);
	static int dividirPorPuntoYComa(string linea, string campos[], int maxCampos);
	static int aEntero(string texto);
	static double aDecimal(string texto);
};

#endif
