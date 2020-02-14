//DobLinkQueue.h
#ifndef DOBLINKQUEUE_H
#define DOBLINKQUEUE_H
#include <iostream>
#include "Node.h"

using namespace std;

template<class T>
class DobLinkQueue {
	private:
		Node<T> *front, *end;
		int quantity;
	public:
		DobLinkQueue() { front = end = 0; quantity = 0; }
		bool isEmpty() { return (front != 0); }
		void pushFront(T);
        void pushBack(T);
		int popFront(T &element);
    	int popBack(T &element);
        T getBack() { return (end != 0? end->getInfo() : 0 ); };
    	T getFront() { return (front != 0? front->getInfo() : 0 );	};
		void print();
		~DobLinkQueue();
};

#endif

template<typename T>
void DobLinkQueue<T>::pushFront(T data)
{
    Node<T> *newnode = new Node<T>(data);
    
    if (!front) {
        front = newnode;
        newnode->setNext(0);
        end = newnode;
    }
	else {
        front->setPrev(newnode);
        newnode->setNext(front);
        front = newnode;
    }
    newnode->setPrev(0);
    newnode = 0;
    quantity++;
}//void pushFront()

template<typename T>
void DobLinkQueue<T>::pushBack(T data)
{
    Node<T> *newnode = new Node<T> (data);

    if (!end) {
        front = newnode;
        end = newnode;
        newnode->setPrev(0);
    } else {
        end->setNext(newnode);
        newnode->setPrev(end);
        end = newnode;
    }
    newnode->setNext(0);
    newnode = 0;
    quantity++;
}//void pushBack(T)

template<class T>
int DobLinkQueue<T>::popFront(T &element)
{
    Node<T> *pt;
    pt = front;
    if(pt == 0)
        return 0;
    front = pt->getNext();
    element = pt->getInfo();
    delete pt;
    pt = 0;
    if(front == 0)
    	end = 0;
    else
    	front->setPrev(0);
    quantity--;
    return 1;
}//int popFront(T)

template<class T>
int DobLinkQueue<T>::popBack(T &element)
{
    Node<T> *pt;
    pt = end;
	if(pt == 0)
        return 0;
    end = pt->getPrev();
    element = pt->getInfo();
    delete pt;
    pt = 0;
    if (end == 0)
    	front = 0;
    else
    	end->setNext(0);
    quantity--;
	return 1;
}//int popBack(T)

template<class T>
void DobLinkQueue<T>::print()
{
	Node<T> *pt = front;
	while(pt)
	{
		cout<<pt->getInfo()<<endl;
		pt = pt->getNext();
	}
}//void print()

template<class T>
DobLinkQueue<T>::~DobLinkQueue()
{
	Node<T>*pt = front, *pt2;
	while(pt != 0)
	{
		pt2 = pt->getNext();
		delete pt;
		pt = pt2;
	}
	quantity = 0;
}//~DoblinkQueue()
