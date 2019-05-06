#ifndef DICCIONARIO_H
#define DICCIONARIO_H
//#include "Archivo.h"
#include <fstream>
#include <string.h>
#include "ordenamiento.h"
#include "busqueda.h"
#include <cmath>
#include <ctime>
#include <Windows.h>

class Diccionario {
	char palabras[10][23];
	int totalPalabras;
	bool ordenado;
	
	public:
		
		Diccionario(char *nomArchivo) {
			//Archivo<char **> arc = Archivo(nomArchivo);
			fstream arch;
			arch.open(nomArchivo, ios::out | ios::in);
			totalPalabras = 0;
			ordenado = false;
			if (!arch.fail()) {
				while (!arch.eof()) {
					char reg[23];
					arch.getline(reg, 23, '\n');
					if (!arch.eof()) {
						strcpy(palabras[totalPalabras], reg);
						totalPalabras += 1;
					}
				}//while
				
			}//if no fallo
			else {
				cout<<"fallo al abrir el archivo"<<endl;
			}
			
			arch.close();
		}//Diccionario()
		
		Diccionario(int totalPalabras, char **palabras) {
			this->totalPalabras = totalPalabras;
			for (int i = 0; i < totalPalabras; i++)
				strcpy(this->palabras[i], palabras[i]);
				
			ordenado = false;
		}
		
		void anyadirPalabra() {  }
		int getTotalPalabras() { return totalPalabras; }
		void guardar() {
			fstream arch;
			arch.open("Diccionario2.txt");
			
			arch.close();
		}
		
		char* getPalabra(int pos) {
			return palabras[pos];
		}
		
		int encontrarPalabra(char* clave) {
			int pos = -1;
			//hace el metodo de busqueda
			return pos;
		}
		
		void desordenarPalabras() {
			int i;
			srand(time(NULL));
			int aux;
			char copia[sizeof(palabras[0])/sizeof(palabras[0][0])];
			for (i = 0; i < totalPalabras; i++) {
				aux = (rand()%totalPalabras);
				strcpy(copia, palabras[i]);
				strcpy(palabras[i], palabras[aux]);
				strcpy(palabras[aux], copia);
			}//for
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
					radixSort(palabras, totalPalabras);
					break;
				case 6:
					shellSort(palabras, totalPalabras);
					break;
				default:
					quickSort(palabras, totalPalabras);
					break;
			}//switch(caso)
		}//ordenar
		
		template<class T>
		void buscar(int caso, T clave) {
			if (!ordenado) {
				ordenar(0); //quickSort
				ordenado = true;
			}

			int pos;
			switch(caso) {
				case 1:
					pos = busquedaBinaria(palabras, totalPalabras, clave);
					break;
				case 2:
					pos = hashFuncPlegamiento(palabras, totalPalabras, clave);
					break;
				case 3:
					pos = hashEspacioLibre(palabras, totalPalabras, clave);
					break;
				default:
					pos = busquedaLinealBloque(palabras, totalPalabras, clave);
					break;
			}//switch(caso)

			if (pos != -1) {
				cout<<"Elemento encontrado en la pos "<<pos<<endl;
			}
			else
				cout<<"No se encontro el elemento."
		}//buscar
		
		~Diccionario() {}
};

#endif
