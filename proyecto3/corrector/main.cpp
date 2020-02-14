#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Palabra.h"
#include "Archivo.h"
#include "Stack.h"
#include "List.h"
#include "gotoxy.h"

extern const TablaLetrasEs tabla = TablaLetrasEs();

//bool validacion sirve para indicar si se va a comprobar lista o no
void cambiarColorPalabra(Palabra pal, bool validacion) {
	COORD xy;
	int x, y;
	xy = getCoord();
	x = xy.X;
	y = xy.Y;
	int i = strlen((char*)pal.getTexto());
	if (validacion)//si la palabra no se encontro
	{
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),4);
		xy.X = xy.X - 2;
	}
		
	else // si se esta borrando
	{
		SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),7);
		xy.X = xy.X - 1;
	}
		
	gotoxy(xy.X, xy.Y);
	i--;
	while (i >= 0)
	{
		xy = getCoord();
		printf("%c", pal.getTextoI(i));
		gotoxy(xy.X-1, xy.Y);
		i--;
	}
	gotoxy(x, y);
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),7);
}//cambiarColorPalabra()

int main() {
	setlocale(LC_ALL, "es_ES"); //arregla impresion y lectura en ASCII
	
	//Crear el archivo e intentar abrirlo. Si falla se cierra el programa.
	Archivo<Palabra>arch((char*)"diccionario.txt");
	arch.AbrirT(ios::in);
	if (!arch.EstaAbierto()) {
		cout<<"Se cerrara el programa."<<endl;
		exit(EXIT_FAILURE);
	}
	
	int totalPalabras;
	List<Palabra>lista;
	unsigned char cad[40];
	
	//impresion de archivo y carga de la lista
	cout<<"IMPRESION DE ARCHIVO:"<<endl;
	while (!arch.Es_Fin()) {
		arch.Leer((char*)cad);
		if (!arch.Es_Fin()) {
			cout<<cad<<endl;
			Palabra pal(cad, false, true); //archivo en ansi
			lista.add(pal);
		}//if
	}//while
	arch.Cerrar(); //cierra archivo
	/*
		cout<<"IMPRESION DE LISTA: "<<endl;
		lista.print();
		cout<<endl;
	*/
	
	cout<<endl<<endl<<endl<<endl;
	cout<<"Instrucciones:"<<endl
		<<"Ingrese texto y al final un punto. No mas de 40 caracteres."<<endl
		<<"No se pueden insertar tabuladores, espacios o parecidos (no flechas de direccion)"
		<<"o se cerrara el programa."<<endl;

	Stack<Palabra>pila;
	//ponerle a la consola un tamanyo desde aqui, para limitar
	COORD xy = getCoord(); //obtener coordenadas xy de la pos actual de consola
	
	char c = 0; //caracter leido
	cad[0] = '\0'; //para fines de validacion
	int i = 0; //contador de caracteres ingresados en la ultima palabra
	Palabra pal;
	bool espacio = false; //verificar que no se puedan ingresar dos espacios o mas
	do {
		fflush(stdin);
		if (kbhit()) {
			c = getch();
			printf("%c", c);
			xy = getCoord();
			//Valida que no se ingresen varios espacios y arregla el carro en caso de que se haga
			if (espacio && c == ' ') {
				gotoxy(xy.X-1, xy.Y);
				xy = getCoord();
			}//no validos dos espacios seguidos
			else {
				switch(c) {
					case ' ':
					case '.':
						if (i != 0) {
							if (i < 40) { //validacion para evitar errores con el array
								cad[i+1] = '\0';
								i = 0;
								
								//char*, si es ascii true (o ansi false), si se va a cambiar el caracter por su equivalente ascii/ansi
								pal.setTexto(cad, true, false);
								pila.add(pal); //anyado a pila
								cad[0] = '\0'; //para fines de validacion hago vacio el caracter 0
								if (!lista.seek(pal)) //buscar en lista, devuelve true cuando consigue
									cambiarColorPalabra(pal, true); //args: Palabra, bool para indicicar si valida lista o borra
							}//if i<40
							else { //cuando la palabra tiene mas de 40 letras se cierra programa
								cout<<"Palabra muy larga, no se puede comprobar."<<endl
									<<"Se mostraran resultados y se cerrara el programa."<<endl;
							}
						}//if i!=0
						if (c == ' ')
							espacio = true;
						break;
					case 8: //borrar
						if (i > 0) { //cuando borra letras i > 0
							i--;
							cad[i] = '\0';
						}
						else if (i == 0) { //si i es igual a cero borra un espacio, en teoria
							if (pila.getQuantity() > 0) {//compruebo si pila no esta vacia
								pila.delet(pal);
								i = strlen((char*)pal.getTexto());
								strcpy((char*)cad, (char*)pal.getTexto());
								cambiarColorPalabra(pal, false); //cambia pal a color blanco
							}//if
						}//else if i==0
						xy = getCoord();
						printf(" ");
						if (xy.X == 0 && pila.getQuantity() != 0) 
						{
							xy.X = xy.X - 1; //devuelvo carro en 1, gotoxy valida negativos en x
						}
						gotoxy(xy.X, xy.Y);
						xy = getCoord();
						espacio = false;
						break;
					default:
						if (c > 32) { //no vale tabulador ni algunos otros no manejados arriba
							if (i < 40) { //validar cantidad de caracteres escritos
								cad[i] = c;
								i++;
								if (i < 39)
									cad[i] = '\0';
							}//cad[i] < 40
						}//si valido para imprimir
						else { //cuando caracter entre 0 y 31 incluidos de ascii cierra programa
							cout<<"No esta permitido hacer eso."<<endl
								<<"Se mostraran resultados y se cerrara el programa."<<endl;
							c = '.';
						}
						espacio = false;
						break;
				}//switch c	
			}//else
		}//if kbhit
	} while (c != '.');
	
	//imprime pila
	cout<<endl<<endl<<endl<<"Pila de palabras escritas: "<<endl;
	pila.print();
	
	cout<<endl<<endl
		<<"El total de palabras escritas en el documento es de: "<<lista.getQuantity()<<"."<<endl
		<<"El total de palabras escritas por el usuario fue de: "<<pila.getQuantity()<<"."<<endl;
	
	/*
		Compruebo en la misma palabra si los caracteres de la izquierda son iguales
		a los caracteres de la derecha, usando dos iteradores. Si existe algun caracter
		diferente entonces la palabra ya no puede ser palindromo.
	*/
	int palindromos = 0;
	int j, k;
	for (i = 0; i < pila.getQuantity(); i++) {
		pila.delet(pal);
		int length = strlen((char*)pal.getTexto()), k = length-1;
		espacio = true; //reutilizo para comparar palindromos
		for (j = 0; j < length; j++) {
			if (pal.getTextoI(j) == pal.getTextoI(k))
				k--;
			else
			{
				espacio = false;
				break;
			}//else
		}//for
		if (espacio) {
			palindromos++;
		}
	}//for
	
	cout<<"El total de palindromos escritos por el usuario fue de: "<<palindromos<<"."<<endl;
	
	fflush(stdin);
	getch();
	return 0;
}
