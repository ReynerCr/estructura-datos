//Archivo.h
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

template <class T>
class Archivo
{
      fstream obj;
      char nom[60];
      T(*pf)(char *k );
      int tam,totalObj,peso;
      T buffer;
   public:
      Archivo() { }
      Archivo( char *n )                  { strcpy(nom,n);  pf=NULL; tam = 0; }
      Archivo( char *n, T(*f)(char *k ) ) { strcpy(nom,n);  pf=f; tam = 0; }
      void AbrirT( const std::_Ios_Openmode &t ){
		   obj.open(nom,t); 
		   if (!obj.is_open()) 
	        cout<<"No se pudo abrir el archivo "<<nom<<endl;
	  }
      int getTotalObj(){return this->totalObj;}
      bool EstaAbierto() { return obj.is_open(); }
      void Peso()        { peso=sizeof(T);      }
      void Inicio()      { obj.seekg(0,ios::beg); }
      void Limpiar()     { obj.clear();           }
      void Cerrar()      { obj.close();           }
      bool Falla ()      { return obj.fail();     }
      bool Es_Fin()      { return obj.eof();      }
      T    Get_buf()     { return buffer;         }
      void CambiarNom( char *n ) { strcpy(nom, n); }
      void Leer(char c[]){ obj.getline(c,180,'\n'); }
      void LeerB( T &b ){ obj.read((char*)&b,sizeof(T));}
      void LeerBi(int pos){obj.seekg(pos*peso);obj.read((char *)&buffer,peso); }
      void RescribirBi(T &dato,int pos){Limpiar();obj.seekg(pos*peso);obj.write((char *)&dato,peso);}
      void EscribirBi(T dato){Limpiar(); obj.seekp(ios::end);obj.write((char *)&dato,peso);}
      void Posicion(int pos){obj.seekg(pos*peso,ios::beg); }
      void Convertir(char c[] ) { buffer=pf(c); }
      int ImprimirBIN();
      int ImprimirTXT();
      void TotalObj();
      void Ordenar();
      bool Buscar_Simple( T &e );
      bool Buscar_Sec     ( T &bus, int &pos, int flag=0, int Max=999999 );
      bool Buscar_Binario ( T &bus, int flag=0 );  
      void GeneraBin(char *n);
      void GeneraTxt(char *n);
      void setTam();
      int getTam() { setTam(); return tam; }
      void EscribirTXT(T lin) { obj<<lin<<","; }
      char* getNombre() { return nom; }
};

template <class T>
void Archivo<T>::setTam()
{
	tam = 0;
  	if (!Falla())
	{
  		while (!Es_Fin())
		{
			obj.ignore(180, '\n');
			tam++;
		}
	}//!falla
	tam--;
	Inicio();
	Limpiar();
}

template <class T>
void Archivo<T>::TotalObj()
{
	Peso();
	obj.seekg(0,ios::end);
	tam=obj.tellg();
	totalObj=(tam/peso);
}

template <class T>
int Archivo<T>::ImprimirTXT()
{
	tam = 0;
	char cad[180];
	while(!Es_Fin())
	{
		Leer(cad);
		if (!Es_Fin()) {
			cout<<cad<<endl;	
			tam++; //num de lineas
		}
	}
	Posicion(0);
	Limpiar();
	return tam;
}

template <class T>
int Archivo<T>::ImprimirBIN()
{
	T aux;
	int total=sizeof(aux);
	bool pa=false;
	Limpiar(); Inicio(); 
	obj.read((char *)&buffer,sizeof(aux));
	tam = 0;
	while(!this->Es_Fin())
	{
		tam++;
		cout<<buffer<<endl;
		obj.seekg(total*tam);
		obj.read((char *)&buffer,sizeof(aux));
	}
	Posicion(0);
	Limpiar();
	return tam;
}

template <class T>
void Archivo<T>::GeneraBin(char *n)
{
  fstream bin;	
  char aux[60];
  bin.open(n,ios::out|ios::binary);
  Peso();
  Leer(aux);
  Limpiar();
  while(!Es_Fin())
  {
  	Convertir(aux);
  	bin.write((char *)&buffer,sizeof(T));
  	Leer(aux);
  }
  bin.close();
  cout<<"Se genero el archivo binario"<<endl;
}

template <class T>
void Archivo<T>::GeneraTxt(char *no)
{
   fstream txt;
   int n=0,num=0;
   txt.open(no,ios::out);
   LeerBi(0);
   Limpiar();
   while(!Es_Fin())
   {
   	 n++;
   	 txt<<buffer.Get_palabra()<<endl;
   	 LeerBi(n);
   }
	txt.close();
	cout<<"Se genero el archivo txt"<<endl;
}

template <class T>
bool Archivo<T>::Buscar_Simple( T &e )
{
     char lin[50]; bool ban=false; int cont=0;
     LeerBi(0);
     Limpiar();
     while(!Es_Fin()&&ban==false)
    {
      if (e==buffer) {
         e=buffer;
         ban=true;
      }
	  else
	  {
	  	cont++;
        LeerBi(cont);
	  }
    }
    return ban;
}

template <class T>
bool Archivo<T>::Buscar_Sec( T &bus, int &pos, int flag, int Max )
{
     int i=pos;
     bool enc=false;
     Limpiar();
     Posicion(pos);
     Limpiar();
     while ( i<=Max && !enc )
     { 
       LeerB(buffer);  
       if ( Es_Fin() ) break; 
       if ( bus.get_clave(flag)==buffer.get_clave(flag) )
       {
           enc=true;
           bus= buffer;
           pos= i;
       }
	   else i++;
     } // fin while 
     return enc;        
}

template <class T>
bool Archivo<T>::Buscar_Binario( T &bus, int flag  )
{
     bool enc=false;
     int li=0, ls=totalObj-1, pm;
     Limpiar();
     while ( !enc && li<=ls )
     {
           pm= (li+ls)/2;
           Posicion(pm);
           LeerB(buffer);
           if ( bus.get_clave(flag)==buffer.get_clave(flag) )
           {
                enc=true;
                bus=buffer;
           }
           else if ( bus.get_clave(flag)< buffer.get_clave(flag) )
                ls= pm-1;
           else
                li= pm+1;
     }
     return enc;
}

template <class T>
void Archivo<T>::Ordenar()
{
     T aux, ini;
     int i, j, pmen;  
     Limpiar();Inicio();
     for ( i=0; i<totalObj;)
     {
        Posicion(i);
        LeerB(aux); ini= aux;
        pmen=i;
        for (j=i+1; j<totalObj; j++)
        {
        	
            Posicion(j);
            LeerB(buffer);
            if (buffer < aux)
            {
                 aux= buffer;
                 pmen= j;
            }
        } // fin for j
        if ( i!=pmen )
        {
             RescribirBi(aux,i);
             RescribirBi(ini,pmen);
        }
		i++;
     }// fin for i 
}


