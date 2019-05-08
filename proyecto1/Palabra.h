//Palabra.h
#ifndef PALABRA_H
#define PALABRA_H
#include <string.h>

class Palabra {
	char texto[24]; //en espanyol, las palabras con mas letras tienen 23
		
	public:
		Palabra() {
			strcpy(texto, "");
		}
		Palabra(char *texto) {
			strcpy(this->texto, texto);
		}
		
		void operator= (Palabra &obj) {
			strcpy(this->texto, obj.getTexto());
		}
		
		bool operator==(Palabra& obj);
		bool operator>(Palabra& obj);
		bool operator>=(Palabra& obj);
		bool operator<(Palabra& obj);
		bool operator<=(Palabra& obj);
		
		char* getTexto() {
			return texto;
		}
		
		void setTexto(char *text) {
			strcpy(texto, text);
		}//void setTexto
		
		int obtenerEnNumero() {
			int length = sizeof(texto)/sizeof(char), i;			
		}//obtenerEnNumero()
		
};

#endif
