//TablaLetrasEs.h
#ifndef TABLALETRASES_H
#define TABLALETRASES_H
#include <cctype>

//tabla solo valida para el espanyol
class TablaLetrasEs {
	char caracter[27]; //letras del alfabeto espanyol
	
	public:
		//inicializa las letras
		TablaLetrasEs() {
			int i, j = 0;
			//inicializo en ASCII, haciendo parada en donde va la enye para insertarla
			for (i = 97; i<111; i++) {
				caracter[j] = (char)i;
				j++;
			}//for
			caracter[j] = (char)164;
			j++;
			for (i = 111; i < 123; i++) {
				caracter[j] = (char)i;
				j++;
			}//for
		}//TablaLetrasEs()
		
		//ascii = bool para saber si debo validar por ascii (true) o por ansi (false)
		//este metodo se puede optimizar quizas no devolviendo un entero, sino usando puntero
		//crear otro aux para no modificar el original no me parece correcto, mejorar
		int getEquiv(char *car, bool ascii, bool edit) const { //retorna -1 si no es letra del espanyol
			int i = 0;
			char aux = tolower((int)(*car));;
			
			while (i < 27 && aux != caracter[i])
				i++;
			unsigned char a = *car;
			if (i < 27) //encontrado entre caracteres de ascii basico
				return ++i;
			if (ascii) { //ansi
				a = (char)(getAnsi((int)(*car), &i));
			}//if caracteres no codificados en ascii
			else if (!ascii) { //ascii
				a = (char)(getAscii((int)(*car), &i));
			}//if codificados en ascii
			if (edit);
				*car = a;
			if (i == -1) {//no hubo cambio al comparar con car esp
				throw "No es caracter del abecedario espanyol";
			}
			return i;
		}//getEquiv(char)
		
		//compara valor en ansi y devuelve en ascii
		int getAscii(int val, int *posTabla) const {
			if (val < 0)
				val += 256;
			
			switch (val) {
				case 225: val = 160; *posTabla = 1; break;
				case 228: val = 132; *posTabla = 1; break;
				case 193: val = 181; *posTabla = 1; break;
				case 196: val = 142; *posTabla = 1; break;

				case 233: val = 130; *posTabla = 5; break;
				case 201: val = 144; *posTabla = 5; break;
				case 203: val = 211; *posTabla = 5; break;
				case 235: val = 137; *posTabla = 5; break;

				case 205: val = 214; *posTabla = 9; break;
				case 237: val = 161; *posTabla = 9; break;
				case 239: val = 139; *posTabla = 9; break;
				case 207: val = 216; *posTabla = 9; break;

				case 243: val = 162; *posTabla = 16; break;
				case 246: val = 148; *posTabla = 16; break;
				case 211: val = 224; *posTabla = 16; break;
				case 214: val = 153; *posTabla = 16; break;

				case 250: val = 163; *posTabla = 22; break;
				case 218: val = 233; *posTabla = 22; break;
				case 252: val = 129; *posTabla = 22; break;
				case 220: val = 154; *posTabla = 22; break;

				case 209: val = 165; *posTabla = 15; break;
				case 241: val = 164; *posTabla = 15; break;
				
				//igualo val a ' ' y posTabla a -1
				default: val = 32; *posTabla = -1; break; //no es letra en ansi
			}//switch val
			
			return val;
		}//getAscii(char)
		
		//compara valor en ascii y devuelve en ansi
		int getAnsi(int val, int *posTabla) const {
			if (val < 0)
				val += 256;
				
			switch (val) {
				case 160: val = 225; *posTabla = 1; break;
				case 132: val = 228; *posTabla = 1; break;
				case 181: val = 193; *posTabla = 1; break;
				case 142: val = 196; *posTabla = 1; break;

				case 130: val = 233; *posTabla = 5; break;
				case 137: val = 235; *posTabla = 5; break;
				case 144: val = 201; *posTabla = 5; break;
				case 211: val = 203; *posTabla = 5; break;

				case 161: val = 237; *posTabla = 9; break;
				case 139: val = 239; *posTabla = 9; break;
				case 214: val = 205; *posTabla = 9; break;
				case 216: val = 207; *posTabla = 9; break;

				case 162: val = 243; *posTabla = 16; break;
				case 148: val = 246; *posTabla = 16; break;
				case 224: val = 211; *posTabla = 16; break;
				case 153: val = 214; *posTabla = 16; break;

				case 163: val = 250; *posTabla = 22; break;
				case 129: val = 252; *posTabla = 22; break;
				case 233: val = 218; *posTabla = 22; break;
				case 154: val = 220; *posTabla = 22; break;

				case 165: val = 209; *posTabla = 15; break;
				case 164: val = 241; *posTabla = 15; break;
				//"¤" == "ñ"
				//igualo val a ' ' y posTabla a -1
				default: val = 32; *posTabla = -1; break; //no es letra en ascii extendido
			}//switch val
			return val;
		}//getAnsi(char)
		
		char getCaracter(int pos) const { //retorna 0 si no es pos valida
			--pos;
			if (pos >= 0 && pos < 27)
				return caracter[pos];
			else 
				return (char)-1;
		}//getCaracter(int)
};//class TablaLetrasES

#endif
