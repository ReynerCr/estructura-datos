#include <iostream>

using namespace std;

template<class T>
class pilaVector
{
	int tope;
	T *v, eli, ini;
	int tam;
	
	public:
		pilaVector(int tam, T valIni);
		int agregar(T elemento);
		int eliminar();
		void imprimir();
};//class pilaVector

template<class T>
pilaVector<T>::pilaVector(int tam, T valIni)
{
	this->tam = tam;
	eli = valIni;
	ini = valIni;
	tope = -1;
	v = new T[tam];
	for (int i = 0; i < tam; i++)
		v[i] = ini;
}//PilaVector(int, T)

template<class T>
int pilaVector<T>::agregar(T elemento)
{
	if (tope == tam-1) return 0; //esta llena
	v[tope + 1] = elemento;
	tope++;
	return;
}//agregar(T)

template<class T>
int pilaVector<T>::eliminar()
{
	if (tope == -1) return 0; //esta vacia
	eli = v[tope];
	v[tope] = ini;
	tope--;
	return 1;
}//eliminar();

template<class T>
void pilaVector<T>::imprimir()
{
	
}//imprimir()


