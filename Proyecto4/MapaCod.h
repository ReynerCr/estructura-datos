//MapaCod.h
#ifndef MAPACOD_H
#define MAPACOD_H
#include "CircDobList.h"
#include "carCod.h"

class MapaCod
{
	public:
		int casoPrueba;
		CircDobList<carCod>*caracteres;
		
		MapaCod() { casoPrueba = 0; caracteres = NULL; }
		MapaCod(int cp, bool ini = false) {
			casoPrueba = cp;
			if (ini) caracteres = new CircDobList<carCod>(0);
			else caracteres = NULL;
		}

		MapaCod(int cp, CircDobList<carCod>*caracteres)
		{
			this->casoPrueba = cp;
			this->caracteres = caracteres;
			caracteres = NULL;
		}
		
		bool operator==(MapaCod obj) { return (this->casoPrueba == obj.casoPrueba); }
		bool operator>(MapaCod obj) { return (this->casoPrueba > obj.casoPrueba); }
		bool operator>=(MapaCod obj) { return (this->casoPrueba >= obj.casoPrueba); }
		bool operator<(MapaCod obj) { return (this->casoPrueba < obj.casoPrueba); }
		bool operator<=(MapaCod obj) { return (this->casoPrueba <= obj.casoPrueba); }
		friend ostream& operator<<(ostream &os, MapaCod &c) {
			cout << "CP: " << c.casoPrueba<<endl;
			if (c.caracteres != NULL)
			{
				if (!(c.caracteres->isEmpty()))
				{
					c.caracteres->reset();
					c.caracteres->print(true);
				}
			}
			os << endl;
			return os;
		};
		void operator=(MapaCod obj) { 
			this->casoPrueba = obj.casoPrueba;
			this->caracteres = obj.caracteres;
		}
		void erase() { if (caracteres != NULL) { delete caracteres; caracteres = NULL; } }
};

#endif
