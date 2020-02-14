//CircDobList.h
#ifndef CIRCDOBLIST_H
#define CIRCDOBLIST_H
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class CircDobList
{
	Node<T> *header, *pt; //pt is the last node visited
	int quantity;
	int ordered; //-1: new elements will be inserted at the beginning
				 //0: new elements will be inserted at the end
				 //1: increasing order 
	
	public:
		CircDobList(int ordered = 1) { header = pt = 0; quantity = 0; this->ordered = ordered; }
		int add(T &newest);
		int remove(T &trash);
		void print(bool flag = true); //true: forward || false: backward
		void reset() { pt = header; }
		void move(int pos); //positive: forward || negative: backward
		T getCurrent() { return pt->getInfo(); }
		void setCurrent(T &value) { pt->setInfo(value);  }
		int getQuantity() { return quantity; }
		int seek(T &element);
		bool isEmpty() { return (header == 0); }
		void eraseData()
		{
			reset();
			Node<T>*aux;
			if (pt != 0)
			{
				header->getPrev()->setNext(0);
				header = 0;
				do
				{
					aux = pt->getNext();
					delete pt;
					pt = aux;
				}while (pt != 0);
				header = 0; pt = 0;
			}
			//llego hasta header, aunque ya no tenga valor si apunta a algo indefinida; por no hasta que pt != 0
		}
		
		~CircDobList();
};

template<class T>
void CircDobList<T>::print(bool flag)
{
	if (header == 0)
		return ;
	
	Node<T>*end;
	end = pt;
	if (flag) //forward
	{
		do
		{
			cout<<pt->getInfo();
			pt = pt->getNext();
		} while(end != pt);
	}
	if (!flag) //backward
	{
		do
		{
			cout<<pt->getInfo();
			pt = pt->getPrev();
		} while(end != pt);
	}

	end = 0;
}//print()

template<class T>
void CircDobList<T>::move(int pos)
{ //se puede optimizar calculando el elemento de la posicion final
	int posAux = pos;
	if (pos < 0)
		posAux = pos*(-1);
	
	for (int i = 0; i < posAux; i++)
	{
		pt = (pos > 0? pt->getNext() : pt->getPrev());
	}//for
}

template<class T>
int CircDobList<T>::add(T &element)
{
	Node<T> *newnode = new Node<T>(element);
	if (newnode == 0) //failed to create a new element, probably problems with memory
		return 0; //not added with problems
	
	if(header == 0)
	{
		newnode->setNext(newnode);
		newnode->setPrev(newnode);
		header = newnode;
	}//if
	else {
		reset();
		if (ordered == 1)
		{
			do
			{
				if (pt->getInfo() > element )
					break;
				pt = pt->getNext();
			}while(pt != header);
		}//if
		
		newnode->setNext(pt);
		newnode->setPrev(pt->getPrev());
		pt->getPrev()->setNext(newnode);
		pt->setPrev(newnode);
		if (ordered == -1 || (ordered == 1 && element < header->getInfo()))
			header = newnode;
	}//else
	quantity++;
	newnode = 0;
	reset();	
	return 1; //added
}//add(T)

//delete an existent element of a list
template<class T>
int CircDobList<T>::remove(T &trash)
{
	if (header == 0)
		return 0; //not initialized
	
	if (ordered == 1 && trash > header->getPrev()->getInfo()) //element not exist in the list
		return -1;
		
	reset();
	if (ordered == 1)
	{
		do
		{
			if (pt->getInfo() >= trash)
				break;
			pt = pt->getNext();
		} while(pt != header);
	}
	else
	{
		do 
		{
			if (trash == pt->getInfo())
				break;
			pt = pt->getNext();
		} while(pt != header);
	}
	
	if(pt->getInfo() != trash) //not found
		return -1;
		
	pt->getPrev()->setNext(pt->getNext());
	pt->getNext()->setPrev(pt->getPrev());
	trash = pt->getInfo();
	
	if (header->getNext() == header)
		header = 0;
	else if (pt == header)
		header = pt->getNext();

	delete pt;
	reset();

	quantity--;
	return 1;
}//remove(trash)

template<class T>
int CircDobList<T>::seek(T &element)
{
	if (pt == 0)
		return -1;
		
	int found = 0;
	reset();
	if (ordered == 1)
	{
		if (pt->getPrev()->getInfo() < element)
			return 0;
		do
		{
			if (element < pt->getInfo())
				break;
			pt = pt->getNext();
		}while(pt != header);
		if (pt->getPrev()->getInfo() == element)
		{
			element = pt->getPrev()->getInfo();
			found = 1;
		}
	}//ordered
	else {
		do
		{
			if (element == pt->getInfo())
			{
				found = 1;
				element = pt->getInfo();
				break;
			}
			pt = pt->getNext();
		}while(found == 0 && pt != header);
	}//unordered
	
	return found;
}//int seek(T &element)

template<class T>
CircDobList<T>::~CircDobList()
{
	eraseData();
}

#endif