#include <ctype.h>
#include <iostream>
#include "Diccionario.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	Diccionario dic((char *) "ordenada.txt");
	dic.desordenarPalabras();

	for (int i = 0; i < dic.getTotalPalabras(); i++) {
		cout<<dic.getTextoPalabra(i)<<endl;
	}//for
	
	dic.ordenar(1); //1 fallan
	
	cout<<endl<<endl<<"ordenados:"<<endl;
	for (int i = 0; i < dic.getTotalPalabras(); i++) {
		cout<<dic.getTextoPalabra(i)<<endl;
	}//for
	
	cout<<endl<<"Total de palabras: "<<dic.getTotalPalabras()<<endl;
	cout<<"Presione una tecla para salir.";
	getchar();
	return 0;
}//int main
