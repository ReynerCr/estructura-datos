/*
 + MATERIA: Estructura de datos.
 + AUTOR:
 + Contreras Reyner; C.I: V 26934400;   seccion 2
*/

#include <iostream>
#include <limits>
#include <conio.h>
#include "Codificador.h"
#include "CircDobList.h"

using namespace std;

int main(int argc, char** argv) {
	
	Codificador codificador;
	if(codificador.vacio())
	{
		_getch();
		cout<<"Abortando."<<endl;
		return 123456; //codigo random para indicar salida forzada
	}

	char nomArch[30];
	while(true)
	{
		cout << "Escriba nuevo nombre de archivo que va a codificar: ";
		cin.getline(nomArch, 29, '\n');
		if (cin.eof())
			return 21312412;
		if (cin && (nomArch[0] != ' ' && nomArch[0] != '\0'))
			break;
		
		cout << "Mala entrada, repita: " << endl << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}//while

	system("cls");

	if (!codificador.cargarArchivo(nomArch))
	{
		cout << "Abortando." << endl;
		_getch();
		return 123456; //codigo random para indicar salida forzada
	}

	codificador.procesar(nomArch, nomArch);
	
	system("pause");
	return 0;
}//main
