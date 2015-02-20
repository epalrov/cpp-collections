/*
 * array-list.cc - example of Array List implementation
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>
#include <sstream>
#include <stdexcept>

#include "list.h"
#include "array-list.h"

/**
 * Array list implementation. 
 *
 * Note that this implementation is not synchronized. If multiple threads
 * access a array list concurrently, and at least one of the threads modifies
 * the list structurally, it must be synchronized externally. This is typically
 * accomplished by synchronizing on some object that naturally encapsulates
 * the list.
 */

/**
 * Constructs an empty <tt>ArrayList</tt>
 */
template<typename E>
ArrayList<E>::ArrayList() {
	array = NULL;
	arraylen = 0;
	count = 0;
}

template<typename E>
ArrayList<E>::~ArrayList() {
	delete [] array;
}

/**
 * Returns the number of elements in this list.
 */
template<typename E>
int ArrayList<E>::size() const {
	return count;
}

/**
 * Returns <tt>true</tt> if this list contains no elements.
 */
template<typename E>
bool ArrayList<E>::isEmpty() const {
	return count == 0 ? true : false;
}

/**
 * Appends the specified element to the end of this list.
 */
template<typename E>
bool ArrayList<E>::add(const E& e) {
	arrayResize(count + 1);
	array[count] = const_cast<E*>(&e);
	count++;
	return true;
}

/**
 * Inserts the specified element at the specified position in this list.
 */
template<typename E>
void ArrayList<E>::add(int index, const E& e) {
	if (index < 0 || index > count) {
		std::stringstream s;
		s << "Index: " << index << ", Size: " << count;
		throw std::out_of_range(s.str());
	}
	arrayResize(count + 1);
	arrayInsert(index, 1);
	array[index] = const_cast<E*>(&e);
	count++;
}

/**
 * Returns the element at the specified position in this list.
 */
template<typename E>
const E& ArrayList<E>::get(int index) const {
	if (index < 0 || index > count) {
		std::stringstream s;
		s << "Index: " << index << ", Size: " << count;
		throw std::out_of_range(s.str());
	}
	return *(array[index]);
}

/**
 * Replaces the element at the specified position in this list with the
 * specified element.
 */
template<typename E>
const E& ArrayList<E>::set(int index, const E& e) {
	if (index < 0 || index > count) {
		std::stringstream s;
		s << "Index: " << index << ", Size: " << count;
		throw std::out_of_range(s.str());
	}
	const E& oldElem = *(array[index]);
	array[index] = const_cast<E*>(&e);
	return oldElem;
}

/**
 * Removes the element at the specified position in this list.
 */
template<typename E>
const E& ArrayList<E>::remove(int index) {
	if (index < 0 || index > count) {
		std::stringstream s;
		s << "Index: " << index << ", Size: " << count;
		throw std::out_of_range(s.str());
	}
	const E& oldElem = *(array[index]);
	arrayRemove(index, 1);
	arrayResize(count - 1);
	count--;
	return oldElem;
}

template<typename E>
ListIterator<E>* ArrayList<E>::iterator() const {
	return new ArrayListIterator<E>(this);
}

template<typename E>
ListIterator<E>* ArrayList<E>::iterator(int index) const {
	return new ArrayListIterator<E>(this, index);
}

/**
 * Constructs a <tt>ArrayListIterator</tt>
 */
template<typename E>
ArrayListIterator<E>::ArrayListIterator(const ArrayList<E> *l) {
	list = l;
	currIndex = 0;
	nextIndex = 0;
}

template<typename E>
ArrayListIterator<E>::ArrayListIterator(const ArrayList<E> *l, int index) {
	list = l;
	currIndex = 0;
	nextIndex = index;
}

template<typename E>
ArrayListIterator<E>::~ArrayListIterator() {
}

template<typename E>
bool ArrayListIterator<E>::hasNext() const {
	return nextIndex == list->count ? false : true;
}

template<typename E>
const E& ArrayListIterator<E>::next() {
	currIndex = nextIndex;
	nextIndex++;
	return *(list->array[currIndex]);
}

/**
 * Internals
 */
template<typename E>
void ArrayList<E>::arrayResize(int len) {
	E **a = array;
	if (arraylen != len) {
		array = new E*[len];
		for (int i = 0; i < len && i < arraylen; i++)
			array[i] = a[i];
		delete [] a;
		arraylen = len;
	}
}

template<typename E>
void ArrayList<E>::arrayInsert(int index, int len) {
	for (int i = arraylen - 1; i - len > index; i--)
		array[i] = array[i - len];
}

template<typename E>
void ArrayList<E>::arrayRemove(int index, int len) {
	for (int i = index ; i + len < arraylen; i++)
		array[i] = array[i + len];
}

template class ArrayList<int>;
template class ArrayListIterator<int>;
template class ArrayList<std::string>;
template class ArrayListIterator<std::string>;

