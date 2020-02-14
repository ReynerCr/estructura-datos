//Codificador.h
#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <cstring>
#include "MapaCod.h"
#include "CircDobList.h"
#include "List.h"
#include "Archivo.h"
#include <cctype>
#include <cstdlib>
#include "Frase.h"
#include "carCod.h"

class Codificador
{
	Archivo<char*>arch; //archivo auxiliar
	
	bool codificado; //si texto en auxF codificado o no
	//auxF: al inicio son frases para codificar, luego de codificar almacena texto codificado
	CircDobList<Frase> *auxF;
	List<MapaCod> *cp; //cp: casos prueba

	int tCasoPrue; //total casos prueba y numero de mapas
	bool cargarCP(); //cargar casos de prueba y primeras frases a codificar
	bool cargarFrasCodif(); //cargar frases a codificar

	void codificar(); //funcion para codificar; NO SE USA DIRECTAMENTE
	void codificarUno(); //funcion para codificacar la primera vez; NO SE USA DIRECTAMENTE
	void codificarDos(); //funcion para la segunda codificacion; NO SE USA DIRECTAMENTE
	
	public:
		Codificador();
		bool cargarArchivo(char nombre[30]);
		bool escribirArchivo(char nombre[30]); //guarda lo que esta en auxF en un archivo
		void imprimirCP();
		void imprimirFrases();
		bool getCodificado() { return codificado; }
		bool vacio() { return ((!cp) ? true : false); }
		void procesar(char nomArch[30], char nom2[30]); //imprime, codifica e imprime
		~Codificador() { delete cp; delete auxF; if (arch.EstaAbierto()) arch.Cerrar(); };
};

#endif
