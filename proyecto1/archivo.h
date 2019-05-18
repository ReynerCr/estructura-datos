#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

template <class T>
class archivo {
      fstream obj;
      char nom[30];
      T(*pf)(char *k);
      int tam;
      T buf;
      
   public:
      archivo() { }
      archivo( char *n )                  { strcpy(nom,n); tam=0; pf=NULL; abrir(); setTam(); }
      archivo( char *n, T(*f)(char *k ) ) { strcpy(nom,n); tam=0; pf=f; abrir(); setTam(); }
      void abrir( )      { obj.open(nom,ios::in | ios::out); }
      void cerrar()      { obj.close();           }
      bool falla ()      { return obj.fail();     }
      bool esFin()      { return obj.eof();      }
      bool estaAbierto() { return obj.is_open(); }
      T getBuf()        { return buf;            }
      void leer(char c[]){obj.getline(c,180,'\n');}
      void convertir(char c[]) { buf=pf(c); }
      bool buscarSimple( T &e );
      void volverInicio() { obj.clear(); obj.seekg(0, ios_base::beg); }
      int getTam() { return tam; }
      fstream getArc() { return obj; }
      void escribir(char c[], int tam) { obj.write(c, tam); }
      void setTam() {
      	while (!falla()) {
      		while (!esFin()) {
			tam++;
			obj.ignore(180, '\n');
			}
			tam--;
		}//arch.fail
		volverInicio();
	  }
	  
	  ~archivo() { if (estaAbierto())     cerrar(); }
}; //class archivo

template <class T>
bool archivo<T>::buscarSimple( T &e ) {
    char lin[180]; bool ban=false;
    while(!ban) {
      leer(lin);
      if (esFin()) 
	  	break;
      buf = pf(lin);
      if (e == buf) {
         e = buf;
         ban = true;
      }
	}
    return ban;
}
