#include "BellmanFord.h"
#include "Pila.h"

static const double INFINITO_BELLMAN = 1e15;

static ResultadoRuta reconstruirCamino(const Grafo& grafo, int origen, int destino, const double dist[], const int padre[], bool hayCicloNegativo) {
	ResultadoRuta res;
	res.existe = false;
	res.cicloNegativo = hayCicloNegativo;
	res.cantidadNodos = 0;
	res.costoTotal = 0.0;
	res.duracionTotal = 0.0;
	res.escalas = 0;
	
	for (int i = 0; i < MAX_CIUDADES; i++) {
		res.nodos[i] = -1;
	}
	
	if (hayCicloNegativo || dist[destino] >= INFINITO_BELLMAN) {
		return res;
	}
	
	Pila pila;
	int actual = destino;
	while (actual != -1) {
		pila.apilar(actual);
		if (actual == origen) {
			break;
		}
		actual = padre[actual];
	}
	
	if (actual != origen) {
		return res;
	}
	
	while (!pila.estaVacia()) {
		res.nodos[res.cantidadNodos] = pila.desapilar();
		res.cantidadNodos++;
	}
	
	for (int i = 0; i < res.cantidadNodos - 1; i++) {
		int u = res.nodos[i];
		int v = res.nodos[i + 1];
		res.costoTotal += grafo.getCostoRuta(u, v);
		res.duracionTotal += grafo.getDuracionRuta(u, v);
	}
	
	res.escalas = (res.cantidadNodos >= 2) ? (res.cantidadNodos - 2) : 0;
	res.existe = true;
	return res;
}

static void ejecutarBellmanFord(const Grafo& grafo, int origen, int criterio, double dist[], int padre[], bool& hayCicloNegativo) {
	int n = grafo.getCantidadCiudades();
	hayCicloNegativo = false;
	
	for (int i = 0; i < n; i++) {
		dist[i] = INFINITO_BELLMAN;
		padre[i] = -1;
	}
	
	if (origen < 0 || origen >= n) {
		return;
	}
	
	dist[origen] = 0.0;
	
	AristaRuta aristas[MAX_CIUDADES * MAX_CIUDADES];
	int totalAristas = grafo.obtenerTodasLasRutas(aristas);
	
	for (int paso = 0; paso < n - 1; paso++) {
		bool huboCambio = false;
		for (int e = 0; e < totalAristas; e++) {
			int u = aristas[e].origen;
			int v = aristas[e].destino;
			if (dist[u] >= INFINITO_BELLMAN) {
				continue;
			}
			
			double peso = (criterio == CRITERIO_COSTO) ? aristas[e].costo : aristas[e].duracion;
			if (peso < 0.0) {
				continue;
			}
			
			if (dist[u] + peso < dist[v]) {
				dist[v] = dist[u] + peso;
				padre[v] = u;
				huboCambio = true;
			}
		}
		if (!huboCambio) {
			break; 
		}
	}

	for (int e = 0; e < totalAristas; e++) {
		int u = aristas[e].origen;
		int v = aristas[e].destino;
		if (dist[u] >= INFINITO_BELLMAN) {
			continue;
		}
		double peso = (criterio == CRITERIO_COSTO) ? aristas[e].costo : aristas[e].duracion;
		if (dist[u] + peso < dist[v]) {
			hayCicloNegativo = true;
			break;
		}
	}
}

ResultadoRuta BellmanFord::calcularRuta(const Grafo& grafo, int origen, int destino, int criterio) {
	int n = grafo.getCantidadCiudades();
	ResultadoRuta res;
	res.existe = false;
	res.cicloNegativo = false;
	res.cantidadNodos = 0;
	res.costoTotal = 0.0;
	res.duracionTotal = 0.0;
	res.escalas = 0;
	
	if (origen < 0 || origen >= n || destino < 0 || destino >= n) {
		return res;
	}
	
	double dist[MAX_CIUDADES];
	int padre[MAX_CIUDADES];
	bool hayCicloNegativo = false;
	
	ejecutarBellmanFord(grafo, origen, criterio, dist, padre, hayCicloNegativo);
	return reconstruirCamino(grafo, origen, destino, dist, padre, hayCicloNegativo);
}

int BellmanFord::calcularTodosLosDestinos(const Grafo& grafo, int origen, int criterio, ResultadoRuta rutasDestinos[MAX_CIUDADES]) {
	int n = grafo.getCantidadCiudades();
	if (origen < 0 || origen >= n) {
		return 0;
	}
	
	double dist[MAX_CIUDADES];
	int padre[MAX_CIUDADES];
	bool hayCicloNegativo = false;
	
	ejecutarBellmanFord(grafo, origen, criterio, dist, padre, hayCicloNegativo);
	
	int alcanzables = 0;
	for (int i = 0; i < n; i++) {
		rutasDestinos[i] = reconstruirCamino(grafo, origen, i, dist, padre, hayCicloNegativo);
		if (i != origen && rutasDestinos[i].existe) {
			alcanzables++;
		}
	}
	return alcanzables;
}
