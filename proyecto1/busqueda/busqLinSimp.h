//busqLinSimp.h
template<class T>
int busqLinSimp(T vector[], int length, T buscar) { //cuando el array esta ordenado, no necesariamente finaliza en la ultima posicion
	int i = 0;
	while (i < length && vector[i] != buscar) {
		i++;
	}//while
	
	if (i >= length)
		i = -1;
		
	return i;
}//busqLinSimp()
