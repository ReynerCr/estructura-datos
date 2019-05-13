//selDir.h

template<class T>
void selDir(T vector[], int length) {	
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
}//selDir()
