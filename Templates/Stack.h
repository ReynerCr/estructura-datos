//Stack.h
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class Stack
{
	Node<T> *top;
	int quantity;
	
	public:
		Stack() { quantity = 0; top = 0; }
		int add(T newest);
		int delet(T &trash);
		void print();
	
		~Stack() { }
};

template<class T>
void Stack<T>::print()
{
	int i = 0;
	Node<T> *pt = top;
	while (pt->getPrev() != 0) {
		pt = pt->getPrev();
	}
	while(i < quantity)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
		i++;
	} 
}//print

template<class T>
int Stack<T>::add(T element)
{
	
	if (quantity == 0)
	{
		top = new Node<T>(element);
		top->setPrev(0);
		quantity++;
		return 1;
	}
	else
	{
		Node<T> *newestt = new Node<T>(element);
		newestt->setPrev(top);
		top->setNext(newestt);
		newestt->setNext(0);
		top = newestt;
		newestt = 0;
		delete newestt;
		quantity++;
		return 0;
	}
	
	return 0;
}

template<class T>
int Stack<T>::delet(T &trash)
{
	if (quantity > 0) {
		Node<T> *pt = top->getPrev();
		trash = top->getInfo();
		delete top;
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
