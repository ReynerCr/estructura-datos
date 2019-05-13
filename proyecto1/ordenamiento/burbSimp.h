//burbSimp.h

template<class T>
void burbSimp(T vector[], T length) {
	int movidos[20];
	vaciarArray(movidos, 20);
	cout<<"ORIGINAL:"<<endl;
	imprimirArray(vector, length, movidos, 0);
	cout<<endl;
	
	int i, j, k = 0;
	for (i = 0; i < length - 1; i++) {
		for (j = 0; j < length - i - 1; j++) {
			if (vector[j] > vector[j+1]) { //simbolo altera el orden
				intercambiar(vector[j], vector[j+1]);
				movidos[k++] = j;
				movidos[k++] = j+1;
			}//if
			imprimirArray(vector, length, movidos, k);
			k = 0;
			vaciarArray(movidos, 20);
		}//for de chequeo e intercambio (si es necesario) de valores
	}//for de repeticiones del algoritmo
}//burbSimp()
