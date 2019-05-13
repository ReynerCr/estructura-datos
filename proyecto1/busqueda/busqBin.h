//busqBin.h

template<class T>
int busqBin(T vector[], int length, T clave) {
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
}//busqBin()
