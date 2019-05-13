//burbBand.h

//metodo burbuja utilizando una bandera (optimizado)
template<class T>
void burbBand(T vector[], int length) {
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
}//burbBand()
