//Cancion.h
#ifndef CANCION_H
#define CANCION_H
#include "Tiempo.h"
#include <iostream>
#include <cstring>

using namespace std;

class Cancion {
	char nombre[40];
	Tiempo tiempo;
	
	public:
		Cancion() {  }
		Cancion(char *nombre, Tiempo tiempo) {
			this->tiempo = tiempo;
			strcpy(this->nombre, nombre);
		}
		
		void setNombre(char* nom) {
			strcpy(nombre, nom);
		}
		
		char* getNombre() { return nombre; }
		Tiempo getTiempo() { return tiempo; }
		
		friend ostream & operator<<(ostream &os, Cancion c) {
			cout<<c.nombre;
			return os;
		}
		
		void operator= (Cancion obj) {
			strcpy(this->nombre, obj.nombre);
			this->tiempo = obj.tiempo;
		}
		
		bool operator==(Cancion &obj) {
			bool cond = false;
			if (strcmp(this->nombre, obj.nombre) == 0 && this->tiempo == obj.tiempo)
				cond = true;
			return cond;
		}//operator==
};

Cancion transfCancion(char cad[180]) {
	char *pt;
	char nom[120];
	int min, seg;
	
	pt = strtok(cad, ","); //autor-nombre
	strcpy(nom, pt);
	
	pt = strtok(NULL, ","); //minutos
	min = atoi(pt);
	
	pt = strtok(NULL, ","); //segundos
	seg = atoi(pt);
	
	Tiempo temp(min, seg);
	return Cancion(nom, Tiempo(min, seg));
}//Cancion()

#endif
