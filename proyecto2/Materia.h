//Materia.h
#include <iostream>
#include <cstdlib>
#include <string.h>
#ifndef MATERIA_H
#define MATERIA_H

using namespace std;
class Materia
{
      char nombreM[35];
      int semestre;
      int codigo;
      int UC;
   public:
      Materia() { }
      Materia( int semestre,int codigo,char *c,int UC ) { this->semestre=semestre;this->codigo=codigo; strcpy(this->nombreM,c);this->UC=UC; }
      char *Get_nombreM(){ return nombreM; }
      bool operator>(Materia &a){ }
      
      int getCodigo() {	return codigo; }
	  
	  int getUC()
	  {
	  	return UC;
	  }
      
      int getSemestre(){return this->semestre;}
      
      void setCodigo(int cod) { codigo = cod; }
      
	  bool operator==(Materia &a)
      { 
	      bool aux=false;
	      if(this->codigo==a.codigo)aux=true;
	      	return aux;  
      }
      
      friend ostream & operator<<(  ostream &os, Materia c ) { 
        os<<"Semestre:"<<c.semestre<<"  Codigo:"<<c.codigo<<"  Nombre:"<<c.nombreM<<"  U.C:"<<c.UC; 
        return os;
      } 
};

#endif

Materia transfMateria( char c[180] )
{
	int var1=0,var2=0,var4=0;
	char var3[35], *p;
	p=strtok(c,"-");
	var1=atoi(p);
	p=strtok(NULL,"-");
	var2=atoi(p);
	p=strtok(NULL,"-");
	strcpy(var3,p);
	p=strtok(NULL,"-");
	var4=atoi(p);
	return ( Materia(var1,var2,var3,var4) );
}
