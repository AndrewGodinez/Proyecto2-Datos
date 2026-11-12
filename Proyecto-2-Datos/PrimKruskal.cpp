#include "PrimKruskal.h"
#include "Ordenamiento.h"
#include "ConjuntoDisjunto.h"
#include "Cola.h"

static const double INFINITO_MST = 1e15;

void PrimKruskal::construirHijos(int cantidadCiudades, const AristaRuta aristas[], int cantidadAristas, int raiz, int hijos[][MAX_CIUDADES], int cantHijos[]) {
	bool visitado[MAX_CIUDADES];
	for (int i = 0; i < cantidadCiudades; i++) {
		visitado[i] = false;
		cantHijos[i] = 0;
	}
	
	Cola cola;
	visitado[raiz] = true;
	cola.encolar(raiz);
	
	while (!cola.estaVacia()) {
		int actual = cola.desencolar();
		for (int i = 0; i < cantidadAristas; i++) {
			int vecino = -1;
			if (aristas[i].origen == actual && !visitado[aristas[i].destino]) {
				vecino = aristas[i].destino;
			} else if (aristas[i].destino == actual && !visitado[aristas[i].origen]) {
				vecino = aristas[i].origen;
			}
			if (vecino != -1) {
				visitado[vecino] = true;
				hijos[actual][cantHijos[actual]] = vecino;
				cantHijos[actual]++;
				cola.encolar(vecino);
			}
		}
	}
}

void PrimKruskal::recPreorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto) {
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += grafo.getCiudad(actual).codigo;
	for (int i = 0; i < cantHijos[actual]; i++) {
		recPreorden(grafo, hijos[actual][i], hijos, cantHijos, texto);
	}
}

void PrimKruskal::recInorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto) {
	if (cantHijos[actual] > 0) {
		recInorden(grafo, hijos[actual][0], hijos, cantHijos, texto);
	}
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += grafo.getCiudad(actual).codigo;
	for (int i = 1; i < cantHijos[actual]; i++) {
		recInorden(grafo, hijos[actual][i], hijos, cantHijos, texto);
	}
}

void PrimKruskal::recPostorden(const Grafo& grafo, int actual, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto) {
	for (int i = 0; i < cantHijos[actual]; i++) {
		recPostorden(grafo, hijos[actual][i], hijos, cantHijos, texto);
	}
	if (!texto.empty()) {
		texto += " -> ";
	}
	texto += grafo.getCiudad(actual).codigo;
}

void PrimKruskal::recAnchura(const Grafo& grafo, int raiz, int hijos[][MAX_CIUDADES], int cantHijos[], string& texto) {
	Cola cola;
	cola.encolar(raiz);
	while (!cola.estaVacia()) {
		int actual = cola.desencolar();
		if (!texto.empty()) {
			texto += " -> ";
		}
		texto += grafo.getCiudad(actual).codigo;
		for (int i = 0; i < cantHijos[actual]; i++) {
			cola.encolar(hijos[actual][i]);
		}
	}
}

void PrimKruskal::llenarRecorridos(const Grafo& grafo, int raiz, ResultadoMST& resultado) {
	int cantidadCiudades = grafo.getCantidadCiudades();
	if (cantidadCiudades <= 0) {
		return;
	}
	int hijos[MAX_CIUDADES][MAX_CIUDADES];
	int cantHijos[MAX_CIUDADES];
	construirHijos(cantidadCiudades, resultado.aristas, resultado.cantidadAristas, raiz, hijos, cantHijos);
	
	resultado.raiz = raiz;
	for (int i = 0; i < cantidadCiudades; i++) {
		resultado.visual[i].etiqueta = grafo.getCiudad(i).codigo;
		resultado.visual[i].factorEquilibrio = 0;
		resultado.visual[i].izq = (cantHijos[i] > 0) ? hijos[i][0] : -1;
		resultado.visual[i].der = -1;
	}
	for (int i = 0; i < cantidadCiudades; i++) {
		for (int k = 0; k + 1 < cantHijos[i]; k++) {
			resultado.visual[hijos[i][k]].der = hijos[i][k + 1];
		}
	}
	
	resultado.preorden = "";
	resultado.inorden = "";
	resultado.postorden = "";
	resultado.anchura = "";
	
	recPreorden(grafo, raiz, hijos, cantHijos, resultado.preorden);
	recInorden(grafo, raiz, hijos, cantHijos, resultado.inorden);
	recPostorden(grafo, raiz, hijos, cantHijos, resultado.postorden);
	recAnchura(grafo, raiz, hijos, cantHijos, resultado.anchura);
}

