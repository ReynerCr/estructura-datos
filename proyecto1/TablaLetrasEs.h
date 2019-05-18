//TablaLetrasEs.h
#ifndef TABLALETRASES_H
#define TABLALETRASES_H
#include <ctype.h>

//tabla solo valida para el espanyol
class TablaLetrasEs {
	char caracter[27]; //letras sin caracteres especiales a excepcion de la enye
	int valCaracter[27]; //valor numerico en la tabla; posicion en array
	
	//inicializa las letras
	TablaLetrasES() {
		int i, j = 0;
		//97 = a
		for (i = 97; i<111; i++) {
			caracter[j] = (char)i;
			valCaracter[j] = j;
			j++;
		}//for
		caracter[j] = (char)164;
		valCaracter[j] = j;
		j++;
		for (i = 111; i < 123; i++) {
			caracter[j] = (char)i;
			valCaracter[j] = j;				
			j++;
		}//for 
	}//TablaLetrasEs()
	
	public:
		int getEquiv(char car) { //retorna -1 si no es letra del espanyol
			int i = 0;
			car = tolower(car);
	
			//reviso si es un caracter especial y cambio por su equiv
			//en minuscula
			switch (car) {
				case 'á':
				case 'ä':
					car = 'a';
					break;
				case 'é':
				case 'ë':
					car = 'e';
					break;
				case 'í':
				case 'ï':
					car = 'i';
					break;
				case 'ó':
				case 'ö':
					car = 'o';
					break;
				case 'ú':
				case 'ü':
					car = 'u';
					break;
			}//switch
			
			while (i < 27 && car != caracter[i])
				i++;
	
			if (i >= 27) //no encontrado
				i = -1;
	
			return i;
		}//getEquiv(char)
		
		char getCaracter(int pos) {
			if (pos >= 0 && pos < 27)
				return caracter[pos];
			else 
				return (char)-1;
		}//getCaracter(int)
};//class TablaLetrasES

#endif
