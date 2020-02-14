//shellsort.h

#include <cmath>

template<class T>
void shellsort(T vector[], int length) {
	bool band;
	int i, iner = floor(length/2);
	while (iner > 0) {
		band = false;
		for (i=0; i + iner < length; i++)
			if (vector[i]>vector[i+iner]) {
				intercambiar(vector[i], vector[i+iner]);
				band = true;
			}//if
		//salida for
		
		if(!band)
			iner = floor(iner / 2);
	}//while
}//shellsort()
