//main.cpp
#include <ctype.h>
#include <iostream>
#include "Diccionario.h"
#include "Palabra.h"
#include <cmath>

using namespace std;

int main() {
	Diccionario dic((char *) "ordenada.txt");
	int tiempo;
	clock_t t;
	
	t = clock();
		dic.ordenar(0);
		t = clock() - t;
		
		cout<<"FINALIZADO EN "<<(((float)t)/CLOCKS_PER_SEC)<<"SEGUNDOS, "
		<<(float)((((float) t)/CLOCKS_PER_SEC)/(pow(10, 6)))<<" MICROSEGUNDOS, O "
		<<(double)((((float) t)/CLOCKS_PER_SEC)/(pow(10, 9)))<<" NANOSEGUNDOS"<<endl;
	
	return 0;
}
