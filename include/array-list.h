/*
 * array-list.h - example of Array List interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename E>
class ArrayList;

template<typename E>
class ArrayListIterator : public ListIterator<E> {
public:
	ArrayListIterator(const ArrayList<E> *list);
	ArrayListIterator(const ArrayList<E> *list, int index);
	~ArrayListIterator();
	bool hasNext() const;
	const E& next();
private:
	const ArrayList<E> *list;
	int nextIndex;
	int currIndex;
};

template<typename E>
class ArrayList : public List<E> {
public:
	ArrayList();
	~ArrayList();
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
	friend class ArrayListIterator<E>;
	ListIterator<E>* iterator() const;
	ListIterator<E>* iterator(int index) const;
private:
	int count;
	E **array;
	int arraylen;
	void arrayResize(int len);
	void arrayInsert(int index, int len);
	void arrayRemove(int index, int len);
};

#endif /* ARRAY_LIST_H */

