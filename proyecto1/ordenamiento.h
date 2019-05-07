#include <math.h>
#include "utilidades.h"

using namespace std;

template<class T>
void burbujaOptima(T vector[], int length) {
	int i, j = length - 1;
	bool bandera = false;

	while (!bandera) {
		bandera = true;
		for  (i = 0; i < j; i++) {
			if  (vector[i] > vector[i + 1]) {
				intercambiar(vector[i], vector[i+1]);
				bandera = false;
			}//if
		}//for
		j--;
	}//while
}//burbujaOptima()

template<class T>
void shakerSort(T a[], int length) {
	bool bandera = true;
    int inicio = 0, fin = length - 1, i, j;
  	
    while (bandera) { 
        bandera = false; 
        for (i = inicio; i < fin; ++i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = true;
            }//if
        }//for
        
        if (!bandera) 
            break; 
            
        bandera = false;
        --fin;
        for (i = fin - 1; i >= inicio; --i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = true;
            }//if
        }//for
        ++inicio; 
    }//while
}//shakerSort()

template<class T>
void insercionDirecta(T vector[], int length) {
	int i, j;
	for (i = 0; i < length - 1; i++) {
		if (vector[i] > vector[i+1]) {
			intercambiar(vector[i], vector[i+1]);
			for (j = i; j > 0; j--)
				if (vector[j-1] > vector[j])
					intercambiar(vector[j], vector[j-1]);
		}//if
	}//for i
}//insercionDirecta()

template<class T>
void seleccionDirecta(T vector[], int length) {	
	int i, j;
	for (i = 0; i < length; i++) {
		int min = i;
		
		//compruebo en todo el array s
		for (j = i + 1; j < length; j++) {
			if (vector[j] < vector[min])  { //simbolo  altera el orden (creciente o decreciente)
				min = j;
			}//if
		}//for j

		intercambiar(vector[i], vector[min]); //intercambio los elementos
	}//for i
}//seleccionDirecta()

/* 
+ COUNTINGSORT Y RADIXSORT SACADOS DE https://www.geeksforgeeks.org/radix-sort/
+ TRADUCIDOS AL ESPANYOL Y ADAPTADOS AL CODIGO
*/
// funcion para hacer countingSort al vector de acuerdo al
// digito representado por exp
/*template<class T>
void countSort(T vector[], int length, int exp) { 
    T salida[length]; // output array 
    int i, cont[10] = {0}; 
  
    //almacena las ocurrencias en cont
	for (i = 0; i < length; i++) 
    	cont[(vector[i]/exp)%10]++; 
  
    // cambia cont[i] asi que cont[i] ahora contiene la actual
	// posicion de este digito en salida[] 
    for (i = 1; i < 10; i++) 
        cont[i] += cont[i - 1]; 
  
    // contruye el vector de salida[] 
    for (i = length - 1; i >= 0; i--) { 
        salida[cont[ (vector[i]/exp)%10 ] - 1] = vector[i]; 
        cont[ (vector[i]/exp)%10 ]--; 
    } 
  
    // copia el vector de salida a vector[], asi que vector[] ahora 
    // contiene numeros ordenados de acuerdo al numero actual 
    for (i = 0; i < length; i++) 
        vector[i] = salida[i]; 
}//countSort()
  
// funcion principal que arregla el vector de tamaño length usando
// radixSort
template<class T>
void radixSort(T vector[], int length) { 
    // encuentra el numero mayor para conocer el numero de digitos
    T max = getMax(vector, length); 
  
    // Hace countingSort por cada digito. Notar que en vez de 
    // pasar el numero del digito, exp es pasado. exp es 10^i 
    // donde i es el actual digito del numero
    for (int exp = 1; max/exp > 0; exp *= 10) 
        countSort(vector, length, exp); 
}//radixSort()
//FIN DE COUNTINGSORT Y RADIXSORT ADAPTADOS*/

template<class T>
void shellSort(T vector[], int length) {
	bool band;
	int i, iner = floor(length/2);
	while (iner > 0) {
		band = false;
		for (i=0; i + iner < length; i++)
			if (vector[i]>vector[i+iner]) {
				intercambiar(vector[i], vector[i+iner]);
				band = true;
			}//if
		//salida for
		
		if(!band)
			iner = floor(iner / 2);
	}//while
}//shellSort()

template<class T>
void quickSort(T vector[], int izq, int der) {
   	T pivote = vector[(izq+der) / 2];
	int i = izq, j = der;
	
	//particion
	while (i < j) {
		while (vector[i] < pivote) {
			i++;
		}
		while (vector[j] > pivote) {
			j--;
		}
		if (i <= j) {
			intercambiar(vector[i], vector[j]);
			j--;
			i++;
		}//if
	}//while

	//recursividad
	if (izq < j) 
		quickSort(vector, izq, j);
		
	if (i < der)
		quickSort(vector, i, der);
}//quickSort()
