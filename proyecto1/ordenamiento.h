#include <iostream>
#include <math.h>
#include "utilidades.h"

using namespace std;

template<class T>
void burbujaBandera(T vector[], T length) {
	int movidos[20];
	vaciarArray(movidos, 20);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(vector, length, movidos, 0);
	cout<<endl;
	
	int i, j, bandera = 1, k = 0;
	for (i = 0; i < length - 1 && bandera != 0; i++) {
		bandera = 0;
		for (j = 0; j < length - i - 1; j++) {
			if (vector[j] > vector[j+1]) { //simbolo altera el orden
				intercambiar(vector[j], vector[j+1]);
				bandera = 1;
				movidos[k++] = j;
				movidos[k++] = j+1;
			}//if
			imprimirArray(vector, length, movidos,  k);
			k = 0;
			vaciarArray(movidos, 20);
		}//for de chequeo e intercambio (si es necesario) de valores
	}//for de repeticiones del algoritmo
}//burbujaBandera()

template<class T>
void shakeSort(T a[], int length) {
	int movidos[20];
	vaciarArray(movidos, 20);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(a, length, movidos, 0);
	cout<<endl;
	
	int bandera = 1; //utilizare como booleano 
    int inicio = 0; 
    int fin = length - 1; 
  	int i, j, k = 0;
  	
    while (bandera) { 
        bandera = 0; 
        for (i = inicio; i < fin; ++i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = 1;
                movidos[k++] = i;
				movidos[k++] = i+1;
            }//if
			imprimirArray(a, length, movidos, k);
			k = 0;
			vaciarArray(movidos, 20);
        }//for
        
        if (bandera == 0) 
            break; 
            
        bandera = 0; 
        --fin;
        for (i = fin - 1; i >= inicio; --i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = 1;
                movidos[k++] = i;
				movidos[k++] = i+1;
            }//if
            imprimirArray(a, length, movidos, k);
            k = 0;
			vaciarArray(movidos, 20);
        }//for
        ++inicio; 
    }//while
}//shakerShort()

//INSERCION DIRECTA HACER
template<class T>
void insercionDirecta(T vector[], T length) {
	
}//insercionDirecta()

template<class T>
void seleccionDirecta(T vector[], T length) {
	int movidos[2];
	vaciarArray(movidos, 2);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(vector, length, movidos, 0);
	cout<<endl;
	
	int i, j;
	for (i = 0; i < length; i++) {
		int min = i;
		
		//compruebo en todo el array s
		for (j = i + 1; j < length; j++) {
			if (vector[j] < vector[min])  { //simbolo  altera el orden (creciente o decreciente)
				vaciarArray(movidos, 2);
				min = j;
				movidos[0] = i;
				movidos[1] = min;
			}//if
			imprimirArray(vector, length, movidos, 2);
		}//for j

		movidos[0] = i;
		movidos[1] = min;
		intercambiar(vector[i], vector[min]); //intercambio los elementos
		imprimirArray(vector, length, movidos, 2);
		vaciarArray(movidos, 2);
	}//for i
}//seleccionDirecta()

//HACER
template<class T>
void radixsort(T vector[], T length) {
	
}//radixsort()

//HACER
template<class T>
void shellsort() {
	
}//shellsort()

//HACER
template<class T>
void quicksort() {
	
}//quicksort()
