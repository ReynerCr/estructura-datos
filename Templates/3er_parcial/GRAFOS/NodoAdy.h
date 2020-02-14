#ifndef NODOADY_H
#define NODOADY_H

#include <iostream>

class NodoAdy
{
	char ver; //vertice
	float pes; //peso
public:
	NodoAdy(char e, float p = 1) { ver = e; pes = p; }
	NodoAdy() { ver = 0; pes = 0.0; }
	float GetVal() { return pes; }
	char  GetVer() { return ver; }
	bool operator==(NodoAdy d) { return this->ver == d.ver; }
	bool operator< (NodoAdy d) { return this->ver < d.ver; }
	void Imprimir() { std::cout << "[" << ver << "] Peso:" << pes << " - "; }
};

#endif