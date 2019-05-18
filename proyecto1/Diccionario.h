//Diccionario.h
#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include <ctype.h>
#include <time.h>
#include "Palabra.h"
#include "archivo.h"
#include "utilidades.h"
#include <Windows.h>   //tiempo en Windows
#include "algoritmos.h"
#include "TablaLetrasEs.h"

using namespace std;

class Diccionario {
	Palabra *palabras;
	int totalPalabras;
	bool ordenado;
	archivo<char*>*arch;
	TablaLetrasEs tabla;

	public:
		Diccionario(char *nomArchivo) {
			totalPalabras = 0;
			tabla = TablaLetrasEs();
			arch = new archivo<char*>(nomArchivo);
			numeroLineas(nomArchivo);
			palabras = new Palabra[totalPalabras];
			cargarPalabras(nomArchivo);
		}//Diccionario()

		Diccionario(int totalPalabras, Palabra *palabras) {
			this->totalPalabras = totalPalabras;
			tabla = TablaLetrasEs();
			for (int i = 0; i < totalPalabras; i++) {
				this->palabras[i] = palabras[i];
			}

			ordenado = false;
		}
		
		int getTotalPalabras() { return totalPalabras; }
		
		Palabra getPalabra(int pos) {
			return palabras[pos];
		}
		
		char* getTextoPalabra(int pos) {
			return palabras[pos].getTexto();
		}
		
		//recorre todo el archivo para conocer el numero de lineas del mismo
		void numeroLineas(char *nomArchivo) {
			totalPalabras = arch->getTam();
		}//numeroLineas()

		void cargarPalabras(char *nomArchivo) {
			ordenado = false;
			int i = 0;
			arch->abrir();
			if (!arch->falla()) {
				while (!arch->esFin()) {
					char reg[24];
					arch->leer(reg);
										
					if (!arch->esFin()) {
						palabras[i].setTexto(reg, &tabla);
							
						i++;
					}
					cin.sync();
				}//while
			}//if no fallo
			else 
				cout<<"Fallo al abrir el archivo"<<endl;
			
			if (arch->estaAbierto())
				arch->cerrar();
		}//cargarPalabras
		
		void guardarPalabras(char *nomArchivo) {
			arch->abrir();
			if(!arch->falla())
				for (int i = 0; i < totalPalabras; i++)
					arch->escribir(palabras[i].getTexto(), 23);
			if(arch->estaAbierto())
				arch->cerrar();
		}//guardarPalabras()
		
		void desordenarPalabras() {
			int i;
			srand(time(NULL));
			int aux;
			Palabra copia[24];
			
			for (i = 0; i < totalPalabras; i++) {
				aux = (rand()%totalPalabras);
				intercambiar(palabras[i], palabras[aux]);
			}//for
			
			guardarPalabras((char*) "desordenado.txt");
			
			ordenado = false;
		}//desordenarPalabras
		
		void ordenar(int caso) {
			switch(caso) {
				case 1:
					burbBand(palabras, totalPalabras);
					break;
				case 2:
					shakesort(palabras, totalPalabras);
					break;
				case 3:
					insDir(palabras, totalPalabras);
					break;
				case 4:
					selDir(palabras, totalPalabras);
					break;
				case 5:
					//radixsort(palabras, totalPalabras);
					break;
				case 6:
					shellsort(palabras, totalPalabras);
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
			delete arch;
		}
};

#endif
