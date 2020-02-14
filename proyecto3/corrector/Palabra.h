//Palabra.h
#ifndef PALABRA_H
#define PALABRA_H
#include <cstring>
#include "TablaLetrasEs.h"
#include <iostream>
#define TAM 40
using namespace std;

extern const TablaLetrasEs tabla;

class Palabra { //almacena y hace todo en ascii, para ansi usar metodos que terminan en ansi
	unsigned char texto[TAM]; //las palabras mas largas del espanyol tienen 23 letras
	int textoNum[TAM]; //equivalencia de letras en numeros segun la tabla
	
	public:
		Palabra() {
			strcpy((char*)this->texto, ""); //inicializo el primer valor
		}
		
		Palabra(unsigned char *texto, bool ascii, bool toAscii) {
			setTexto(texto, ascii, toAscii);
		}
		
		void operator= (Palabra obj) {
			strcpy((char*)this->texto, (char*)obj.getTexto());
			for (int i = 0; i < TAM && texto[i] != '\0'; i++) {
				this->textoNum[i] = obj.textoNum[i];
			}
		}
		
		bool operator==(Palabra obj);
		bool operator>(Palabra &obj);
		bool operator>=(Palabra &obj);
		bool operator<(Palabra obj);
		bool operator<=(Palabra obj);
		friend ostream & operator<<(ostream &os, Palabra c) {
			cout<<c.texto;
			return os;
		}
		//sobrecargar + para concatenar
		//sobrecargar = con palabra y char para que sea setTexto
		//bool operator/ (int& exp);
		
		unsigned char* getTexto() {
			return texto;
		}
		
		unsigned char getTextoI(int pos) {
			if (pos >= 0 && pos < TAM)
				return texto[pos];
			else
				return 0;
		}
		
		unsigned char* getTextoAnsi(unsigned char aux[TAM]) {
			int i;
			char car;
			strcpy((char*)aux, (char*)texto);
			for (i = 0; i < TAM && texto[i] != '\0'; i++) {
				car = (char)aux[i];
				tabla.getEquiv(&car, false, true);
				aux[i] = car;
			}//for
			if (i < TAM)
				aux[i] = '\0';
			
			return aux;
		}//unsigned char* getTextoAnsi()
		
		int getTextoNum(int pos) {
			return textoNum[pos];
		}
		
		void setTexto(unsigned char *text, bool ascii, bool edit) {
			int i = 0, j;
			char aux;
			if (strlen((char*)text) >= TAM)
				throw "Palabra con demasiados caracteres";
			while (i < 27 && text[i] != '\0') {
				aux = (char)text[i];
				j = tabla.getEquiv(&aux, ascii, edit);
				texto[i] = aux;
				textoNum[i] = j;
				i++;
			}
			if (i < 27) {
				texto[i] = '\0';
				textoNum[i] = (int) '\0';
			}
		}//void setTexto
		
		~Palabra() { }
}; //class Palabra

#endif
