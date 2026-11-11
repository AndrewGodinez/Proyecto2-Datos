#ifndef PILAENTEROS_H
#define PILAENTEROS_H

struct NodoPila {
	int valor;
	NodoPila* siguiente;
};

class PilaEnteros {
private:
	NodoPila* tope;
	int cantidad;
	
public:
	PilaEnteros();
	~PilaEnteros();
	
	void apilar(int valor);
	int desapilar();     
	int verTope() const;  
	bool estaVacia() const;
	int tamanio() const;
	void vaciar();
	
	PilaEnteros(const PilaEnteros&) = delete;
	PilaEnteros& operator=(const PilaEnteros&) = delete;
};

#endif
