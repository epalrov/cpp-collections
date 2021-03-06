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
	virtual ~ListIterator() = 0;
	virtual bool hasNext() const = 0;
	virtual const E& next() = 0;
};

template<typename E>
inline ListIterator<E>::~ListIterator() { }

template<typename E>
class List {
public:
	virtual ~List() = 0;
	virtual int size() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const E& e) = 0;
	virtual void add(int index, const E& e) = 0;
	virtual const E& remove(int index) = 0;
	virtual const E& set(int index, const E& e) = 0;
	virtual const E& get(int index) const = 0;
	virtual ListIterator<E>* iterator() const = 0;
	virtual ListIterator<E>* iterator(int index) const = 0;
};

template<typename E>
inline List<E>::~List() { };

#endif /* LIST_H */

