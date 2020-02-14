//grafo.cpp
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <iostream>
#include "grafo.h"
#define INF numeric_limits<float>::max()

using namespace std;

Grafo::Grafo(char separador, bool tip)
{
	Tam = 0;
	EsDir = tip;
	lisnodo = new lista< NodoDir >; //esta lista guarda todos los nodos del grafo; no adyacencias (para eso esta nodoAdy)
	Tam = 0;
}//Grafo(char separador, bool tip)

Grafo::Grafo(char nomfile[25], char separador, bool tip)
{
	char ori, des; //origen, destino
	float pes; //peso
	Tam = 0;
	EsDir = tip;
	lisnodo = new lista< NodoDir >; //esta lista guarda todos los nodos del grafo; no adyacencias (para eso esta nodoAdy)
	ifstream objarc(nomfile);
	int aux;
	Tam = 0;
	while (true)  //adaptar para que separe por el caracter que se indique; eso es un parametro
	{
		objarc >> ori >> des >> pes;
		if (objarc.eof())
			break;

		NodoDir nue1(ori), nue2(des); //nodos origen y destino
		aux = lisnodo->agregar(nue1); //este agregar primero verifica que no exista; si existe no lo agrega.
		Tam += aux;
		if (aux)
			nomVers.push_back(ori);
		aux = lisnodo->agregar(nue2); //mismo caso aqui abajo
		if (aux)
			nomVers.push_back(des);
		Tam += aux;

		NodoAdy nue3(des, pes); //nodo que sera agregado al origen como un adyacente, guarda el peso si lo hay
		if (lisnodo->buscar(nue1) != -1)
			nue1.AgregarAdy(nue3);
	}

	cams = new char*[Tam];
	for (int i = 0; i < Tam; i++)
		cams[i] = new char[Tam];

	sort(nomVers.begin(), nomVers.end());
	CrearM();
	objarc.close();
}//Grafo(char nomfile[25], char separador, bool tip)

int Grafo::Agregar_A(char ori, char des, float pes)
{
	int aux;
	NodoDir nue1(ori), nue2(des); //nodos origen y destino
	aux = lisnodo->agregar(nue1); //este agregar primero verifica que no exista; si existe no lo agrega.
	Tam += aux;
	if (aux)
		nomVers.push_back(ori);
	aux = lisnodo->agregar(nue2); //mismo caso aqui abajo
	if (aux)
		nomVers.push_back(des);
	Tam += aux;

	cout << pes << endl;
	NodoAdy nue3(des, pes); //nodo que sera agregado al origen como un adyacente, guarda el peso si lo hay
	if (lisnodo->buscar(nue1) != -1)
		nue1.AgregarAdy(nue3);

	return 1;
}//Agregar_A(char ori, char des, float pes)

void Grafo::CrearM()
{
	//dar memoria al vector M
	M = new float* [Tam];
	for (int i = 0; i < Tam; i++)
		M[i] = new float[Tam];

	//inicializar el vector con 0
	for (int i = 0; i < Tam; i++)
	{
		for (int j = 0; j < Tam; j++)
			M[i][j] = 0.0f;
	}

	//cargarMatriz con los nodos
	if (lisnodo) {
		Nodo<NodoDir>* p = lisnodo->get_cab();
		Nodo<NodoAdy>* q;
		int i = 0, j;
		while (p) {
			q = p->get_inf().GetCab(); //retorna puntero de primer NodoAdy de la lista
			while (q) {
				NodoDir aux(q->get_inf().GetVer(), false);
				j = lisnodo->buscar(aux); //para obtener j, columna
				M[i][j] = q->get_inf().GetVal();
				if (!EsDir) //si no es dirigido la matriz sera simetrica, se ahorra trabajo
					M[j][i] = M[i][j];
				q = q->get_sig();
			}//while
			i++;
			p = p->get_sig();
		}//while(p)
	}//if
}//CrearM()

void Grafo::FloydCamino()
{ //esto se deberia ajustar para saber si es dirigido o no; siendo no dirigido el algoritmo asi como esta da mas vueltas de lo necesario
	int i, j, k;
	Md = new float* [Tam];

	for (i = 0; i < Tam; i++)
		Md[i] = new float[Tam];
	//mala carga de matriz

	for (i = 0; i < Tam; i++)
	{
		for (j = 0; j < Tam; j++)
		{
			if (M[i][j] == 0)
			{
				Md[i][j] = INF;
				cams[i][j] = '-';
			}//if
			else
			{
				Md[i][j] = M[i][j];
				cams[i][j] = nomVers[j];
			}//else
		}//for j
	}//for i

	//inicio de floyd
	for (k = 0; k < Tam; k++)
	{
		for (i = 0; i < Tam; i++)
		{
			for (j = 0; j < Tam; j++)
			{
				if ((Md[i][k] != INF) && (Md[k][j] != INF)
					&& (Md[i][k] + Md[k][j] < Md[i][j]))
				{
					if (i != j && i != k && j != k) //condicion para que no calcule la diagonal principal
					{
						Md[i][j] = Md[i][k] + Md[k][j];
						cams[i][j] = cams[i][k];
					}
				}//if
			}//for j
		}//for i
	}//for k
}//FloydCamino()

