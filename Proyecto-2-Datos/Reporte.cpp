#include "Reporte.h"
#include <iostream>
#include <fstream>

void Reporte::mostrarDiagnosticoConsola(const Aerolinea& sistema) {
	cout << "====================================================\n";
	cout << "   DIAGNOSTICO GENERAL AEROLINEA UNA - EIF207\n";
	cout << "====================================================\n";
	cout << "Ciudades en red:      " << sistema.getGrafo().getCantidadCiudades() << "\n";
	cout << "Aeronaves en flota:   " << sistema.getCantidadAeronaves() << "\n";
	cout << "Tripulantes activos:  " << sistema.getCantidadTripulantes() << "\n";
	cout << "Vuelos programados:   " << sistema.getCantidadVuelos() << "\n";
	cout << "Reservas registradas: " << sistema.getCantidadReservas() << "\n";
	
	ResultadoRuta rutaCosto = sistema.buscarRutaDijkstra("SJO", "CDG", CRITERIO_COSTO);
	ResultadoRuta rutaTiempo = sistema.buscarRutaDijkstra("SJO", "CDG", CRITERIO_DURACION);
	cout << "----------------------------------------------------\n";
	cout << "Dijkstra SJO->CDG (Menor Costo):    $" << rutaCosto.costoTotal << " (" << rutaCosto.duracionTotal << " hrs)\n";
	cout << "Dijkstra SJO->CDG (Menor Duracion): $" << rutaTiempo.costoTotal << " (" << rutaTiempo.duracionTotal << " hrs)\n";
	
	ResultadoMST redPrim = sistema.obtenerRedPrim();
	ResultadoMST redKruskal = sistema.obtenerRedKruskal();
	cout << "----------------------------------------------------\n";
	cout << "MST Prim (Costo $" << redPrim.costoTotal << "):\n";
	cout << "  Preorden:  " << redPrim.preorden << "\n";
	cout << "  Inorden:   " << redPrim.inorden << "\n";
	cout << "  Postorden: " << redPrim.postorden << "\n";
	cout << "  Anchura:   " << redPrim.anchura << "\n";
	
	cout << "MST Kruskal (Duracion " << redKruskal.duracionTotal << " hrs):\n";
	cout << "  Preorden:  " << redKruskal.preorden << "\n";
	cout << "  Inorden:   " << redKruskal.inorden << "\n";
	cout << "  Postorden: " << redKruskal.postorden << "\n";
	cout << "  Anchura:   " << redKruskal.anchura << "\n";
	
	cout << "----------------------------------------------------\n";
	cout << "Arbol AVL Pasajeros (" << sistema.getAvlPasajeros().tamanio() << " nodos):\n";
	cout << "  Preorden:  " << sistema.getAvlPasajeros().preorden() << "\n";
	cout << "  Inorden:   " << sistema.getAvlPasajeros().inorden() << "\n";
	cout << "  Postorden: " << sistema.getAvlPasajeros().postorden() << "\n";
	cout << "  Anchura:   " << sistema.getAvlPasajeros().anchura() << "\n";
	cout << "====================================================\n";
}

bool Reporte::exportarReporteTxt(string nombreArchivo, const Aerolinea& sistema) {
	ofstream archivo(nombreArchivo.c_str());
	if (!archivo.is_open()) {
		return false;
	}
	
	archivo << "REPORTE TECNICO DE ESTRUCTURAS DE DATOS - AEROLINEA UNA\n";
	archivo << "=======================================================\n\n";
	archivo << "1. RESUMEN DE ENTIDADES CARGADAS\n";
	archivo << "   - Ciudades:    " << sistema.getGrafo().getCantidadCiudades() << "\n";
	archivo << "   - Aeronaves:   " << sistema.getCantidadAeronaves() << "\n";
	archivo << "   - Tripulacion: " << sistema.getCantidadTripulantes() << "\n";
	archivo << "   - Vuelos:      " << sistema.getCantidadVuelos() << "\n";
	archivo << "   - Reservas:    " << sistema.getCantidadReservas() << "\n\n";
	
	ResultadoMST redPrim = sistema.obtenerRedPrim();
	ResultadoMST redKruskal = sistema.obtenerRedKruskal();
	archivo << "2. OPTIMIZACION GLOBAL DE RED (MST)\n";
	archivo << "   [Prim - Menor Costo Total: $" << redPrim.costoTotal << "]\n";
	archivo << "   - Preorden:  " << redPrim.preorden << "\n";
	archivo << "   - Inorden:   " << redPrim.inorden << "\n";
	archivo << "   - Postorden: " << redPrim.postorden << "\n";
	archivo << "   - Anchura:   " << redPrim.anchura << "\n\n";
	
	archivo << "   [Kruskal - Menor Duracion Total: " << redKruskal.duracionTotal << " hrs]\n";
	archivo << "   - Preorden:  " << redKruskal.preorden << "\n";
	archivo << "   - Inorden:   " << redKruskal.inorden << "\n";
	archivo << "   - Postorden: " << redKruskal.postorden << "\n";
	archivo << "   - Anchura:   " << redKruskal.anchura << "\n\n";
	
	archivo << "3. ARBOL BALANCEADO AVL DE PASAJEROS\n";
	archivo << "   - Preorden:  " << sistema.getAvlPasajeros().preorden() << "\n";
	archivo << "   - Inorden:   " << sistema.getAvlPasajeros().inorden() << "\n";
	archivo << "   - Postorden: " << sistema.getAvlPasajeros().postorden() << "\n";
	archivo << "   - Anchura:   " << sistema.getAvlPasajeros().anchura() << "\n\n";
	
	archivo << "4. LISTADO DE RESERVAS CON RUTA DIFERENCIADA DE EQUIPAJE\n";
	for (int i = 0; i < sistema.getCantidadReservas(); i++) {
		Reserva res = sistema.getReserva(i);
		archivo << "   - Reserva #" << res.idReserva << " | " << res.nombrePasajero << " (Ced: " << res.cedulaPasajero << ")\n";
		archivo << "     Ruta Pasajero: " << res.rutaPasajero << "\n";
		archivo << "     Ruta Equipaje: " << res.rutaEquipaje << "\n";
	}
	
	archivo.close();
	return true;
}
