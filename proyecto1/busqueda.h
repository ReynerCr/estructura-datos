template<class T>
int busquedaLinealSimple(T vector[], int length, T buscar) { //cuando el array esta ordenado, no necesariamente finaliza en la ultima posicion
	int movidos[1];
	vaciarArray(movidos, 1);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(vector, length, movidos, 0);
	cout<<endl;
	
	int i = 0;
	while (i < length && vector[i] != buscar) {
		i++;
		movidos[0] = i;
		imprimirArray(vector, length, movidos, 1);
		vaciarArray(movidos, 1);
	}//while
	
	if (i >= length)
		i = -1;
		
	return i;
}//busquedaLinealSimple()

template<class T>
int busquedaLinealBloque(T vector[], int length, T buscar) {
	int movidos[1];
	vaciarArray(movidos, 1);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(vector, length, movidos, 0);
	cout<<endl;
	
	bool encontrado = false;
	int i, bloques = floor(sqrt(length)), j = 0;
	for (i = bloques-1; i <= bloques*bloques; i += bloques) {
		if (vector[i] >= buscar) {
			for (j = i - bloques; j <= i; j++) {
				if (buscar == vector[j]) {
					encontrado = true;	
					break;
				}//if
			}//for j
			break;
		}//if
	}//for i
	
	if (length > bloques*bloques && !encontrado) {
		if (vector[length - 1] >= buscar)
			for (i -= 2; i < length; i++)
				if (buscar == vector[i]) {
					j = i;
					encontrado = true;
					break;
				}
	}//if length > bloques*bloques
	
	if (!encontrado)
		j = -1;
		
	else {
		movidos[0] = j;
		imprimirArray(vector, length, movidos, 1);
		vaciarArray(movidos, 1);
	}

	return j;
}//busquedaLinealBloque()

//HACER
template<class T>
int busquedaBinaria(T vector[], int length, T buscar) {

}//busquedaBinaria()

//HACER
template<class T>
int hashFuncPlegamiento(T vector[], int length, T buscar) {
	
}//hashFuncPlegamiento()

//HACER QUE RESUELVA COLISION
int hashEspacioLibre(T vector[], int length, T buscar) {
	
}//hashEspacioLibre()
