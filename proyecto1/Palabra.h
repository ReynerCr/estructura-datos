//Palabra.h
#ifndef PALABRA_H
#define PALABRA_H
#include <string.h>
#include "TablaLetrasEs.h"

class Palabra {
	char texto[24]; //las palabras mas largas del espanyol tienen 23 letras
	char textoMod[24]; //texto modificado; sin caracteres especiales 
	
	public:
		Palabra() {
			strcpy(texto, "");
			strcpy(textoMod, "");
		}
		
		Palabra(char *texto, TablaTextoEs *tablita) {
			setTexto(texto, &tablita);
		}
		
		void operator= (Palabra &obj) {
			strcpy(this->texto, obj.getTexto());
			strcpy(this->textoMod, obj.getTextoMod());
		}
		
		bool operator==(Palabra& obj);
		bool operator>(Palabra& obj);
		bool operator>=(Palabra& obj);
		bool operator<(Palabra& obj);
		bool operator<=(Palabra& obj);
		//bool operator/ (int& exp);
		
		char* getTexto() {
			return texto;
		}
		
		char* getTextoMod() {
			return textoMod;
		}
		
		void setTexto(char *text, TablaLetrasEs *tablita) {
			strcpy(texto, text);
			
			int i = 0, j;
			
			while (i < 27 && texto[i] != '\0') {
				j = *(tablita).getEquiv(texto[i]);
				textoMod[i] = *(tablita).getCaracter(j);
			}
		}//void setTexto
		
		~Palabra() { }
}; //class Palabra

#endif
