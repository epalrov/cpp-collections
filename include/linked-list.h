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
struct LinkedListNode {
	const E *elem;
	LinkedListNode<E> *next;
	LinkedListNode<E> *prev;

	LinkedListNode(const E *e, LinkedListNode<E> *n, LinkedListNode<E> *p);
	~LinkedListNode();
};

template<typename E>
class LinkedList;

template<typename E>
class LinkedListIterator : public ListIterator<E> {
public:
	LinkedListIterator(const LinkedList<E> *list);
	LinkedListIterator(const LinkedList<E> *list, int index);
	~LinkedListIterator();
	bool hasNext() const;
	const E& next();
private:
	const LinkedList<E> *list;
	LinkedListNode<E> *nextNode;
	LinkedListNode<E> *currNode;
	int nextIndex;
};

template<typename E>
class LinkedList : public List<E> {
public:
	LinkedList();
	~LinkedList();
	// query
	int size() const;
	bool isEmpty() const;
	const E& get(int index) const;
	// modification
	bool add(const E& e);
	void add(int index, const E& e);
	const E& remove(int index);
	const E& set(int index, const E& e);
	// iterator
	friend class LinkedListIterator<E>;
	ListIterator<E>& iterator() const;
	ListIterator<E>& iterator(int index) const;
private:
	LinkedListNode<E> *head;
	int count;
};

#endif /* LINKED_LIST_H */

