#ifndef REPORTE_H
#define REPORTE_H

#include "Aerolinea.h"

class Reporte {
public:
	static void mostrarDiagnosticoConsola(const Aerolinea& sistema);
	static bool exportarReporteTxt(string nombreArchivo, const Aerolinea& sistema);
};

#endif