ResultadoMST PrimKruskal::calcularPrim(const Grafo& grafo, int ciudadInicial) {
	ResultadoMST resultado;
	resultado.conectado = false;
	resultado.cantidadAristas = 0;
	resultado.costoTotal = 0.0;
	resultado.duracionTotal = 0.0;
	resultado.raiz = -1;
	
	int cantidadCiudades = grafo.getCantidadCiudades();
	if (cantidadCiudades <= 0) {
		return resultado;
	}
	if (ciudadInicial < 0 || ciudadInicial >= cantidadCiudades) {
		ciudadInicial = 0;
	}
	
	bool visitado[MAX_CIUDADES];
	for (int i = 0; i < cantidadCiudades; i++) {
		visitado[i] = false;
	}
	visitado[ciudadInicial] = true;
	
	for (int paso = 0; paso < cantidadCiudades - 1; paso++) {
		int mejorOrigen = -1;
		int mejorDestino = -1;
		double menorCosto = INFINITO_MST;
		double duracionElegida = 0.0;
		
		for (int u = 0; u < cantidadCiudades; u++) {
			for (int v = 0; v < cantidadCiudades; v++) {
				if (visitado[u] && !visitado[v]) {
					if (grafo.existeRuta(u, v) && grafo.getCostoRuta(u, v) < menorCosto) {
						menorCosto = grafo.getCostoRuta(u, v);
						duracionElegida = grafo.getDuracionRuta(u, v);
						mejorOrigen = u;
						mejorDestino = v;
					}
					if (grafo.existeRuta(v, u) && grafo.getCostoRuta(v, u) < menorCosto) {
						menorCosto = grafo.getCostoRuta(v, u);
						duracionElegida = grafo.getDuracionRuta(v, u);
						mejorOrigen = v;
						mejorDestino = u;
					}
				}
			}
		}
		
		if (mejorOrigen == -1) {
			return resultado;
		}
		
		int idx = resultado.cantidadAristas;
		resultado.aristas[idx].origen = mejorOrigen;
		resultado.aristas[idx].destino = mejorDestino;
		resultado.aristas[idx].costo = menorCosto;
		resultado.aristas[idx].duracion = duracionElegida;
		resultado.aristas[idx].activa = true;
		resultado.cantidadAristas++;
		
		resultado.costoTotal += menorCosto;
		resultado.duracionTotal += duracionElegida;
		
		if (visitado[mejorOrigen]) {
			visitado[mejorDestino] = true;
		} else {
			visitado[mejorOrigen] = true;
		}
	}
	
	resultado.conectado = true;
	llenarRecorridos(grafo, ciudadInicial, resultado);
	return resultado;
}

ResultadoMST PrimKruskal::calcularKruskal(const Grafo& grafo, int ciudadInicial) {
	ResultadoMST resultado;
	resultado.conectado = false;
	resultado.cantidadAristas = 0;
	resultado.costoTotal = 0.0;
	resultado.duracionTotal = 0.0;
	resultado.raiz = -1;
	
	int cantidadCiudades = grafo.getCantidadCiudades();
	if (cantidadCiudades <= 0) {
		return resultado;
	}
	if (ciudadInicial < 0 || ciudadInicial >= cantidadCiudades) {
		ciudadInicial = 0;
	}
	
	AristaRuta listaRutas[MAX_CIUDADES * MAX_CIUDADES];
	int totalRutas = grafo.obtenerTodasLasRutas(listaRutas);
	Ordenamiento::ordenarRutas(listaRutas, totalRutas, CRITERIO_DURACION);
	
	ConjuntoDisjunto componentes;
	componentes.inicializar(cantidadCiudades);
	
	for (int i = 0; i < totalRutas; i++) {
		if (resultado.cantidadAristas == cantidadCiudades - 1) {
			break;
		}
		int ciudadA = listaRutas[i].origen;
		int ciudadB = listaRutas[i].destino;
		if (componentes.unir(ciudadA, ciudadB)) {
			resultado.aristas[resultado.cantidadAristas] = listaRutas[i];
			resultado.cantidadAristas++;
			resultado.costoTotal += listaRutas[i].costo;
			resultado.duracionTotal += listaRutas[i].duracion;
		}
	}
	
	if (resultado.cantidadAristas == cantidadCiudades - 1) {
		resultado.conectado = true;
		llenarRecorridos(grafo, ciudadInicial, resultado);
	}
	return resultado;
}
