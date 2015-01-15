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
	const E *elem;
	ListNode<E> *next;
	ListNode<E> *prev;

	ListNode(const E *e, ListNode<E> *n, ListNode<E> *p);
	~ListNode();
};

template<typename E>
class LinkedListIterator : public ListIterator<E> {
public:
	LinkedListIterator(int index);
	LinkedListIterator();
	~LinkedListIterator();
	bool hasNext() const;
	const E& next() const;
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
	int size() const;
	bool isEmpty() const;
	bool add(const E& e);
	void add(int index, const E& e);
	const E& remove(int index);
	const E& set(int index, const E& e);
	const E& get(int index) const;
	ListIterator<E> iterator() const;
	ListIterator<E> iterator(int index) const;
private:
	ListNode<E> *head;
	int count;
};

#endif /* LINKED_LIST_H */

