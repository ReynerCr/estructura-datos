//CarPos.h
//CarPos: caracter posicion
#ifndef CARCOD_H
#define CARCOD_H

struct carCod
{
	char carNor; //caracter no codificado
	char carCodi; //caracter codificado
	
	carCod(char carNor, char carCodi) { this->carNor = carNor; this->carCodi = carCodi; }
	carCod() { this->carNor = '\0'; this->carCodi = '\0'; }
	
	bool operator==(carCod obj) { return (this->carNor == obj.carNor); }
	bool operator==(char c) { return (this->carNor == c); }
	bool operator<(carCod obj) { return (this->carNor < obj.carNor); }
	bool operator>(carCod obj) { return (this->carNor > obj.carNor); }
	bool operator<=(carCod obj) { return (this->carNor <= obj.carNor); }
	bool operator>=(carCod obj) { return (this->carNor >= obj.carNor); }
	void operator=(carCod obj) { this->carNor = obj.carNor; this->carCodi = obj.carCodi; }
	//void operator=(char c) { this->carNor = c; }
	friend ostream& operator<<(ostream &os, carCod c) { os<<"("<<c.carNor<<","<<c.carCodi<<")"; return os; };
};

#endif




