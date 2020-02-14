//Mp3.h
#ifndef MP3_H
#define MP3_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "Archivo.h"
#include "Queue.h"
#include "Cancion.h"
#include "Tiempo.h"

using namespace std;

class Mp3 {
	Archivo<char*>*arch;
	Queue<Cancion>cola;
	Cancion reproduciendo;
	Tiempo tiempo;
	bool activo;
	
	public: 
		Mp3() {
			arch = new Archivo<char*>((char*)"mp3.txt");
			if (arch == 0) {
				cout<<"Problema al crear objeto de archivo, quizas falta memoria."<<endl;
				cout<<"se cerarrar el programa."<<endl;
				exit(EXIT_FAILURE);
			}
			arch->AbrirT(ios::in);
			if (!arch->EstaAbierto()) {
				cout<<"Se cerrara el programa."<<endl;
				delete arch;
				exit(EXIT_FAILURE);
			}
			tiempo.reiniciar();
			activo = false;
			reproduciendo.setNombre((char*)"");
		}//Mp3()
		
		bool reproducir() {
			activo = true;
			return activo;
		}//reproducir
		
		bool detener() {
			if (activo) {
				tiempo.reiniciar();
				activo = false;
			}//if activo
			return activo;
		}//detener()
		
		bool pausar() {
			activo = false;
			return activo;
		}//pausar()
		
		bool siguiente() {
			if (cola.getQuantity() > 0) {
				cola.delet(reproduciendo);
				tiempo.reiniciar();
				pausar();
			}
			else if (arch == 0 && cola.getQuantity() == 0)
				return false;
				
			return true;
		}//siguiente()
		
		bool agregarCola() {
			if (arch != 0 && !arch->Falla()) {
				char cad[180];
				arch->Leer(cad);
				if (!arch->Es_Fin()) {
					cola.add(transfCancion(cad));
					return true;
				}//!es_fin
				else if (arch != 0) {
					arch->Cerrar();
					delete arch;
					arch = 0;
				}//si ya no se puede cargar mas se cierra archivo y se hace null
			}//!falla
			return false;
		}//agregarCola()
		
		Tiempo getTiempoTrans() { return tiempo; }
		Cancion getActual() { return reproduciendo; } //retorna la cancion que se reproduce
		Queue<Cancion> getCola() { return cola; }
		bool estaActivo() { return activo; }
};

#endif
