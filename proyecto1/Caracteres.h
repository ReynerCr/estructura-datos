//Caracteres.h
#ifndef CARACTERES_H
#define CARACTERES_H

class Caracteres {
	char caracteres[27];
	
	public:
		Caracteres() {
			int i, j = 0;
			//97 = a
			for (i = 97; i<111; i++) {
				caracteres[j] = (char)i;
				j++;
			}
			caracteres[j] = (char) 164;
			j++;
			for (i = 111; i < 123; i++) {
				caracteres[j] = (char)i;
				j++;
			}
		}//Caracteres()
		
		//retorna 0 cuando no se consigue el caracter
		int getNum(char caracter) {
			int i = 0;
			
			//65-90 A-Z
			//97-122 a-z  diferencia de a y A es 32, o sea, espacio
			//ñ 164, Ñ 165
			//a   e   i   o   u    //vocales
			//160 130 161 162 163
			aux = (int) caracter;
			if (aux < 0)
				aux += 256; //arreglo ascii por si da negativo
			if (aux < 97 && aux + 32 >= 97 && aux + 32 <= 122)
				aux += 32;
			else if (aux > 122) {
				switch (aux) {
					//tildes
					case 160:
						aux = 97;
						break;
					case 130:
						aux = 101;
						break;
					case 161:
						aux = 105;
						break;
					case 162:
						aux = 111;
						break;
					case 163:
						aux = 117;
						break;
					//dieresis
					case 132:
						aux = 97;
						break;
					case 137:
						aux = 101;
						break;
					case 139:
						aux = 105;
						break;
					case 148:
						aux = 111;
						break;
					case 129:
						aux = 117;
						break;
				}//switch(aux)
				
				caracter = (char) aux; //cambio el caracter con su equivalente
			}//else
			
			if (aux >= 97 && aux <= 122) {
				while (i < 27 && caracter[i] != caracter) { //error
					i++;
				}//while
				
				if (i >= 27)
					i = 0; //no encontrado
				else 
					i++;
			}//if
				
			return i;
		}//getEquivalencia()
		
		char getCaracter(int pos) {
			return caracteres[pos];
		}
		
		int getPos(char caracter) {
			int i = 0;
			while (i < 27 && caracteres[i] != caracter)
				i++;
			
			if (i >= 27)
				i = -1; //no se encontro
			
			return i;
		}//getPos
		
		char* getCaracteres() {
			return caracteres;
		}
};//class Caracteres

#endif





