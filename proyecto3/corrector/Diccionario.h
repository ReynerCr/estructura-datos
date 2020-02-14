//Diccionario.h
#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include <ctype.h>
#include <time.h>
#include "Palabra.h"
#include "Archivo.h"
#include <Windows.h>   //tiempo en Windows
#include "algoritmos.h"
#include "TablaLetrasEs.h"

using namespace std;

extern const TablaLetrasEs tabla = TablaLetrasEs();

Palabra transfPalabra(char lin[180]) {
	return Palabra((unsigned char*)lin, true);
}

class Diccionario {
	Palabra *palabras;
	int totalPalabras;
	bool ordenado;

	public:
		Diccionario(char *nomArchivo) {
			totalPalabras = 0;
			cargarPalabras(nomArchivo);
		}//Diccionario()

		Diccionario(int totalPalabras, Palabra *palabras) {
			this->totalPalabras = totalPalabras;
			for (int i = 0; i < totalPalabras; i++) {
				this->palabras[i] = palabras[i]; //deberia verificar si es ansi o ascii
			}

			ordenado = false;
		}
		
		int getTotalPalabras() { return totalPalabras; }
		
		Palabra getPalabra(int pos) {
			return palabras[pos];
		}
		
		unsigned char* getTextoPalabra(int pos) {
			return palabras[pos].getTexto();
		}
		
		//recorre todo el archivo para conocer el numero de lineas del mismo
		void numeroLineas(Archivo<Palabra>*arch) {
			totalPalabras = arch->getTam();
		}//numeroLineas()

		void cargarPalabras(char *nomArchivo) {
			ordenado = false;
			int i = 0;
			Archivo<Palabra>arch(nomArchivo, transfPalabra);
			arch.AbrirT(ios::in);
			if (arch.Falla()) {
				cout<<"Fallo al abrir el archivo."<<endl; return ;
			}
			numeroLineas(&arch);
			palabras = new Palabra[totalPalabras];
			
			while (!arch.Es_Fin()) {
				unsigned char reg[24];
				arch.Leer((char*)reg);
				if (!arch.Es_Fin()) {
					try {
						palabras[i].setTexto(reg, false, true);
					} 
					catch (const char* msg) { //aqui tendria que hacerlo mucho mas dinamico, que elimine una pos
					//pero eso seria con array dinamico de objetos dinamicos
						cout<<i<<": error "<<msg<<endl;
						i--;//me salto la linea jeje
						palabras[i].setTexto((unsigned char*)"Z", true, false);
					}
					
					i++;
				}//if !Es_Fin
			}//while
			
			if (arch.EstaAbierto())
				arch.Cerrar();
		}//cargarPalabras
	//busquedas malas csm
		void guardarPalabras(char *nomArchivo) {
			Archivo<Palabra>arch(nomArchivo, transfPalabra);
			arch.AbrirT(ios::out);
			if(!arch.Falla()) {
				unsigned char aux[24];
				for (int i = 0; i < totalPalabras; i++)
				if (palabras[i].getTexto() != (unsigned char*)"Z") {
					arch.EscribirTXT((char*)palabras[i].getTextoAnsi(aux));
					for (int j = 0; j < 24 && aux[j] != '\0'; j++)	{
						cout<<aux[j]<<"**"<<(int)aux[j]<<endl;
					}//for
				}//if
			}//if
			if(arch.EstaAbierto())
				arch.Cerrar();
		}//guardarPalabras()
		
		void desordenarPalabras() {
			int i;
			srand(time(NULL));
			int aux;
			Palabra copia[24];
			
			for (i = 0; i < totalPalabras; i++) {
				aux = (rand()%totalPalabras);
				swap(palabras[i], palabras[aux]);
			}//for
			
			ordenado = false;
		}//desordenarPalabras
		
		void ordenar(int caso) {
			switch(caso) {
				case 1:
					//burbBand(palabras, totalPalabras);
					break;
				case 2:
					//shakesort(palabras, totalPalabras);
					break;
				case 3:
					//insDir(palabras, totalPalabras);
					break;
				case 4:
					//selDir(palabras, totalPalabras);
					break;
				case 5:
					//radixsort(palabras, totalPalabras);
					break;
				case 6:
					//shellsort(palabras, totalPalabras);
					break;
				default:
					quicksort(palabras, 0, totalPalabras - 1);
					break;
			}//switch(caso)
			ordenado = true;
		}//ordenar
		
		template<class T>
		void buscar(int caso, T clave) {
			if (!ordenado) {
				ordenar(0); //quickSort
			}
			int pos;
			switch(caso) {
				case 1:
					pos = busqBin(palabras, totalPalabras, clave);
					break;
				case 2:
					//pos = hashPleg(palabras, totalPalabras, clave);
					break;
				case 3:
					//pos = hashEspLib(palabras, totalPalabras, clave);
					break;
				default:
					pos = busqLinBloq(palabras, totalPalabras, clave);
					break;
			}//switch(caso)

			if (pos != -1) {
				cout<<"Elemento encontrado en la pos "<<pos<<endl;
			}
			else
				cout<<"No se encontro el elemento.";
		}//buscar
		
		~Diccionario() {
			delete[] palabras;
		}
};

#endif
