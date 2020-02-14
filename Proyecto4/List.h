//list.h
#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Node.h"

template<class T>
class List
{
	Node<T> *header;
	int quantity;
	int ordered; //-1: new elements will be inserted at the beginning
				 //0: new elements will be inserted at the end
				 //1: increasing order 
	
	public:
		List(int ordered = 1) { this->ordered = ordered; quantity = 0; header = 0; }
		int add(T element);
		int remove(T &trash);
		void print();
		int getQuantity() { return quantity; }
		int seek(T &element);
		
		~List();
};

template<class T>
void List<T>::print()
{
	Node<T> *pt = header;
	while(pt != 0)
	{
		std::cout<<pt->getInfo()<<std::endl;
		pt = pt->getNext();
	}
	pt = 0;
}//print()

template<class T>
int List<T>::add(T element)
{
	Node<T> *newnode;
	newnode = new Node<T>(element);
	if (newnode == 0)
		return -1;
			
	Node<T> *pprev = 0, *pt;
	pt = header;
	
	if (ordered == 0)
	{
		while (pt != 0)
		{
			pprev = pt;
			pt = pt->getNext();
		}//while
	}//new elements at the end
	else if (ordered == 1)
	{
		while (pt != 0)
		{
			if (element < pt->getInfo())  //for ascendant lists
				break;
			pprev = pt;
			pt = pt->getNext();
			
		}//while
	}//ordered
	
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
	return 1; //added
}//add(T)

//delete an existent element of a list
template<class T>
int List<T>::remove(T &trash)
{
	if (header == 0)
		return 0; //not initialized

	Node<T> *pt, *pprev;
	pt = header;
	if (ordered == 1)
	{
		while (pt != 0)
		{
			if (trash <= pt->getInfo()) //for ascendant lists
				break;
			pprev = pt;
			pt = pt->getNext();
		}//while
	}//ordered
	else
	{
		while (pt != 0)
		{
			if (trash == pt->getInfo())
				break;
			pprev = pt;
			pt = pt->getNext();
		}//while
	}//ordered != 1

	if (pt != 0 && pt->getInfo() == trash) {
		if (pt == header)
			header = header->getNext();
		else
			pprev->setNext(pt->getNext());

		delete pt; quantity--;
		pt = pprev = 0;
		return 1; //succesfully deleted
	}//if pt!=null and founded
	
	return -1; //not found
}//remove(trash)

template<class T>
int List<T>::seek(T &element)
{
	Node<T> *pt = header, *pprev;
	
	if (pt == 0)
		return -1;
	
	int found = 0;
	pprev = pt;
	if (ordered == 1)
	{
		while (pt != 0)
		{
			if (element < pt->getInfo())
				break;
			pprev = pt;
			pt = pt->getNext();
		}//while
		if (pprev->getInfo() == element)
		{
			element = pprev->getInfo();
			found = 1;
		}
	}//ordered
	else {
		while (found == 0 && pt != 0)
		{
			if (element == pt->getInfo())
			{
				found = 1;
				element = pt->getInfo();
				break;
			}
			pt = pt->getNext();
		}//while
	}//unordered
	
	return found;
}//int seek(T &element)

template<class T>
List<T>::~List()
{
	Node<T>*aux;
	while (header != 0)
	{
		aux = header->getNext();
		delete header;
		header = aux;
	}
}

#endif

