#include <iostream>
using namespace std;

template <class T>
class Cola_Array
{
	private:
		T *V;
		int TAM,FRE,FIN;
		T ELI,VALINI;
		bool FREFIJ;
	public:	
		Cola_Array(int size,T INI,bool ban);
		int Agregar(T ELE);
		int Eliminar();
		void Imprimir();
		T Get_Eliminar(){return ELI;}
		bool Esta_Vacia(){return FRE==-1;}
		T Get_Primero(){return (Esta_Vacia()?VALINI:V[FRE]);}
};

template<class T>
Cola_Array<T>::Cola_Array(int size,T INI,bool ban) //ban=FREFIJ=true cola estatica false=cola circular
{
	TAM=size;
	ELI=VALINI=INI;
	FRE=FIN=-1;
	FREFIJ=ban;
	V=new T[TAM];
	for(int i=0;i<TAM;i++)
	{
		V[i]=INI;
	}
}

template<class T>
int Cola_Array<T>::Agregar(T ELE)
{
    if((FIN+1)%TAM==FRE) return 0;
    if(Esta_Vacia()){V[0]=ELE;FRE=FIN=0;}
    else{V[(FIN+1)%TAM]=ELE;FIN=(FIN+1)%TAM;}
}

template<class T>
void Cola_Array<T>::Imprimir()
{
	if (Esta_Vacia())
		return ;
	
	int i = FRE;
	cout<<"ELEMENTO: ";
	do
	{
		cout<<V[i]<<" ";
		i = (i+1) % TAM;
	} while (i != (FIN + 1) % TAM);
	cout<<endl;
}//Imprimir()

template <class T>
int Cola_Array<T>::Eliminar()
{
	if(Esta_Vacia())	
	{
		return 0;
	}//if esta vacio
	else
	{
		ELI = V[FRE];
		V[FRE] = VALINI;
		if (FRE==FIN)
		{
			FRE = -1;
			FIN = -1;
		}
		else
		{
			if (FREFIJ)
			{
				for(int i = FRE; i < FIN; i++)
					V[i] = V[i+1];
				V[FIN] = VALINI;
				FIN--;
			}//if FEFIJ
			else
				FRE = (FRE + 1) % TAM;
		}//else
	}//else esta vacio
	return 0;
}//Eliminar()
