/*
 * tree-set.cc - example of Tree Set implementation
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>
#include <sstream>
#include <stdexcept>

#include "set.h"
#include "tree-set.h"

/**
 * Unbalanced tree implementation. 
 *
 * All of the operations perform as could be expected for an unbalanced binary
 * tree. Balancing as a Red-Black binary tree is strightforward.
 *
 * Note that this implementation is not synchronized. If multiple threads
 * access a tree set concurrently, and at least one of the threads modifies
 * the set structurally, it must be synchronized externally. This is typically
 * accomplished by synchronizing on some object that naturally encapsulates
 * the set.
 */

/**
 * Constructs an empty <tt>TreeSet</tt>
 */
template<typename E, typename C>
TreeSet<E,C>::TreeSet() {
	root = NULL;
	count = 0;
}

template<typename E, typename C>
TreeSet<E,C>::~TreeSet() {
	while (root)
		removeNode(root);
}

/**
 * Returns the number of elements in this set.
 */
template<typename E, typename C>
int TreeSet<E,C>::size() const {
	return count;
}

/**
 * Returns <tt>true</tt> if this set contains no elements.
 */
template<typename E, typename C>
bool TreeSet<E,C>::isEmpty() const {
	return count == 0 ? true : false;
}

/**
 * Appends the specified element to the end of this set.
 */
template<typename E, typename C>
bool TreeSet<E,C>::add(const E& e) {
	TreeSetNode<E> *n = root;
	TreeSetNode<E> *parent = NULL;

	// add the new element to an empty set
	if (n == NULL) {
		root = new TreeSetNode<E>(&e, NULL);
		count++;
		return true;
	}

	while (n != NULL) {
		parent = n;
		if (compare(e, *(n->elem)))
			n = n->left;
		else if (compare(*(n->elem), e))
			n = n->right;
		else // already in the set
			return false;
	}
	
	// add the new entry as leaf of the current parent position
	n = new TreeSetNode<E>(&e, parent);
	if (compare(e, *(parent->elem)))
		parent->left = n;
	else
		parent->right = n;
	count++;
	return true;
}

/**
 * Returns <tt>true</tt> if this set contains the element.
 */
template<typename E, typename C>
bool TreeSet<E,C>::contains(const E& e) const {
	TreeSetNode<E> *n = root;

	while (n != NULL) {
		if (compare(e, *(n->elem)))
			n = n->left;
		else if (compare(*(n->elem), e))
			n = n->right;
		else // found!
			return true;
	}
	return false;
}

/**
 * Removes the specified element from this set.
 */
template<typename E, typename C>
bool TreeSet<E,C>::remove(const E& e) {
	TreeSetNode<E> *n = root;

	while (n != NULL) {
		if (compare(e, *(n->elem))) {
			n = n->left;
		} else if (compare(*(n->elem), e)) {
			n = n->right;
		} else { // found, remove it!
			removeNode(n);
			return true;
		}
	}
	return false;
}

template<typename E, typename C>
SetIterator<E>* TreeSet<E,C>::iterator() const {
	return new TreeSetIterator<E>(this);
}

/**
 * Constructs a <tt>TreeSetIterator</tt>
 */
template<typename E>
TreeSetIterator<E>::TreeSetIterator(const TreeSet<E> *s) {
	set = s;
	currNode = NULL;
	nextNode = set->getFirstNode();
}

template<typename E>
TreeSetIterator<E>::~TreeSetIterator() {
}

template<typename E>
bool TreeSetIterator<E>::hasNext() const {
	return nextNode == NULL ? false : true;
}

template<typename E>
const E& TreeSetIterator<E>::next() {
	currNode = nextNode;
	nextNode = set->getNextNode(currNode);
	return *(currNode->elem);
}

/**
 * Constructs a <tt>TreeSetNode</tt>
 */
template<typename E>
TreeSetNode<E>::TreeSetNode(const E *e, TreeSetNode<E> *p) {
	elem = e;
	parent = p;
	left = NULL;
	right = NULL;
}

template<typename E>
TreeSetNode<E>::~TreeSetNode() {
}

/**
 * Internals
 */
template<typename E, typename C>
TreeSetNode<E>* TreeSet<E,C>::getFirstNode() const {
	TreeSetNode<E> *n = root;
	while (n != NULL && n->left != NULL)
		n = n->left;
	return n;
}

template<typename E, typename C>
TreeSetNode<E>* TreeSet<E,C>::getNextNode(TreeSetNode<E> *n) const {
	if (n == NULL)
		return n;

	if (n->right) {
		n = n->right;
		while (n != NULL && n->left != NULL)
			n = n->left;
	} else {
		TreeSetNode<E> *c = n;
		n = n->parent;
		while (n != NULL && c == n->right) {
			c = n;
			n = n->parent;
		}
	}
	return n;
}

template<typename E, typename C>
void TreeSet<E,C>::removeNode(TreeSetNode<E> *n) {
	if (n == NULL)
		return;

	// Node with two children:
	// - replace the specified node with its successor by copying.
	// - note that a successor always exixts!
	// - note also that the replacement alghoritm continue!
	if (n->left != NULL && n->right != NULL) {
		TreeSetNode<E> *nn = getNextNode(n);
		n->elem = nn->elem;
		n = nn;
	}

	// Node with one child or no children
	TreeSetNode<E> *c = (n->left != NULL ? n->left : n->right);
	if (c != NULL)
		c->parent = n->parent;
	if (n->parent == NULL)
		root = c;
	else if (n == n->parent->left)
		n->parent->left = c;
	else
		n->parent->right = c;

	// Finally delete the node
	delete n;
}

template class TreeSet<int>;
template class TreeSetIterator<int>;
template class TreeSet<std::string>;
template class TreeSetIterator<std::string>;

