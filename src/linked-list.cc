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
	head = new ListNode<E>(NULL, NULL, NULL);
	head->next = head;
	head->prev = head;
	count = 0;
}

template<typename E>
LinkedList<E>::~LinkedList() {
// FIXME: delete all ListNode!!
	count = 0;
}

/**
 * Returns the number of elements in this list.
 */
template<typename E>
int LinkedList<E>::size() {
	return count;
}

/**
 * Returns <tt>true</tt> if this list contains no elements.
 */
template<typename E>
bool LinkedList<E>::isEmpty() {
	return count == 0 ? true : false;
}

/**
 * Appends the specified element to the end of this list.
 */
template<typename E>
bool LinkedList<E>::add(E& e) {
	ListNode<E> *n = head;
	ListNode<E> *node = new ListNode<E>(&e, n, n->prev);
	n->prev->next = node;
	n->prev = node;
	count++;
	return true;
}

/**
 * Inserts the specified element at the specified position in this list.
 */
template<typename E>
void LinkedList<E>::add(int index, E& e) {
	ListNode<E> *n = head;
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
	ListNode<E> *node = new ListNode<E>(&e, n, n->prev);
	n->prev->next = node;
	n->prev = node;
	count++;
}

/**
 * Returns the element at the specified position in this list.
 */
template<typename E>
E& LinkedList<E>::get(int index) {
	ListNode<E> *n = head;
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
E& LinkedList<E>::set(int index, E& e) {
	ListNode<E> *n = head;
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
	E& oldElem = *(n->elem);
	n->elem = &e;
	return oldElem;
}

/**
 * Removes the element at the specified position in this list.
 */
template<typename E>
E& LinkedList<E>::remove(int index) {
	ListNode<E> *n = head;
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
// FIXME: delete the ListNode!!
	count--;
	return *(n->elem); 
}

template<typename E>
ListNode<E>::ListNode(E *e, ListNode<E> *n, ListNode<E> *p) {
	elem = e;
	next = n;
	prev = p;
}

template<typename E>
ListNode<E>::~ListNode() {
}

template class LinkedList<int>;

