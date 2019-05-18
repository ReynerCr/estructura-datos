//Palabra.cpp
#include "Palabra.h"
#include <ctype.h>
#include <cmath>

bool Palabra::operator==(Palabra& obj) {
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) == 0)
		cond = true;
	return cond;
}

bool Palabra::operator<(Palabra& obj) {
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) < 0)
		cond = true;
	return cond;
}

bool Palabra::operator<=(Palabra& obj) {
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) <= 0)
		cond = true;
	return cond;
}

bool Palabra::operator>(Palabra& obj) {
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) > 0)
		cond = true;
	return cond;
}

bool Palabra::operator>=(Palabra& obj ){
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) >= 0)
		cond = true;
	return cond;
}

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
