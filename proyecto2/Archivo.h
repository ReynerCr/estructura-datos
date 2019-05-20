//Archivo.h
#include <iostream>
#include <fstream>
#include <string.h>

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
      Archivo( char *n )                  { strcpy(nom,n); Peso();TotalObj(); pf=NULL; }
      Archivo( char *n, T(*f)(char *k ) ) { strcpy(nom,n); Peso();TotalObj(); pf=f;    }
      void AbrirT( const std::_Ios_Openmode &t ){ obj.open(nom,t); }
      bool EstaAbierto() { return obj.is_open(); }
      void Peso()        { peso=sizeof(buffer);      }
      void Inicio()      { obj.seekg(0,ios::beg); }
      void Limpiar()     { obj.clear();           }
      void Cerrar()      { obj.close();           }
      bool Falla ()      { return obj.fail();     }
      bool Es_Fin()      { return obj.eof();      }
      T    Get_buf()     { return buffer;         }
      void CambiarNom( char *n ) { strcpy(nom, n); }
      void Leer(char c[]){obj.getline(c,59,'\n'); }
      void LeerB( T &b ){Peso(); obj.read((char*)&b,peso);}
      void LeerBi(int pos){obj.seekg(pos*peso);obj.read((char *)&buffer,peso); }
      void RescribirBi(T dato,int pos){obj.seekg(pos*peso);obj.write((char *)&dato,peso);}
      void EscribirBi(T dato){Limpiar(); obj.seekp(ios::end);obj.write((char *)&dato,peso);}
      void Posicion(int pos){obj.seekg(pos*peso,ios::beg); }
      void Convertir(char c[] ) { buffer=pf(c); }
      void MostrarBi();
      void TotalObj();
      void Ordenar();
      bool Buscar_Simple( T &e );
      bool Buscar_Sec     ( T &bus, int &pos, int flag=0, int Max=999999 );
      bool Buscar_Binario ( T &bus, int flag=0 );  
      void GeneraBin(char *n);
      void GeneraTxt(char *n);
};

template <class T>
void Archivo<T>::TotalObj()
{
	obj.seekg(0,ios::end);
	tam=obj.tellg();
	totalObj=(tam/peso);
	//cout<<"total obj:"<<totalObj<<endl;
}

template <class T>
void Archivo<T>::MostrarBi()
{
	T aux;
	int num=0,n=0,total=sizeof(aux);
	bool pa=false;
	Limpiar();
	obj.read((char *)&buffer,sizeof(T));
	while(!this->Es_Fin())
	{
		n++;
		num++;
		cout<<buffer<<endl;
		obj.seekg(total*n);
		obj.read((char *)&buffer,sizeof(T));
	}
	Limpiar();
	Posicion(0);
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
     Peso();
     Limpiar();
     for ( i=0; i<totalObj-1; i++ )
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
     }// fin for i 
}

