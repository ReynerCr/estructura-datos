//Carrera.h
#include <iostream>
#include <cstdlib>
#include <string.h>
#ifndef CARRERA_H
#define CARRERA_H

using namespace std;
class Carrera
{
      char nombreC[25];
      int codigo;

   public:
      Carrera() { }
      Carrera( int codigo,char *c) { this->codigo=codigo; strcpy(this->nombreC,c); }
      char *getNombreC(){ return nombreC; }
      int getCodigo() { return codigo; }
      bool operator==(Carrera &a)
      { 
    	bool aux=false;
    	if(this->codigo==a.codigo) aux=true;
    	return aux;  
      }
      friend ostream & operator<<(  ostream &os, Carrera c ) { 
        os<<"Codigo:"<<c.codigo<<" Nombre Carrera:"<<c.nombreC; 
        return os;
      } 
};

#endif

Carrera transfCarrera( char c[60] )
{
	int var1=0;
	char var2[40], *p;
	p=strtok(c,"-");
	var1=atoi(p);
	p=strtok(NULL,"-");
	strcpy(var2,p);
	return ( Carrera(var1,var2) );
}
