//Inscrito.h
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <windows.h>
#ifndef INSCRITO_H
#define INSCRITO_H
using namespace std;

class Inscrito {
	unsigned int cedula; 
	char codMaterias[15];
	int totalUC;
	
	friend ostream & operator<<(  ostream &os, Inscrito  c ) { 
		os<<"C.I:"<<c.cedula<<"  Inscritas:"<<c.codMaterias<<"  Total U.C.:"<<c.totalUC; 
    	return os;
	} 
	
	public:
		Inscrito() {}
		Inscrito(unsigned int cedula, char *codMaterias , int totalUC) {
			this->cedula = cedula;
			strcpy(this->codMaterias, codMaterias);
			this->totalUC = totalUC;
		}
		
		unsigned int getCedula() { return cedula; }
		
		void setCedula(unsigned int ced) { cedula = ced; }
		
		char* getCodMaterias() { return codMaterias; }
		
		bool operator==(Inscrito &a)
		{
			bool aux = false;
			if(this->cedula==a.cedula) aux=true;
			return aux;
		}
		bool operator>=(Inscrito &c) 
		{
			return this->cedula >= c.cedula;
		}
		bool operator<=(Inscrito &c) 
		{
			return this->cedula <= c.cedula;
		}
		bool operator>(Inscrito &c) 
		{
			return this->cedula > c.cedula;
		}
		bool operator<(Inscrito &c) 
		{
			return this->cedula < c.cedula;
		}
		
		~Inscrito() {}
};

//funcion para leer los alumnos de un archivo binario
Inscrito transfInscrito(char lin[180]) {
	unsigned int ced;
	int totalUC;
	char codMaterias[15];
	char *p;
	p = strtok(lin, "-");
	ced = atoi(p);
	p = strtok(NULL, "-");
	strcpy(codMaterias, p);
	p = strtok(NULL, "\n");
	totalUC = atoi(p);
	return Inscrito(ced, codMaterias, totalUC);
}

#endif
