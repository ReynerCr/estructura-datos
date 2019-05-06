#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <fstream>
#include <iostream>
#include <string.h>

template<class T>
class Archivo {
	char nom[30];
	int tam; //lineas
	T reg; //datos
	T (*func)(char cad[180]);
	fstream arch;
	char delim;
	
	public:
		Archivo() { 
			strcpy(nom, "nombre.txt");
			delim = '\n'
		}
		
		Archivo(char *c) { strcpy(nom, c); }
		
		Archivo(char *c, T(*pf)) (char cad[180]) {
			strcpy(nom, c);
			func = pf;
			delim = '\n'
		}
		
		Archivo(char *nom, char delim) {
			strcpy(this-nom, nom)
			this->delim = delim;
		}
		
		void abrir() { arch.open(nom, ios::in | ios::out); }
		
		void cerrar() { 
			if (arch.is_open())
				arch.close();
		}
		
		bool es_fin() { return arch.eof(); }
		bool falla() { return arch.fail(); }
		void leer(char lin[180]) {
			arch.getline(lin, 180, delim);
			if(!es_fin())
				reg = fun(lin);
		}
		
		T getReg() { return reg; }
		bool buscar(T &bus);
		
		char *getNombre() { return nom; };
		int getTam() { return tam; }
		
}; //class archivo

#endif
