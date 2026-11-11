#ifndef COLA_H
#define COLA_H

struct NodoCola {
	int valor;
	NodoCola* siguiente;
};

class Cola {
private:
	NodoCola* frente;
	NodoCola* ultimo;
	int cantidad;
	
public:
	Cola();
	~Cola();
	
	void encolar(int valor);
	int desencolar();
	int verFrente() const;
	int verPosicion(int pos) const;
	bool estaVacia() const;
	int tamanio() const;
	void vaciar();
	
	Cola(const Cola&) = delete;
	Cola& operator=(const Cola&) = delete;
};

#endif
