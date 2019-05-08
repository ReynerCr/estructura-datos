//busqueda.h

template<class T>
int busquedaLinealSimple(T vector[], int length, T buscar) { //cuando el array esta ordenado, no necesariamente finaliza en la ultima posicion
	int i = 0;
	while (i < length && vector[i] != buscar) {
		i++;
	}//while
	
	if (i >= length)
		i = -1;
		
	return i;
}//busquedaLinealSimple()

template<class T>
int busquedaLinealBloque(T vector[], int length, T buscar) {	
	bool encontrado = false;
	int i, tamBloque = floor(sqrt(length)), j = 0;
	for (i = tamBloque-1; i <= (tamBloque*tamBloque) - 1; i += tamBloque) {
		if (vector[i] >= buscar) {
			for (j = i - (tamBloque - 1); j <= i; j++) {
				if (buscar == vector[j]) {
					encontrado = true;	
					break;
				}//if
			}//for j
			break;
		}//if
	}//for i
	
	if (!encontrado && length > tamBloque*tamBloque) {
		if (vector[length - 1] >= buscar)
			for (i = length - 1; i > (tamBloque*tamBloque - 1); i--)
				if (buscar == vector[i]) {
					j = i;
					encontrado = true;
					break;
				}
	}//if length > tamBloque*tamBloque
	
	if (!encontrado)
		j = -1;
		
	return j;
}//busquedaLinealBloque()

template<class T>
int busquedaBinaria(T vector[], int length, T clave) {
	int r = length-1, l = 0, m;
	
	while (l <= r) {
		m = (r + l)/2;
	  	
		if (vector[m] == clave)
			return m;
		else if (clave < vector[m])
			r = m - 1;
		else
			l = m + 1;
	}//while
	
	return -1;
}//busquedaBinaria()

//HACER
template<class T>
int hashFuncPlegamiento(T vector[], int length, T buscar) {
	
}//hashFuncPlegamiento()

//HACER QUE RESUELVA COLISION
template<class T>
int hashEspacioLibre(T vector[], int length, T buscar) {
	
}//hashEspacioLibre()
