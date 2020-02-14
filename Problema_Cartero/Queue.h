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
		bool isEmpty() { return (front != 0); }
		Node<T> getFront() { (isEmpty()? 0:front); }
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
	if (newnode == 0) //failed to create a new element, probably problems with memory
		return 1; //not added with problems
	
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
	if (quantity == 0)
		return 0; //not initialized
	else
		trash = front->getInfo();
	
	Node<T> *pt = front;
	front = front->getNext();
	
	if (front == 0)
		end = 0;
		
	quantity--;
	return 1; //succesfully deleted
}//delet(T&)
