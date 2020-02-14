//Tiempo.h
#ifndef TIEMPO_H
#define TIEMPO_H
#include <iostream>

using namespace std;

class Tiempo {
	int min, seg;
	
	public:
		Tiempo() { min = 0; seg = 0; }
		Tiempo(int mi, int se) { min = mi; seg = se; }
		Tiempo (int tiemposeg) { this->min = tiemposeg / 60; this->seg = tiemposeg % 60; }
		
		int getSeg() { return seg;	}
		int getMin() { return min;	}
		void masSeg() { seg++; }
		void masMin() { min++; }
		void setTiempo(int tiemposeg) { this->min = tiemposeg / 60; this->seg = tiemposeg % 60;	}
		int getTiempoSeg() { return ((this->min * 60) + this->seg); }
		
		void operator= (Tiempo &obj) {
			this->min = obj.getMin();
			this->seg = obj.getSeg();
		}
		
		friend ostream & operator<<(ostream &os, Tiempo c) {
			cout<<c.min<<":"<<c.seg;
			return os;
		}
		
		bool operator==(Tiempo &obj) {
			bool cond = false;
			if (this->min == obj.min && this->seg == obj.seg)
				cond = true;
			return cond;
		}//operator==
		
		bool operator<(int t) {
			return (this->getTiempoSeg() < t);
		}
		
		bool operator<(Tiempo t) {
			return (this->getTiempoSeg() < t.getTiempoSeg());
		}
		
		bool operator>(int t) {
			return (this->getTiempoSeg() > t);
		}
		
		bool operator>(Tiempo t) {
			return (this->getTiempoSeg() > t.getTiempoSeg());
		}
		
		void avanzar() {
			seg++;
			if (seg >= 60) {
				min++;
				seg = 0;
			}
		}
		
		void reiniciar() {
			min = 0;
			seg = 0;
		}
};

#endif
