//utilidades.h
#include <iostream>
#include "gotoxy.h"

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
void imprimirArray(T vector[], int length, int movidos[], int lengthMovidos) {
	int i, k = 0;
	
	cout<<" | ";
	for (i = 0; i < length; i++) {
		 if (movidos[k] != -1 && i == movidos[k]) {
		 	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),2);
			k++;
		 }
		 
		 cout<<vector[i];
		 SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),7);
		 cout<<" | ";
	}//for i
	cout << endl;
}//imprimirArray()