void Grafo::imprimirTodasRutas()
{
	if (!cams)
	{
		cout << "Matriz de caminos vacia" << endl;
		return;
	}
	char ori, dest;
	cout << "TODAS LAS RUTAS DESDE U HASTA V EN GRAFO:\n\n";
	for (int i = 0; i < Tam; i++)
	{
		ori = nomVers[i];
		cout << "desde " << ori << "hasta" << endl;
		for (int j = 0; j < Tam; j++)
		{
			if (j == i)
				continue;
			dest = nomVers[j];
			cout << "     : " << dest << "   ";
			vector<char>* pt = camino(ori, dest);
			imprimirCamino(pt);
			delete pt;
		}//for j
	}//for i
}//imprimirTodasRutas()

void Grafo::imprimirMd()
{
	if (!Md)
	{
		cout << "Md no cargada." << endl;
		return;
	}
	cout << "Matriz de distancia minima es: \n\n";
	for (int i = 0; i < Tam; i++)
	{
		for (int j = 0; j < Tam; j++)
			cout << ((Md[i][j] < INF) ? Md[i][j] : -1.00f) << " ";
		cout << endl;
	}//for
}//imprimirMd()

void Grafo::imprimirCams()
{
	if (!cams)
	{
		cout << "Matriz de caminos no calculada." << endl;
		return;
	}
	for (int i = 0; i < Tam; i++)
	{
		for (int j = 0; j < Tam; j++)
			cout << cams[i][j] << " ";
		cout << endl;
	}//for i
}//imprimirCams()

vector<char>* Grafo::camino(char o, char d) //o = origen; d = destino
{
	if (!cams)
	{
		cout << "Matriz para calcular los caminos vacia" << endl;
		return NULL;
	}

	NodoDir origen(o);
	NodoDir destino(d);
	int i = lisnodo->buscar(origen);
	int j = lisnodo->buscar(destino);

	if (cams[i][j] == '-')
		return NULL;
	vector<char>* ruta = new vector<char>;
	ruta->push_back(o);
	while (o != d)
	{
		origen.setVer(o);
		destino.setVer(d);
		i = lisnodo->buscar(origen);
		j = lisnodo->buscar(destino);
		o = cams[i][j];
		ruta->push_back(o);
	}
	return ruta;
}//camino(char o, char d)

void Grafo::imprimirCamino(vector<char>* ruta)
{
	if (ruta != NULL)
	{
		int fin = std::distance(ruta->begin(), ruta->end());
		for (int i = 0; i < fin; i++)
			cout << ruta->at(i) << " -> ";
	}
	else
		cout << "NO HAY CAMINO." << endl;

	cout << endl;
}//imprimirCamino(vector<char>*ruta)

void Grafo::Imprimir()
{
	if (lisnodo != NULL)
		lisnodo->imprimir();
	if (M != NULL)
	{
		cout <<endl<< "\nMatriz de Adyacencia:\n";
		for (int i = 0; i < Tam; i++)
		{
			cout << endl;
			for (int j = 0; j < Tam; j++)
				cout << setiosflags(ios::fixed) << setprecision(2) << M[i][j] << "   ";
		}//for
	}//if
}//Imprimir()

void Grafo::Warshall() //solo para sacar la matriz de caminos posibles booleanos
{
	int i, j, k;
	float **R; //R matriz de camino para algoritmo de Warshall
	R = new float*[Tam];

	for (i = 0; i < Tam; i++)
	{
		R[i] = new float[Tam];
		for (j = 0; j < Tam; j++)
			R[i][j] = (M[i][j] != 0.0f ? 1.0f : 0.0f);
	}

	/*  
	    ejecutar warshall:
		i, j y k son los iteradores
		k es el iterador de nodo puente y repeticiones del algoritmo
	*/
	for (k = 0; k < Tam; k++)
	{
		for (i = 0; i < Tam; i++)
			for (j = 0; j < Tam; j++)
				R[i][j] = R[i][j] || (R[i][k] && R[k][j]); //operaciones de and/or

		//impresiones
		cout << endl << endl;
		cout << k << ":    " << endl;
		for (i = 0; i < Tam; i++)
		{
			for (j = 0; j < Tam; j++)
				cout << R[i][j]<<"   ";
			cout << endl;
		}//for i
	}//for K

	cout <<endl<< "FINAL:" << endl;
	//imprimir
	for (i = 0; i < Tam; i++)
	{
		cout << endl;
		for (j = 0; j < Tam; j++)
			cout << R[i][j] << "   ";
	}//Fin for i
	delete[]R;
}//Warshall(int n)

void Grafo::Floyd()
{
	int i, j, k;
	Md = new float* [Tam];

	for (i = 0; i < Tam; i++)
		Md[i] = new float[Tam];

	//si EsDir se hace TODO; si no, se deberia recortar 

	for (i = 0; i < Tam; i++)
		for (j = 0; j < Tam; j++)
			if (M[i][j] == 0)
				Md[i][j] = INF;
			else
				Md[i][j] = M[i][j];

	//inicio de floyd
	for (k = 0; k < Tam; k++)
		for (i = 0; i < Tam; i++)
			for (j = 0; j < Tam; j++)
				if (i != j && i != k && j != k)
					if (Md[i][k] != INF  && Md[k][j] != INF && Md[i][k] + Md[k][j] < Md[i][j])
						Md[i][j] = Md[i][k] + Md[k][j];
}//Floyd()