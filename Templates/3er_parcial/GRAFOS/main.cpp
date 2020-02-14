#include <cstdlib>
#include <iostream>
#include "grafo.h"

using namespace std;

int main(int argc, char *argv[])
{
    Grafo det((char*)"datos.txt", ' ', true);
	det.Imprimir();
	cout << endl << endl;

    det.FloydCamino();
	cout << endl;

	det.imprimirMd();
	cout << endl;

	det.imprimirTodasRutas();
	cout << endl;

    cout<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}