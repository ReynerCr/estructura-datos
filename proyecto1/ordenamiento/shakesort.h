//shakesort.h

template<class T>
void shakesort(T a[], int length) {
	bool bandera = true;
    int inicio = 0, fin = length - 1, i, j;
  	
    while (bandera) { 
        bandera = false; 
        for (i = inicio; i < fin; ++i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = true;
            }//if
        }//for
        
        if (!bandera) 
            break; 
            
        bandera = false;
        --fin;
        for (i = fin - 1; i >= inicio; --i) { 
            if (a[i] > a[i + 1]) { 
                intercambiar(a[i], a[i + 1]); 
                bandera = true;
            }//if
        }//for
        ++inicio; 
    }//while
}//shakesort()
