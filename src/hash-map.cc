/*
 * hash-map.cc - example of Hash Map implementation
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>
#include <sstream>
#include <stdexcept>

#include "map.h"
#include "hash-map.h"

/**
 * Hash map implementation. 
 *
 * Note that this implementation is not synchronized. If multiple threads
 * access a hash map concurrently, and at least one of the threads modifies
 * the map structurally, it must be synchronized externally. This is typically
 * accomplished by synchronizing on some object that naturally encapsulates
 * the map.
 */

/**
 * Constructs an empty <tt>HashMap</tt> with the default capacity (16).
 */
template<typename K, typename V, typename H, typename E>
HashMap<K,V,H,E>::HashMap() {
	tablelen = 16;
	table = new HashMapNode<K,V>*[tablelen];
	for (int i = 0; i < tablelen; i++)
		table[i] = NULL;
	count = 0;
}

/**
 * Constructs an empty <tt>HashMap</tt> with the specified capacity.
 */
template<typename K, typename V, typename H, typename E>
HashMap<K,V,H,E>::HashMap(int capacity) {
	if (capacity <= 0) {
		std::stringstream s;
		s << "Illegal capacity: " << capacity;
		throw std::invalid_argument(s.str());
	}
	tablelen = capacity;
	table = new HashMapNode<K,V>*[tablelen];
	for (int i = 0; i < tablelen; i++)
		table[i] = NULL;
	count = 0;
}

/**
 * Destructs the <tt>HashMap</tt>.
 */
template<typename K, typename V, typename H, typename E>
HashMap<K,V,H,E>::~HashMap() {
	for (int index = 0; index < tablelen; index++) {
		while (table[index] != NULL) {
			HashMapNode<K,V> *n = table[index];
			table[index] = n->next;
			delete n;
		}
	}
	delete [] table;
}

/**
 * Returns the number of elements in this map.
 */
template<typename K, typename V, typename H, typename E>
int HashMap<K,V,H,E>::size() const {
	return count;
}

/**
 * Returns <tt>true</tt> if this map contains no elements.
 */
template<typename K, typename V, typename H, typename E>
bool HashMap<K,V,H,E>::isEmpty() const {
	return count == 0 ? true : false;
}

/**
 * Returns the element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::get(const K& key) const {
	int hash = hashCode(key);
	int index = hash % tablelen;

	// search for the specified key
	for (HashMapNode<K,V> *n = table[index]; n != NULL; n = n->next) {
		if (hash == n->hash && equals(key, *(n->key))) {
			return n->value;
		}
	}
	return NULL;
}

/**
 * Inserts the specified element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::put(const K& key, const V& value) {
	int hash = hashCode(key);
	int index = hash % tablelen;

	// check if the key is already contained: update the value
	for (HashMapNode<K,V> *n = table[index]; n != NULL; n = n->next) {
		if (hash == n->hash && equals(key, *(n->key))) {
			const V *oldValue = n->value;
			n->value = &value;
			return oldValue;
		}
	}

	// insert the new mapping at the beginning of the list
	HashMapNode<K,V> *n = new HashMapNode<K,V>(hash, &key, &value,
		table[index]);
	table[index] = n;
	count++;
	return NULL;
}

/**
 * Removes the element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::remove(const K& key) {
	int hash = hashCode(key);
	int index = hash % tablelen;

	// search for the specified key
	HashMapNode<K,V> *p = table[index];
	for (HashMapNode<K,V> *n = table[index]; n != NULL; n = n->next) {
		if (hash == n->hash && equals(key, *(n->key))) {
			if (p == n)
				table[index] = n->next;
			else
				p->next = n->next;
			count--;
			const V *oldValue = n->value;
			delete n;
			return oldValue;
		}
		p = n;
	}
	return NULL;
}

/**
 * Returns a new <tt>MapIterator</tt>
 */
template<typename K, typename V, typename H, typename E>
MapIterator<K,V>* HashMap<K,V,H,E>::iterator() const {
	return new HashMapIterator<K,V>(this);
}

/**
 * Constructs a <tt>HashMapIterator</tt>
 */
template<typename K, typename V>
HashMapIterator<K,V>::HashMapIterator(const HashMap<K,V> *m) {
	map = m;
	index = 0;
	currNode = NULL;
	nextNode = NULL;
	for ( ; index < map->tablelen; index++) {
		if (map->table[index] != NULL) {
			nextNode = map->table[index];
			break;
		}
	}
}

template<typename K, typename V>
HashMapIterator<K,V>::~HashMapIterator() {
}

template<typename K, typename V>
bool HashMapIterator<K,V>::hasNext() const {
	return nextNode != NULL ? true : false;
}

template<typename K, typename V>
const V& HashMapIterator<K,V>::next() {
	currNode = nextNode;
	if (nextNode->next != NULL) {
		nextNode = nextNode->next;
	} else {
		nextNode = NULL;
		for ( ; index < map->tablelen; index++) {
			if (map->table[index] != NULL) {
				nextNode = map->table[index];
				//break;
			}
		}
	}
	return *(currNode->value);
}

/**
 * Constructs a <tt>HashMapNode</tt>
 */
template<typename K, typename V>
HashMapNode<K,V>::HashMapNode() : hash(0), key(NULL), value(NULL), next(NULL) {
}

template<typename K, typename V>
HashMapNode<K,V>::HashMapNode(int h, const K *k, const V *v, HashMapNode<K,V> *n) {
	hash = h;
	key = k;
	value = v;
	next = n;
}

template<typename K, typename V>
HashMapNode<K,V>::~HashMapNode() {
}

template class HashMap<int, int>;
template class HashMapIterator<int, int>;
template class HashMap<int, std::string>;
template class HashMapIterator<int, std::string>;

