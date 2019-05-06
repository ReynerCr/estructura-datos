#include <ctype.h>
#include <iostream>
#include "Diccionario.h"
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	Diccionario dic((char *) "lista10.txt");
	dic.desordenarPalabras();
	dic.ordenar(0); //quicksort
	for (int i = 0; i < ; i++) {
		cout<<dic.getPalabra(i)<<endl;
	}//for
	
	
	
	cout<<endl<<"Total de palabras: "<<dic.getTotalPalabras()<<endl;
	cout<<"Presione una tecla para salir.";
	getchar();
	return 0;
}//int main
