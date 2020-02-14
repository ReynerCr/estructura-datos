#include <iostream>
#include "Mp3.h"
#include <conio.h>
#include <cctype>
#include <windows.h>

using namespace std;

void reimprimir(Mp3 *mp3) {
	system("cls");
	cout<<"Teclas a usar:"<<endl
		<<"R: Reproducir."<<endl
		<<"S: Detener."<<endl
		<<"P: Pausar."<<endl
		<<"N: Siguiente."<<endl
		<<"C: Agregar a la cola."<<endl
		<<endl;
	cout<<"Cola de reproduccion:"<<endl;
	if (mp3->getCola().getQuantity() > 0)
		mp3->getCola().print();
	
	cout<<endl<<endl;
	cout<<"Reproduciendo: "<<mp3->getActual()<<"   Tiempo: "<<mp3->getActual().getTiempo();
	cout<<endl<<endl;
	
	cout<<"Tiempo transcurrido: "<<mp3->getTiempoTrans()<<endl;
	cout<<endl<<endl;
}

int main() {
	Mp3 mp3;
	
	bool aux = false;
	bool fin = false;
	char c = 0;
	int i = 0;
	reimprimir(&mp3);
	while (!fin) {
		if (kbhit()) {
			fflush(stdin);
			c = 0,
			c = tolower(getch());

			switch(c) {
				case 'r': //reproducir
					aux = mp3.reproducir();
					if (aux)
						reimprimir(&mp3);
					break;
				case 'p': //pausar
					aux = mp3.pausar();
					if (aux)
						reimprimir(&mp3);
					break;
				case 's': //detener
					aux = mp3.pausar();
					mp3.getTiempoTrans().reiniciar();
					if (aux)
						reimprimir(&mp3);
					break;
				case 'c': //cargar cancion en cola
					aux = mp3.agregarCola();
					if (aux)
						reimprimir(&mp3);
					break;
				case 'n': //siguiente
					aux = mp3.siguiente();
					if (aux)
						reimprimir(&mp3);
					else 
						fin = true;
					break;
			}//switch(c)
		}//if kbhit()
		
		if (!fin && mp3.estaActivo() && aux) {
			Sleep(1000);
			reimprimir(&mp3);
			mp3.getTiempoTrans().avanzar();
		}
		
		if (mp3.getTiempoTrans() > mp3.getActual().getTiempo()) {
			aux = mp3.siguiente();
			mp3.getTiempoTrans().reiniciar();
			if (!aux)
				fin = true;
		}
	}//while no sea fin de cola
	
	cout<<"Se acabo la cola de reproduccion y las posibles canciones, se cierra reproductor."<<endl;
	
	fflush(stdin);
	getch();
	return 0;
}
