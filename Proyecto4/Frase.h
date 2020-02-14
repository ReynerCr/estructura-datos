//Frase.h
//Esta clase contendra por un breve momento la frase u oracion que se quiera codificar, y el caso de prueba.
//Luego se codifica y contendra la frase codificada.
#ifndef FRASE_H
#define FRASE_H

#include "CircDobList.h"
#include <string>
#include <string.h>

using namespace std;

class Frase
{
	public:
		int numFrase;
		CircDobList<char>*frase;
		Frase() { numFrase = 0; frase = NULL; }
		
		Frase(int numFrase, char linea[180])
		{
			this->numFrase = numFrase;
			frase = new CircDobList<char>(0); //no ordenada, nuevo elemento de ultimo
			int i = 0;
			while (i < 180 && linea[i] != '\0')
			{
				frase->add(linea[i]);
				i++;
			}//while
		}//Frase(int numFrase, char linea[180])

		string getString() {
			string f;
			int fin = frase->getQuantity();
			frase->reset();
			for (int i = 0; i < fin; i++)
			{
				f += frase->getCurrent();
				frase->move(1);
			}
			return f;
		}//getString()

		void setString(string f)
		{
			if (frase)
				delete frase;

			frase = new CircDobList<char>(0); //no ordenada como cola
			int fin = (int)f.length();
			for (int i = 0; i < fin; i++)
				frase->add(f[i]);
		}//setString(string f)

		bool operator==(Frase fras) { return (this->numFrase == fras.numFrase); }
		bool operator>(Frase fras) { return (this->numFrase > fras.numFrase); }
		bool operator<(Frase fras) { return (this->numFrase < fras.numFrase); }
		bool operator>=(Frase fras) { return (this->numFrase >= fras.numFrase); }
		bool operator<=(Frase fras) { return (this->numFrase <= fras.numFrase); }
		void operator=(Frase fras) { frase = fras.frase; numFrase = fras.numFrase; }
		
		friend ostream& operator<<(ostream& os, Frase& c) {
			c.frase->reset(); c.frase->print();
			os << endl;
			return os;
		};

		void erase() { if (frase != NULL) { delete frase; frase = NULL; } }
};

#endif
