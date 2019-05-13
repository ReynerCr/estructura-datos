//insDir.h

template<class T>
void insDir(T vector[], int length) {
	int i, j;
	for (i = 0; i < length - 1; i++) {
		if (vector[i] > vector[i+1]) {
			intercambiar(vector[i], vector[i+1]);
			for (j = i; j > 0; j--)
				if (vector[j-1] > vector[j])
					intercambiar(vector[j], vector[j-1]);
		}//if
	}//for i
}//insDir()
