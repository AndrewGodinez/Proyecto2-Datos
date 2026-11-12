#include "Dijkstra.h"
#include "Pila.h"

static const double INFINITO_DIJKSTRA = 1e15;

ResultadoRuta Dijkstra::calcularRuta(const Grafo& grafo, int origen, int destino, int criterio, int ignorarOrigen, int ignorarDestino) {
	ResultadoRuta res;
	res.existe = false;
	res.cicloNegativo = false;
	res.cantidadNodos = 0;
	res.costoTotal = 0.0;
	res.duracionTotal = 0.0;
	res.escalas = 0;
	
	int n = grafo.getCantidadCiudades();
	if (origen < 0 || origen >= n || destino < 0 || destino >= n) {
		return res;
	}
	
	double dist[MAX_CIUDADES];
	bool visitado[MAX_CIUDADES];
	int padre[MAX_CIUDADES];
	
	for (int i = 0; i < n; i++) {
		dist[i] = INFINITO_DIJKSTRA;
		visitado[i] = false;
		padre[i] = -1;
	}
	
	dist[origen] = 0.0;
	
	for (int paso = 0; paso < n; paso++) {
		int u = -1;
		double mejorDist = INFINITO_DIJKSTRA;
		
		for (int i = 0; i < n; i++) {
			if (!visitado[i] && dist[i] < mejorDist) {
				mejorDist = dist[i];
				u = i;
			}
		}
		
		if (u == -1 || u == destino) {
			break;
		}
		
		visitado[u] = true;
		
		for (int v = 0; v < n; v++) {
			if (!grafo.existeRuta(u, v)) {
				continue;
			}
			if (u == ignorarOrigen && v == ignorarDestino) {
				continue;
			}
			
			double peso = 0.0;
			if (criterio == CRITERIO_COSTO) {
				peso = grafo.getCostoRuta(u, v);
			} else if (criterio == CRITERIO_DURACION) {
				peso = grafo.getDuracionRuta(u, v);
			} else {
				peso = 1.0;
			}
			
			if (peso < 0.0) {
				continue;
			}
			
			if (!visitado[v] && dist[u] + peso < dist[v]) {
				dist[v] = dist[u] + peso;
				padre[v] = u;
			}
		}
	}
	
	if (dist[destino] >= INFINITO_DIJKSTRA) {
		return res;
	}
	
	Pila pila;
	int actual = destino;
	while (actual != -1) {
		pila.apilar(actual);
		actual = padre[actual];
	}
	
	while (!pila.estaVacia()) {
		res.nodos[res.cantidadNodos] = pila.desapilar();
		res.cantidadNodos++;
	}
	
	for (int i = 0; i < res.cantidadNodos - 1; i++) {
		int a = res.nodos[i];
		int b = res.nodos[i + 1];
		res.costoTotal += grafo.getCostoRuta(a, b);
		res.duracionTotal += grafo.getDuracionRuta(a, b);
	}
	
	res.escalas = (res.cantidadNodos >= 2) ? (res.cantidadNodos - 2) : 0;
	res.existe = true;
	return res;
}

ResultadoRuta Dijkstra::calcularRutaConEscala(const Grafo& grafo, int origen, int escala, int destino, int criterio) {
	if (escala == -1 || escala == origen || escala == destino) {
		return calcularRuta(grafo, origen, destino, criterio);
	}
	
	ResultadoRuta r1 = calcularRuta(grafo, origen, escala, criterio);
	ResultadoRuta r2 = calcularRuta(grafo, escala, destino, criterio);
	
	ResultadoRuta res;
	res.existe = false;
	res.cicloNegativo = false;
	res.cantidadNodos = 0;
	res.costoTotal = 0.0;
	res.duracionTotal = 0.0;
	res.escalas = 0;
	
	if (!r1.existe || !r2.existe) {
		return res;
	}
	
	for (int i = 0; i < r1.cantidadNodos; i++) {
		if (res.cantidadNodos < MAX_CIUDADES) {
			res.nodos[res.cantidadNodos++] = r1.nodos[i];
		}
	}
	for (int i = 1; i < r2.cantidadNodos; i++) {
		if (res.cantidadNodos < MAX_CIUDADES) {
			res.nodos[res.cantidadNodos++] = r2.nodos[i];
		}
	}
	
	res.costoTotal = r1.costoTotal + r2.costoTotal;
	res.duracionTotal = r1.duracionTotal + r2.duracionTotal;
	res.escalas = (res.cantidadNodos >= 2) ? (res.cantidadNodos - 2) : 0;
	res.existe = true;
	return res;
}

ResultadoRuta Dijkstra::calcularRutaEquipaje(const Grafo& grafo, int origen, int destino, int criterioEquipaje, const ResultadoRuta& /*rutaPasajero*/) {
	return calcularRuta(grafo, origen, destino, criterioEquipaje);
}
