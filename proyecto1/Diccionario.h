#ifndef DICCIONARIO_H
#define DICCIONARIO_H
//#include "Archivo.h"
#include <fstream>
#include <string.h>
#include "ordenamiento.h"
#include "busqueda.h"

class Diccionario {
	char palabras[10][23];
	int totalPalabras;
	
	public:
		
		Diccionario(char *nomArchivo) {
			//Archivo<char **> arc = Archivo(nomArchivo);
			fstream arch;
			arch.open(nomArchivo, ios::out | ios::in);
			if (!arch.fail()) {
				while (!arch.eof()) {
					char reg[23];
					arch.getline(reg, 23, '\n');
					if (!arch.eof())
						memcpy(reg, palabras[totalPalabras], sizeof(reg));
					cout<<palabras[totalPalabras]<<endl;
					totalPalabras++;
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
		
		~Diccionario() {}
};

#endif
