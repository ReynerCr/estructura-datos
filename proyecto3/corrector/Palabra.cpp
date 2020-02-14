//Palabra.cpp
#include "Palabra.h"
#include "cctype"

bool Palabra::operator==(Palabra obj) {
	int length1 = strlen((char*)this->texto), length2 = strlen((char*)obj.texto);
	int i = 0;
	if (length1 == length2) { //para ser iguales deben tener el mismo tam
		while (i < length1) {
			int m = tolower(obj.texto[i]);
			int n = tolower(this->texto[i]);
			if (n != m)
				return false;
			i++;
		}//while
		return true;
	}//if
	return false;
}//operator==

bool Palabra::operator<(Palabra obj) {
	int length1 = strlen((char*)this->texto), length2 = strlen((char*)obj.texto);
	int menor = (length1 > length2? length2:length1);
	int i = 0;
	while (i < menor) {
		if (this->textoNum[i] < obj.textoNum[i])
			return true;
		else if (this->textoNum[i] > obj.textoNum[i])
			return false;
		i++;
	}//while
	if (length1 > length2)
		return false;
	else if (length1 == length2) {
		i = 0;
		while  (i < menor) {
			if (this->texto[i] != obj.texto[i]) {
				int m = obj.texto[i];
				int n = this->texto[i];
				if (n < m)
					return true;
				else
					return false;
			}//if diferentes
			i++;
		}//while
		return false;
	}//si son "iguales" busco si no hay caracter Especial
}//operator<

bool Palabra::operator<=(Palabra obj) {
	if (*this < obj)
		return true;
	else if (*this == obj)
		return true;
	else
		return false;
}//operator<=

bool Palabra::operator>(Palabra& obj) {
	int length1 = strlen((char*)this->texto), length2 = strlen((char*)obj.texto);
	int menor = (length1 > length2? length2:length1);
	int i = 0;
	while (i < menor) {
		if (this->textoNum[i] > obj.textoNum[i])
			return true;
		else if (this->textoNum[i] < obj.textoNum[i])
			return false;
		i++;
	}//while
	if (length1 < length2)
		return false;
	else if (length1 == length2) {
		i = 0;
		while  (i < menor) {
			if (this->texto[i] != obj.texto[i]) {
				int m = obj.texto[i];
				int n = this->texto[i];
				if (n > m)
					return true;
				else
					return false;
			}//if diferentes
			i++;
		}//while
		return false;
	}//si son "iguales" busco si no hay caracter Especial
}//operator>

bool Palabra::operator>=(Palabra &obj){
	if (*this > obj)
		return true;
	else if (*this == obj)
		return true;
	else
		return false;
}//operator>=

//exp es el numero de la potencia de 10
/*char* Palabra::operator/(int& exp) {
	char pal[24];
	int i;
	exp = pow(10, exp);
	//usar string 
	textoMod[i]
	strcpy(pal, this.textoMod);
	
	return pal;
}*/
