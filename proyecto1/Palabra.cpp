#include "Palabra.h"
#include <ctype.h>

bool Palabra::operator==(Palabra& obj) {
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) == 0)
		cond = true;
	return cond;
}

bool Palabra::operator<(Palabra& obj){
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) < 0)
		cond = true;
	return cond;	
}

bool Palabra::operator<=(Palabra& obj){
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) <= 0)
		cond = true;
	return cond;	
}

bool Palabra::operator>(Palabra& obj){
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) > 0)
		cond = true;
	return cond;	
}

bool Palabra::operator>=(Palabra& obj){
	bool cond = false;
	if (strcmp(this->texto, obj.getTexto()) >= 0)
		cond = true;
	return cond;	
}

