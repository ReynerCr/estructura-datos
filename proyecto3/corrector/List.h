//list.h
#ifndef LIST_H
#define LIST_H
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
		int delet(T &trash);
		void print();
		int getQuantity() { return quantity; }
		bool seek(T &aux);
		
		~List() { }
};

#endif

template<class T>
void List<T>::print()
{
	Node<T> *pt = header;
	while(pt != 0)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
	}
}//print()

template<class T>
int List<T>::add(T element)
{
	Node<T> *newnode = new Node<T>(element);
	if (newnode == 0) //failed to create a new element
		return 1;
		
	Node<T> *pprev, *pt;
	pt = header;
	while (pt != 0)
	{
		if (newnode->getInfo() < pt->getInfo())
			break;
			
		pprev = pt;
		pt = pt->getNext();
	}//while
	
	if (pt == header)
	{
		newnode->setNext(header);
		header = newnode;
	}
	else
	{
		pprev->setNext(newnode);
		newnode->setNext(pt);
	}
	newnode = 0;
	quantity++;
	return 0;
}//add(T)

//delete an existent element of a list
template<class T>
int List<T>::delet(T &trash)
{
	if (header != 0) {
		Node<T> *pt, *pprev;
		pt = header;
		while (pt != 0)
		{
			if (trash <= pt->getInfo()) //found
				break;
				
			pprev = pt;
			pt = pt->getNext();
		}//while

		if (pt != 0 && pt->getInfo() == trash) {
			if (pt == header)
			{
				pt = header->getNext();
				delete header;
				header = pt;
				if (header != 0)
					header->setPrev(0);
				quantity--;
			}
			else if (quantity > 0)
			{
				pprev->setNext(pt->getNext());
				
				if (pt->getNext() != 0)
					pt->getNext()->setPrev(pprev);
					
				delete pt;
				quantity--;
			}
			
			pt = pprev = 0;
			return 0; //succesfully deleted
		}//if pt!=null and founded
	}//if header is not null
	return 1; //not found or not initialized
}//delet(trash)

template<class T>
bool List<T>::seek(T &aux)
{
	if (header != 0)
	{
		Node<T> *pt, *pprev;
		pt = header;
		while (pt != 0)
		{
			if (aux <= pt->getInfo()) //found
				break;
				
			pprev = pt;
			pt = pt->getNext();
		}//while
		
		if (pt != 0 && pt->getInfo() == aux)
			return true;
	}//header != 0
	return false;
}//bool seek(T &aux)

