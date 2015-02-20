/*
 * set.h - example of Set interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef SET_H
#define SET_H

template<typename E>
class SetIterator {
public:
	virtual ~SetIterator() = 0;
	virtual bool hasNext() const = 0;
	virtual const E& next() = 0;
};

template<typename E>
inline SetIterator<E>::~SetIterator() { }

template<typename E>
class Set {
public:
	virtual ~Set() = 0;
	virtual int size() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const E& e) = 0;
	virtual bool remove(const E& e) = 0;
	virtual bool contains(const E& e) const = 0;
	virtual SetIterator<E>* iterator() const = 0;
};

template<typename E>
inline Set<E>::~Set() { };

#endif /* SET_H */

