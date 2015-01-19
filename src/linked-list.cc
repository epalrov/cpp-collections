/*
 * linked-list.cc - example of Linked List implementation
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <cstdlib>

#include "list.h"
#include "linked-list.h"

/**
 * Linked list implementation. 
 *
 * All of the operations perform as could be expected for a doubly-linked
 * list. Operations that index into the list will traverse the list from
 * the beginning or the end, whichever is closer to the specified index.
 *
 * Note that this implementation is not synchronized. If multiple threads
 * access a linked list concurrently, and at least one of the threads modifies
 * the list structurally, it must be synchronized externally. This is typically
 * accomplished by synchronizing on some object that naturally encapsulates
 * the list.
 */

/**
 * Constructs an empty <tt>LinkedList</tt>
 */
template<typename E>
LinkedList<E>::LinkedList() {
	head = new LinkedListNode<E>(NULL, NULL, NULL);
	head->next = head;
	head->prev = head;
	count = 0;
}

template<typename E>
LinkedList<E>::~LinkedList() {
	LinkedListNode<E> *n;
	while (count > 0) {
		n = head->next;
		head->next = n->next;
		count--;
		delete n;
	}
	delete head;
}

/**
 * Returns the number of elements in this list.
 */
template<typename E>
int LinkedList<E>::size() const {
	return count;
}

/**
 * Returns <tt>true</tt> if this list contains no elements.
 */
template<typename E>
bool LinkedList<E>::isEmpty() const {
	return count == 0 ? true : false;
}

/**
 * Appends the specified element to the end of this list.
 */
template<typename E>
bool LinkedList<E>::add(const E& e) {
	LinkedListNode<E> *n = head;
	LinkedListNode<E> *node = new LinkedListNode<E>(&e, n, n->prev);
	n->prev->next = node;
	n->prev = node;
	count++;
	return true;
}

/**
 * Inserts the specified element at the specified position in this list.
 */
template<typename E>
void LinkedList<E>::add(int index, const E& e) {
	LinkedListNode<E> *n = head;
	if (index == count) {
		n = head;
	} else if (index >= 0 && index < count/2) {
		for (int i = 0; i <= index; i++)
			n = n->next;
	} else if (index < count && index >= count/2) {
		for (int i = count; i > index; i--)
			n = n->prev;
	} else {
		//throw new IndexOutOfBoundsException(
		//	"Index: " + index + ", Size: " + count);
	}
	LinkedListNode<E> *node = new LinkedListNode<E>(&e, n, n->prev);
	n->prev->next = node;
	n->prev = node;
	count++;
}

/**
 * Returns the element at the specified position in this list.
 */
template<typename E>
const E& LinkedList<E>::get(int index) const {
	LinkedListNode<E> *n = head;
	if (index >= 0 && index < count/2) {
		for (int i = 0; i <= index; i++)
			n = n->next;
	} else if (index < count && index >= count/2) {
		for (int i = count; i > index; i--)
			n = n->prev;
	} else {
		//throw new IndexOutOfBoundsException(
		//	"Index: " + index + ", Size: " + count);
	}
	return *(n->elem); 
}

/**
 * Replaces the element at the specified position in this list with the
 * specified element.
 */
template<typename E>
const E& LinkedList<E>::set(int index, const E& e) {
	LinkedListNode<E> *n = head;
	if (index >= 0 && index < count/2) {
		for (int i = 0; i <= index; i++)
			n = n->next;
	} else if (index < count && index >= count/2) {
		for (int i = count; i > index; i--)
			n = n->prev;
	} else {
		//throw new IndexOutOfBoundsException(
		//	"Index: " + index + ", Size: " + count);
	}
	const E& oldElem = *(n->elem);
	n->elem = &e;
	return oldElem;
}

/**
 * Removes the element at the specified position in this list.
 */
template<typename E>
const E& LinkedList<E>::remove(int index) {
	LinkedListNode<E> *n = head;
	if (index >= 0 && index < count/2) {
		for (int i = 0; i <= index; i++)
			n = n->next;
	} else if (index < count && index >= count/2) {
		for (int i = count; i > index; i--)
			n = n->prev;
	} else {
		//throw new IndexOutOfBoundsException(
		//	"Index: " + index + ", Size: " + count);
	}
	n->next->prev = n->prev;
	n->prev->next = n->next;
	count--;

	const E& oldElem = *(n->elem);
	delete n;
	return oldElem;
}

template<typename E>
ListIterator<E>& LinkedList<E>::iterator() const {
	return *(new LinkedListIterator<E>(this, 0));
}

template<typename E>
ListIterator<E>& LinkedList<E>::iterator(int index) const {
	return *(new LinkedListIterator<E>(this, index));
}

/**
 * Constructs a <tt>LinkedListIterator</tt>
 */
template<typename E>
LinkedListIterator<E>::LinkedListIterator(const LinkedList<E> *l, int index) {
	list = l;
	currNode = list->head;
	nextNode = list->head;
	nextIndex = 1;
}

template<typename E>
LinkedListIterator<E>::~LinkedListIterator() {
}

template<typename E>
bool LinkedListIterator<E>::hasNext() const {
	return nextIndex == list->count ? false : true;
}

template<typename E>
const E& LinkedListIterator<E>::next() {
	currNode = nextNode;
	nextNode = currNode->next;
	nextIndex++;
	return *(currNode->elem);
}

template<typename E>
LinkedListNode<E>::LinkedListNode(const E *e, LinkedListNode<E> *n, LinkedListNode<E> *p) {
	elem = e;
	next = n;
	prev = p;
}

template<typename E>
LinkedListNode<E>::~LinkedListNode() {
}

template class LinkedList<int>;
template class LinkedListIterator<int>;

