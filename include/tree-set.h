/*
 * tree-set.h - example of Tree Set interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef TREE_SET_H
#define TREE_SET_H

#include <functional>

#include "set.h"

template<typename E, typename C = std::less<E>>
class TreeSet;

template<typename E>
struct TreeSetNode {
	const E *elem;
	TreeSetNode<E> *parent;
	TreeSetNode<E> *left;
	TreeSetNode<E> *right;

	TreeSetNode(const E *e, TreeSetNode<E> *p);
	~TreeSetNode();
};

template<typename E>
class TreeSetIterator : public SetIterator<E> {
public:
	TreeSetIterator(const TreeSet<E> *set);
	~TreeSetIterator();
	bool hasNext() const;
	const E& next();
private:
	const TreeSet<E> *set;
	TreeSetNode<E> *nextNode;
	TreeSetNode<E> *currNode;
};

template<typename E, typename C>
class TreeSet : public Set<E> {
public:
	TreeSet();
	~TreeSet();
	// query
	int size() const;
	bool isEmpty() const;
	bool contains(const E& e) const;
	// modification
	bool add(const E& e);
	bool remove(const E& e);
	// iterator
	friend class TreeSetIterator<E>;
	SetIterator<E> *iterator() const;
private:
	int count;
	TreeSetNode<E> *root;
	// functor
	C compare;
	// internals
	TreeSetNode<E> *getFirstNode() const;
	TreeSetNode<E> *getNextNode(TreeSetNode<E> *n) const;
	void removeNode(TreeSetNode<E> *n);
};

#endif /* TREE_SET_H */

