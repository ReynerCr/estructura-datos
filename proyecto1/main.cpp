#include <ctype.h>
#include <iostream>
#include "ordenamiento.h"
#include "busqueda.h"

using namespace std;

int main(int argc, char** argv) {
	char menu, loop;
	int vector[] = {3, 2, 1, 7, 5, 9, 4, 5, 8, 6, 0};
	int vectorResultado[11];
	int length = sizeof(vector)/sizeof(*vector);
	int i;
	
	do {
		for (i = 0; i < 11; i++) //copio el array original para no perder sus datos
			vectorResultado[i] = vector[i];
		
		cout<<"Este programa contiene los seis algoritmos que se estudiaron:"<<endl<<endl;
		
		do {
			cout<<"1. Burbuja simple."<<endl;
			cout<<"2. Burbuja con bandera."<<endl;
			cout<<"3. Seleccion directa."<<endl;
			cout<<"4. Shaker sort"<<endl;
			cout<<"5. Busqueda lineal simple."<<endl;
			cout<<"6. Busqueda lineal por bloque."<<endl;
			cout<<"7. Salir."<<endl;
			cout<<"Su respuesta: ";
			
			fflush(stdin);
			menu = getchar();
			
			system("cls");
			int aux;
			switch (menu) {
				case '1':
					insercionDirecta(vectorResultado, length);
				case '2':
					burbujaBandera(vectorResultado, length);
					break;
				case '3':
					seleccionDirecta(vectorResultado, length);
					break;
				case '4':
					shakerSort(vectorResultado, length);
					break;
				case '5':
					cout<<"Vector original: ";
					imprimirArray(vectorResultado, length);
					shellSort(vectorResultado, length);
					imprimirArray(vectorResultado, length);
					break;
				case '6':
					seleccionDirecta(vectorResultado, length);
					cout<<"Vector original: ";
					imprimirArray(vectorResultado, length);
					
					cout<<endl<<endl<<endl<<"Que numero desea buscar?  ";
					cin>>aux;
					cout<<"AUX VALE: "<<aux<<endl;
					aux = busquedaLinealBloque(vectorResultado, length, aux);
					if (aux != -1)
						cout<<endl<<"Se encontro en la posicion "<<aux<<"."<<endl;
					else
						cout<<endl<<"No se encontro el numero en el vector."<<endl;
					break;
				case '7':
					loop = 'n';
					break;
				default:
					cout<<"Respuesta invalida, reingrese valor."<<endl;
					menu = 'n';
					break;
			}//switch()
		} while (menu == 'n');
		
		if (menu != '7') {
			cout<<endl<<endl<<"Desea repetir el programa? S/N: ";
			fflush(stdin);
			loop = tolower(getchar());
		}//if
		system("cls");
	}while (loop != 'n');
	
	return 0;
}//int main
