#ifndef LISTA_H
#define LISTA_H

using namespace std;

template <class T>
class Nodo
{
      T info;
      Nodo<T> *ant, *sig;
      public:
             Nodo()    { ant=sig=NULL; }
             Nodo(T e) { ant=sig=NULL; info=e; }
             void  set_inf( T val )      { info=val; }
             void  set_ant( Nodo<T> *p ) { ant= p;   }
             void  set_sig( Nodo<T> *p ) { sig= p;   }
             T get_inf()        { return info; }
             Nodo<T> *get_sig() { return sig;  }
             Nodo<T> *get_ant() { return ant;  }                          
};

template <class T>
class lista
{
		Nodo<T>* cab, ptMov;
 public:
        Nodo <T> *get_cab() { return cab; }
		Nodo <T> reiniciarPt() { ptMov = cab; }
        Nodo <T> moverPt(int i) {
			int j = 0;
			while (ptMov && j < i)
				ptMov = ptMov->get_sig();
		}
		Nodo<T>* get_ptMov() { return ptMov;	}
        lista ( ) { cab=NULL; }
        int  agregar  ( T nue );
        int  buscar   ( T &bus, Nodo<T> **q=NULL);
        int  eliminar ( T &eli);
        void imprimir ( );
};

template <class T>
int lista<T>::agregar ( T nue ) 
{
  Nodo<T> *p, *q = NULL, *pnue;
  pnue= new Nodo<T>(nue);
  if ( !pnue ) return 0;
  p= cab;
  while (p)
  {
    if (nue==p->get_inf() )  return 0;
    if ( nue<p->get_inf() )  break;
    else
    {
      q= p;  
      p= p->get_sig();
    }
  }
  pnue->set_sig( p );
  if (p==cab) {
     if ( cab ) cab->set_ant(pnue);              
     cab= pnue;
  }       
  else if (p)  {
       pnue->set_ant(p->get_ant());
       p->get_ant()->set_sig(pnue);
       p->set_ant(pnue);
  } 
  else
  {
      pnue->set_ant(q);
      q->set_sig(pnue);
  }
  return 1;
}

template <class T>
int lista<T>::buscar( T &bus, Nodo<T> **q)
{
      Nodo<T> *p; int i=0;
      for (p=cab; p; p= p->get_sig(),i++)
          if ( bus==p->get_inf() )
          {
               if ( q!=NULL ) *q= p;
               bus= p->get_inf();
               return i;
          }
      return -1;
}
     
template <class T>
int lista<T>::eliminar( T &eli)
{
      Nodo<T> *p= cab;
      if ( !cab ) return -1;
      if ( buscar(eli,&p) )
      {
           if (p==cab)
           {
               cab= p->get_sig();
               if ( cab ) cab->set_ant(NULL);
           }
           else
           {
               p->get_ant()->set_sig(p->get_sig());
               if ( p->get_sig() ) 
                   p->get_sig()->set_ant( p->get_ant() );
           }
           delete p;
           return 1;
      }
      else
          return 0;

}

template <class T>
void lista<T>::imprimir ( ) 
{
      Nodo<T> *p;
      for (p=cab; p; p= p->get_sig())
         p->get_inf().Imprimir();
}

#endif
