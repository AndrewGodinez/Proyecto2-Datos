#ifndef COLAENTEROS_H
#define COLAENTEROS_H

struct NodoCola {
	int valor;
	NodoCola* siguiente;
};

class ColaEnteros {
private:
	NodoCola* frente;
	NodoCola* ultimo;
	int cantidad;
	
public:
	ColaEnteros();
	~ColaEnteros();
	
	void encolar(int valor);         
	int desencolar();                
	int verFrente() const;          
	int verPosicion(int pos) const; 
	bool estaVacia() const;
	int tamanio() const;
	void vaciar();           
	
	ColaEnteros(const ColaEnteros&) = delete;
	ColaEnteros& operator=(const ColaEnteros&) = delete;
};

#endif
