//Queue.h
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class Queue
{
	Node<T> *front, *end;
	int quantity;
	public:
		Queue() { quantity = 0; front = end = 0; }
		int add(T newest);
		int delet(T &trash);
		void print();
		bool isVoided() { return (front != 0); }
		Node<T> getFront() { (isVoided()? 0:front); }
		
		~Queue() { }
};

template <class T>
void Queue<T>::print() {
	int i = 0;
	Node<T> *pt = front;
	while(i < quantity)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
		i++;
	}
}//print

template<class T>
int Queue<T>::add(T element)
{
	if (quantity == 0)
	{
		front = new Node<T>(element);
		front->setPrev(0);
		end = front;
		front->setNext(end);
		quantity++;
		return 1;
	}
	else
	{
		Node<T> *newestt = new Node<T>(element);
		
		newestt->setPrev(end);
		end->setNext(newestt);
		newestt->setNext(0);
		end = newestt;
		newestt = 0;
		delete newestt;
		quantity++;
		return 0;
	}
}

template<class T>
int Queue<T>::delet(T &trash)
{
	if (quantity > 0) 
	{
		Node<T> *pt = 0;
		pt = front->getNext();
		trash = front->getInfo();
		delete front;
		front = pt;
		pt = 0;
		delete pt;
		front->setNext(front->getNext());
		front->setPrev(0);
		quantity--;
		return 0;
	}
	else
		return 1;
}
