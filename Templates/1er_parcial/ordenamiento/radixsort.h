//radixsort.h

#include "countingsort.h"

//funcion de utilidad para obtener el mayor valor de un vector
template<class T>
T getMax(T vector[], int length) { 
    T max = vector[0]; 
    for (int i = 1; i < length; i++) 
        if (vector[i] > max) 
            max = vector[i]; 
    return max; 
}//getMax()

// radixSort
template<class T>
void radixsort(T vector[], int length) { 
    // encuentra el numero mayor para conocer el numero de digitos
    T max = getMax(vector, length); 
  
    // Hace countingSort por cada digito. Notar que en vez de 
    // pasar el numero del digito, exp es pasado. exp es 10^i 
    // donde i es el actual digito del numero
    for (int exp = 1; max/exp > 0; exp *= 10) 
        countSort(vector, length, exp); 
}//radixsort()
