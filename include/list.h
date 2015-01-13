/*
 * list.h - example of List interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef LIST_H
#define LIST_H

template<typename E>
class ListIterator {
public:
	virtual bool hasNext() = 0;
	virtual E& next() = 0;
};

template<typename E>
class List {
public:
	virtual int size() = 0;
	virtual bool isEmpty() = 0;
	virtual bool add(E& e) = 0;
	virtual void add(int index, E& e) = 0;
	virtual E& remove(int index) = 0;
	virtual E& set(int index, E& e) = 0;
	virtual E& get(int index) = 0;
//	virtual ListIterator<E> iterator() = 0;
//	virtual ListIterator<E> iterator(int index) = 0;
};

#endif /* LIST_H */

