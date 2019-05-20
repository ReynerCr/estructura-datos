//Alumno.h
#include <iostream>
#include <cstdlib>
#include <string.h>
#ifndef ALUMNO_H
#define ALUMNO_H

using namespace std;

class Alumno {
	unsigned int cedula; //cuando no es unsigned da problemas con numeros grandes
	char nombre[45];
	int codCarrera;
	
	friend ostream & operator<<(  ostream &os, Alumno  c ) { 
		os<<"C.I:"<<c.cedula<<"  Nombre:"<<c.nombre<<"  Carrera:"<<c.codCarrera; 
    	return os;
	} 
	
	public:
		Alumno() {}
		Alumno(unsigned int cedula, char* nombre, int codCarrera) {
			this->cedula = cedula;
			strcpy(this->nombre, nombre);
			this->codCarrera = codCarrera;
		}
		
		void cargarAlumno()
		{
			cout<<"Ingrese Nombre: ";cin.sync();cin.getline(this->nombre,45);
			cout<<"Ingrese codigo de carrera: ";cin.sync();cin>>this->codCarrera;
		}
		
		~Alumno() {}
		
		void setCedula(unsigned int aux)
		{
			this->cedula=aux;
		}
		
		int getCarrera() {
			return codCarrera;
		}
		
		unsigned int getCedula() {
			return cedula;
		}
		
		bool operator==(Alumno &a)
		{
			bool aux = false;
			if(this->cedula==a.cedula) aux=true;
			return aux;
		}
		bool operator>=(Alumno &c)
		{
			return this->cedula >= c.cedula;
		}
		bool operator<=(Alumno &c) 
		{
			return this->cedula <= c.cedula;
		}
		bool operator>(Alumno &c) 
		{
			return this->cedula > c.cedula;
		}
		bool operator<(Alumno &c) 
		{
			return this->cedula < c.cedula;
		}
};

Alumno transfAlumno(char lin[180]) {
	char nomb[45], *p;
	unsigned int ced;
	int codCarr;
	p = strtok(lin, "-");
	ced = atoi(p);
	p = strtok(NULL, "-");
	strcpy(nomb, p);
	p = strtok(NULL, "\n");
	codCarr = atoi(p);
	return Alumno(ced, nomb, codCarr);
}

#endif
