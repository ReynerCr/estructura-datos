#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include "lista.h"
#include "NodoAdy.h"
#include "NodoDir.h"
#include <vector>

using namespace std;

class Grafo
{
	float **M; //representacion de matriz de adyacencia del grafo M
	float** Md; //matriz con las distancias minimas calculadas en floyd-warshall
	char** cams; //matriz para calcular las rutas
	vector<char>nomVers;
    int Tam; //tamanyo del grafo o numero de vertices del grafo
    lista< NodoDir > *lisnodo; //representacion de la lista de adyacencia del grafo; guarda los nodos
    bool EsDir; //true si el grafo es dirigido, false si no lo es
public:
    Grafo(char nomfile[25], char separador, bool tip = true); //nomfile es el nombre del archivo; tip en true para dirigido, en falso para no dirigido
	Grafo(char separador = ' ', bool tip = true);
	int Agregar_A(char ori, char des, float pes = 1);
	void CrearM();
    void Imprimir();
    void Warshall();
    void Floyd();
    void FloydCamino();
	vector<char>* camino(char origen, char destino);
	void imprimirCamino(vector<char>* camino);
	void imprimirMd(); //imprimir la matriz que almacena las distancias minimas
	void imprimirCams(); //imprimir la matriz para calcular los caminos
	void imprimirTodasRutas(); //mostrar las rutas para llegar desde u hasta v
};

#endif
