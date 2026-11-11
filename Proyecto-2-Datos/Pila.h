#ifndef PILA_H
#define PILA_H

struct NodoPila {
	int valor;
	NodoPila* siguiente;
};

class Pila {
private:
	NodoPila* tope;
	int cantidad;
	
public:
	Pila();
	~Pila();
	
	void apilar(int valor);
	int desapilar();
	int verTope() const;
	bool estaVacia() const;
	int tamanio() const;
	void vaciar();
	
	Pila(const Pila&) = delete;
	Pila& operator=(const Pila&) = delete;
};

#endif
