/* 
 + MATERIA: Estructura de datos.
 + AUTORES:
 + Contreras Reyner; C.I: V 26934400;   seccion 2
 + Llanes John; C.I: V 30853320;   seccion 2
*/

#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <cctype>
#include "grafo.h"
#include "fstream"
#include "Queue.h"

using namespace std;

int main(int argc, char *argv[])
{

	//pregunto si el grafo es dirigido o no
	bool dir;
	char resp;
	do
	{
		cout << "Grafo dirigido? S/N   ";
		resp = tolower(_getch());
		if (resp != 's' && resp != 'n')
		{
			cout << "Entrada invalida, repita." << endl << endl;
			fflush(stdin);
		}
	} while (resp != 's' && resp != 'n');
	dir = (resp == 's' ? true : false);
	system("cls");


	fstream arch;

	//cargo grafo.txt y lo muestro
	arch.open("grafo.txt", ios::in);
	if (!arch.is_open())
	{
		cout << "Archivo grafos.txt no encontrado." << endl;
		return -12321;
	}

	cout << "Datos de grafo.txt: " << endl << endl;
	while (true)
	{
		char lin[10];
		arch.getline(lin, 10, '\n');
		if (arch.eof())
			break;
		cout << lin << endl;
	}//while()
	arch.close();

	cout << "---------------------------------------------" << endl << endl;

	//ahora cargo itinerario.txt y lo muestro
	arch.open("itinerario.txt", ios::in);
	if (!arch.is_open())
	{
		cout << "Archivo itinerario.txt no encontrado." << endl;
		return -12321;
	}

	Queue<char>itinerario;
	cout << "Datos de itinerario.txt: " << endl << endl;
	while (true)
	{
		char lin[10];
		arch.getline(lin, 10, '\n');
		if (arch.eof())
			break;
		cout << lin << endl;
		itinerario.add(lin[0]); //primera linea guarda el nombre
	}//while()
	arch.close();

	//cargo el grafo y lo muestro
    Grafo g((char*)"grafo.txt", ' ', dir);
	cout << endl << "MOSTRAR DATOS CARGADOS DEL GRAFO: "<<endl;
	g.Imprimir();
	cout << endl;

    g.FloydCamino();
	cout << endl;

	g.imprimirMd();
	cout << endl;

	g.imprimirCams();
	cout << endl;

	cout << "---------------------------------------------" << endl<<endl;
	
	//ahora si voy a mostrar la trayectoria del cartero:
	cout << "Recorrido del cartero: " << endl;
	char ori, dest;

	itinerario.delet(ori);
	while (itinerario.delet(dest))
	{
		cout << "Comenzando en " << ori << " para llegar a " << dest << ": ";
		g.imprimirCamino(g.camino(ori, dest));
		ori = dest;
	}

    cout<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}//int main()
