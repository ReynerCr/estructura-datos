#ifndef NODODIR_H
#define NODODIR_H

#include <iostream>
#include "NodoAdy.h"
#include "lista.h"

class NodoDir
{
	char ver; //vertice
	lista< NodoAdy >* ady;
public:
	NodoDir(char e, bool band = true) {
		ver = e;
		ady = (band ? (new lista< NodoAdy >) : (NULL));
	}

	NodoDir() { ver = 0; ady = NULL; }
	char GetVer() { return ver; }
	Nodo<NodoAdy>* GetCab() { return ady->get_cab(); }
	bool operator==(NodoDir d) { return this->ver == d.ver; }
	bool operator!=(NodoDir d) { return this->ver != d.ver; }
	bool operator< (NodoDir d) { return this->ver < d.ver; }
	int  AgregarAdy(NodoAdy e) { return ady->agregar(e); }
	void Imprimir() {
		std::cout << endl << ver << " Nodos Adyacentes: ";
		ady->imprimir();
	}
	void setVer(char ver) { this->ver = ver; }
};

#endif
