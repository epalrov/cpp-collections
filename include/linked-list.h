/*
 * linked-list.h - example of Linked List interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template<typename E>
struct ListNode {
	E *elem;
	ListNode<E> *next;
	ListNode<E> *prev;

	ListNode(E *e, ListNode<E> *n, ListNode<E> *p);
	~ListNode();
};

template<typename E>
class LinkedListIterator : public ListIterator<E> {
public:
	LinkedListIterator(int index);
	LinkedListIterator();
	~LinkedListIterator();
	bool hasNext();
	E& next();
private:
	ListNode<E> *nextNode;
	ListNode<E> *currNode;
	int nextIndex;
};

template<typename E>
class LinkedList : public List<E> {
public:
	LinkedList();
	~LinkedList();
	int size();
	bool isEmpty();
	bool add(E& e);
	void add(int index, E& e);
	E& remove(int index);
	E& set(int index, E& e);
	E& get(int index);
	ListIterator<E> iterator();
	ListIterator<E> iterator(int index);
private:
	ListNode<E> *head;
	int count;
};

#endif /* LINKED_LIST_H */

