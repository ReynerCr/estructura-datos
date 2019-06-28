//list.h
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class List
{
	Node<T> *header;
	int quantity;
	
	public:
		List() { quantity = 0; header = 0; }
		int add(T newest);
		//int delet(T &trash);
		void print();
	
		~List() { }
};

template<class T>
void List<T>::print()
{
	int i = 0;
	Node<T> *pt = header;
	while(i < quantity)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
		i++;
	}
}//print

template<class T>
int List<T>::add(T element)
{
	if (quantity == 0)
	{
		header = new Node<T>(element);
		header->setPrev(0);
		header->setNext(0);
		quantity++;
		return 1;
	}
	else
	{
		Node<T> *newestt = new Node<T>(element);
		Node<T> *pt = header;
		while (pt->getNext() != 0 && newestt->getInfo() > pt->getInfo())
		{
			pt = pt->getNext();
		}
		if (pt->getNext() == 0)
		{
			pt->setNext(newestt);
			newestt->setPrev(pt);
			newestt->setNext(0);
		}
		else
		{
			Node<T> *pt2 = pt;
			pt = pt->getPrev();
			pt->setNext(newestt);
			newestt->setNext(pt2);
			pt2->setPrev(newestt);
			pt = 0;
			pt2 = 0;
			delete pt2;
		}
		delete pt;
		delete newestt;
		quantity++;
		return 0;
	}
}

/* no definido ni idea de como se debe borrar aqui jeje
template<class T>
int List<T>::delet(T &trash)
{
	if (quantity > 0) {
		Node<T> *pt = top->getPrev();
		trash = top->getInfo();
		delete header;
		top = pt;
		pt = 0;
		delete pt;
		top->setNext(0);
		quantity--;
		return 0;
	}
	else
		return 1;
}
*/
