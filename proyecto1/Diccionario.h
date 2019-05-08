//Diccionario.h
#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include <fstream>
#include <string.h>
#include "ordenamiento.h"
#include "busqueda.h"
#include "Palabra.h"
#include <ctype.h>
#include <iostream>
#include <ctype.h>
#include <time.h>
#include <Windows.h>

class Diccionario {
	Palabra *palabras; //creo que operator= no me deja crear objetos dinamicos
	int totalPalabras;
	bool ordenado;
	
	public:
		Diccionario(char *nomArchivo) {
			totalPalabras = 0;
			numeroLineas(nomArchivo);
			palabras = new Palabra[totalPalabras];
			cargarPalabras(nomArchivo);
		}//Diccionario()
		
		Diccionario(int totalPalabras, Palabra *palabras) {
			this->totalPalabras = totalPalabras;
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
			fstream arch;
			arch.open(nomArchivo, ios::in);
			if(!arch.fail()) {
				while (!arch.eof()) {
					totalPalabras++;
					arch.ignore(24, '\n');
				}
				totalPalabras--;
			}//arch.fail
		}//numeroLineas()

		void cargarPalabras(char *nomArchivo) {
			fstream arch;
			arch.open(nomArchivo, ios::out | fstream::in);
			ordenado = false;
			int i = 0;
			if (!arch.fail()) {
				while (!arch.eof()) {
					char reg[24];
					arch.getline(reg, 24, '\n');
					
					if (!arch.eof()) {
						for (int j = 0; j < 24 && reg[j] != '\0'; j++) {
							reg[j] = tolower(reg[j]);
						}//for
						palabras[i].setTexto(reg);
							
						i++;
					}
					cin.sync();
				}//while
			}//if no fallo
			else 
				cout<<"Fallo al abrir el archivo"<<endl;
			
			if (arch.is_open())
				arch.close();
		}//cargarPalabras
		
		void guardarPalabras(char *nomArchivo) {
			fstream arch2;
			arch2.open(nomArchivo, ios::out);
			
			if(!arch2.fail())
				for (int i = 0; i < totalPalabras; i++)
					arch2<<palabras[i].getTexto()<<endl;
				
			if (arch2.is_open())
				arch2.close();
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
					burbujaOptima(palabras, totalPalabras);
					break;
				case 2:
					shakerSort(palabras, totalPalabras);
					break;
				case 3:
					insercionDirecta(palabras, totalPalabras);
					break;
				case 4:
					seleccionDirecta(palabras, totalPalabras);
					break;
				case 5:
					//radixSort(palabras, totalPalabras);
					break;
				case 6:
					shellSort(palabras, totalPalabras);
					break;
				default:
					quickSort(palabras, 0, totalPalabras - 1);
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
					pos = busquedaBinaria(palabras, totalPalabras, clave);
					break;
				case 2:
					//pos = hashFuncPlegamiento(palabras, totalPalabras, clave);
					break;
				case 3:
					//pos = hashEspacioLibre(palabras, totalPalabras, clave);
					break;
				default:
					pos = busquedaLinealBloque(palabras, totalPalabras, clave);
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
