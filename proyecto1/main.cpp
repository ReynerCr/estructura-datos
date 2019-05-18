//main.cpp
#include <ctype.h>
#include <iostream>
#include "Diccionario.h"
#include "Palabra.h"
#include <cmath>
#include "TablaLetrasEs.h"

using namespace std;

int main(int argc, char** argv) {
	TablaLetrasEs tabla = TablaLetrasEs();
	
	cout<<"Voy a cargar datos: "<<endl;
	Diccionario dic((char *) "ordenada.txt");
	int tiempo;
	clock_t t;
	cout<<"Metodos de ordenamiento y busqueda."<<endl<<endl;
	cout<<"Total de palabras: "<<dic.getTotalPalabras()<<endl<<endl;
	
	cout<<"Desordenar y guardar en otro archivo:..."<<endl;
	dic.desordenarPalabras();
	cout<<"Listo"<<endl<<endl;
	
	int i = 1;
	while (i < 8) {
		switch (i) {
			case 1:
				cout<<"Burbuja optima:..."<<endl;
				break;
			case 2:
				cout<<"ShakerSort:..."<<endl;
				break;
			case 3:
				cout<<"Insercion directa:..."<<endl;
				break;
			case 4:
				cout<<"Seleccion directa:..."<<endl;
				break;
			case 5:
				cout<<"RadixSort (NO IMPLEMENTADO):..."<<endl;
				break;
			case 6:
				cout<<"ShellSort:..."<<endl;
				break;
			default:
				cout<<"QuickSort:..."<<endl;
				break;
		}//switch(i)
		t = clock();
		dic.ordenar(i);
		t = clock() - t;
		
		cout<<"FINALIZADO EN "<<(((float)t)/CLOCKS_PER_SEC)<<" SEGUNDOS, "
		<<((((float) t)/CLOCKS_PER_SEC)*(1000))<<" MILISEGUNDOS, O "
		<<(double)((((float) t)/CLOCKS_PER_SEC)*(pow(10, 9)))<<" NANOSEGUNDOS"<<endl;
		
		i++;
		
		cout<<endl<<"-------------------------------------------"<<endl<<endl; //separador
		cout<<"Cargando palabras de archivo desordenado: "<<endl;
		dic.cargarPalabras((char *)"desordenado.txt");
		cout<<"LISTO"<<endl;
		cout<<endl<<"-------------------------------------------"<<endl<<endl;
	}//while para probar los algoritmos de ordenamiento
	i = 0;
	char palp[24];
	Palabra pal;
	while (i < 4) {
		switch(i) {
			case 1:
				cout<<"Busqueda binaria: "<<endl;
				break;
			case 2:
				cout<<"Hashing con funcion plegamiento(NO IMPLEMENTADO): "<<endl;
				break;
			case 3:
				cout<<"Hashing espacio libre(NO IMPLEMENTADO): "<<endl;
				break;
			default:
				cout<<"Busqueda linea por bloque: "<<endl;
				break;
		}//switch(caso)
		
		cout<<endl<<"Que elemento desea buscar?   ";
		cin.sync();
		cin.getline(palp, 24);
		pal.setTexto(palp);
		
		t = clock();
		dic.buscar(i, pal);
		t = clock() - t;
		
		cout<<"FINALIZADO EN "<<(((float)t)/CLOCKS_PER_SEC)<<" SEGUNDOS, "
		<<((((float) t)/CLOCKS_PER_SEC)*(1000))<<" MILISEGUNDOS, O "
		<<(double)((((float) t)/CLOCKS_PER_SEC)*(pow(10, 9)))<<" NANOSEGUNDOS"<<endl;
		
		i++;
		cout<<endl<<"-------------------------------------------"<<endl<<endl; //separador
	}//while para probar los algoritmos de busqueda
	
	cout<<endl<<"Presione una tecla para salir.";
	getchar();
	return 0;
}//int main
