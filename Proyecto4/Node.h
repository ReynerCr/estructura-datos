//Node.h
#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
	T info;
	Node<T> *next, *prev; //previous
	
	public:
		Node() { next = prev = 0; }
		Node(T &e) { next = prev = 0; info = e; }
		void setInfo(T &e) { info = e; }
		void setNext(Node<T> *pt) { next = pt; }
		void setPrev(Node<T> *pt) { prev = pt; }
		Node<T> *getPrev() { return prev; }
		Node<T> *getNext() { return next; } //al iterar entre lista cp explota?
		T getInfo() { return info; }
		
		~Node() { }
};

#endif
