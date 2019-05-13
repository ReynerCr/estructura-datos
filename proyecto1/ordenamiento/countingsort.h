//countingsort.h

// funcion para hacer countingSort al vector de acuerdo al
// digito representado por exp
template<class T>
void countingsort(T vector[], int length, int exp) { 
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
}//countingsort()
