//utilidades.h
#include <iostream>

using namespace std;

template<class T>
void intercambiar(T &a, T &b) {
	T aux = a;
	a = b;
	b = aux;
}//intercambiar

template<class T>
void vaciarArray(T vector[], int length) {
	int i;
	for (i = 0; i < length; i++)
		vector[i] = -1;
}

template<class T>
void imprimirArray(T vector[], int length) {
	int i;
	
	for (i = 0; i < length; i++) {
		 cout<<vector[i]<<" | ";
	}//for i
	cout << endl;
}//imprimirArray()

//funcion de utilidad para obtener el mayor valor de un vector
int getMax(int vector[], int length) { 
    int max = vector[0]; 
    for (int i = 1; i < length; i++) 
        if (vector[i] > max) 
            max = vector[i]; 
    return max; 
}//getMax()
