//Stack.h
#include <iostream>
#include "Node.h"
#ifndef STACK_H
#define STACK_H

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
		int getQuantity() { return quantity; }
		bool isEmpty() { return (top != 0); }
		
		~Stack() { }
};

#endif

template<class T>
void Stack<T>::print()
{
	Node<T> *pt = top;
	while (pt != 0 && pt->getPrev() != 0) {
		pt = pt->getPrev();
	}
	while(pt != 0)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
	} 
}//print()

template<class T>
int Stack<T>::add(T element)
{
	Node<T> *newnode = new Node<T>(element);
	if (newnode == 0) //failed to create a new element, probably problems with memory
		return -1; //not added with problems
	
	newnode->setNext(top);
	top = newnode;
	newnode = 0;
	quantity++;
	return 1; //added
}//add(T)

template<class T>
int Stack<T>::delet(T &trash)
{
	if (quantity == 0)
		return 0; //not initialized
	else
		trash = top->getInfo();
	
	Node<T> *pt = top;
	top = top->getNext();
	quantity--;
	return 1; //succesfully deleted
}//delet(T&)
