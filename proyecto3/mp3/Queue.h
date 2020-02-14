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
		int getQuantity() { return quantity; }
		
		~Queue() { }
};

template <class T>
void Queue<T>::print() {
	Node<T> *pt = front;
	while(pt != 0)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
	}
}//print()

template<class T>
int Queue<T>::add(T element)
{
	Node<T> *newnode = new Node<T>(element);
	if (newnode == 0) //failed to create a new element
		return 1;
	
	if (front == 0 && end == 0)
		front = end = newnode;
		
	else
	{
		end->setNext(newnode);
		end = newnode;
	}
	newnode = 0;
	quantity++;	
	return 0;
}//add(T)

template<class T>
int Queue<T>::delet(T &trash)
{
	if (front != 0) 
	{
		Node<T> *pt = front->getNext();
		trash = front->getInfo();
		delete front;
		front = pt;
		pt = 0;
		if (front != 0)
		{
			front->setNext(front->getNext());
			front->setPrev(0);
		}
		quantity--;
		return 0;
	}
	else
		return 1;
}//delet(T&)
