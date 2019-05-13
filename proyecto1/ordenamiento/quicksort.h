//quicksort.h

template<class T>
void quicksort(T vector[], int izq, int der) {
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
		quicksort(vector, izq, j);
		
	if (i < der)
		quicksort(vector, i, der);
}//quicksort()
