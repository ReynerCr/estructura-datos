//DobLinkList.h
#ifndef DOBLINKLIST_H
#define DOBLINKLIST_H
#include "Node.h"

template<class T>
class DobLinkList
{
	Node<T> *header, *end;
	int quantity;
	
	public:
		DobLinkList() { header = end = 0; quantity = 0; }
		int add(T newest);
		int remove(T &trash);
		void print();
		int getQuantity() { return quantity; }
		int seek(T &element);
		bool isEmpty() { return (header != 0); }
		
		~DobLinkList(); 
};

template<class T>
void DobLinkList<T>::print()
{
	Node<T> *pt = header;
	while(pt != 0)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
	}
}//print()

template<class T>
int DobLinkList<T>::add(T element)
{
	Node<T> *pt, *newnode = new Node<T>(element);
	if (newnode == 0) //failed to create a new element, probably problems with memory
		return 0; //not added with problems
	
	if(header == 0)
	{
		header = end = newnode;
	}
	else
	{
		if(newnode->getInfo() < header->getInfo())
		{
			newnode->setNext(header);
			header->setPrev(newnode);
			header = newnode;
		}
		
		else if(newnode->getInfo() > end->getInfo())
		{
			newnode->setPrev(end);
			end->setNext(newnode);
			end = newnode;
		}
		
		else
		{
			pt = header->getNext();
			while(true)
			{
				if(pt->getInfo() > newnode->getInfo())
					break;
				pt = pt->getNext();
			}
			newnode->setPrev(pt->getPrev());
			newnode->setNext(pt);
			pt->getPrev()->setNext(newnode);
			pt->setPrev(newnode);
		}
	}
	quantity++;
	newnode = 0;
	return 1; //added
}//add(T)

//delete an existent element of a list
template<class T>
int DobLinkList<T>::remove(T &trash)
{
	if (header == 0)
		return 0; //not initialized

	Node<T> *pt;
	if (trash < header->getInfo()  || trash > end->getInfo())
		return -1;
		
	if (trash == header->getInfo())
	{
		trash = header->getInfo();
		header = header->getNext();
		if (header == 0)
		{
			delete end;
			end = 0;
		}
		else
		{
			delete header->getPrev();
			header->setPrev(0);
		}
		quantity--;
		return 1;
	}
	else if (trash == end->getInfo())
	{
		trash = end->getInfo();
		end = end->getPrev();
		delete end->getNext();
		end->setNext(0);
		quantity--;
		return 1;
	}
	else
	{
		pt = header->getNext();
		bool flag = false;
		while(pt != 0 && !flag)
		{
			if(pt->getInfo() >= trash)
				flag = true;
			else
				pt = pt->getNext();
		}
		if(flag && pt->getInfo() != trash)
			return -1;
		pt->getPrev()->setNext(pt->getNext());
		pt->getNext()->setPrev(pt->getPrev());
		trash = pt->getInfo();
		delete pt;
		pt = 0;
		quantity--;
		return 1;
	}
	
	return -1; //not found
}//remove(trash)

template<class T>
int DobLinkList<T>::seek(T &element)
{
	if (header == 0)
		return -1; //not initialized

	Node<T> *pt = header;
	while (pt != 0)
	{
		if (element <= pt->getInfo()) //for ascendant lists
			break;
			
		pt = pt->getNext();
	}//while
	
	if (pt != 0 && pt->getInfo() == element)
	{
		element = pt->getInfo();
		return 1; //found
	}
		
	return 0; //not found
}//int seek(T &element)

template<class T>
DobLinkList<T>::~DobLinkList()
{
	Node<T> *pt = header, *aux;
	while (pt != 0)
	{
		aux = pt->getNext();
		delete pt;
		pt = aux;
	}
}

#endif
