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
#include <functional>

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
 * Constructs an empty <tt>HashMap</tt>
 */
//template<typename K, typename V,
//	typename H = std::hash<K>,
//	typename E = std::equal_to<K>>
template<typename K, typename V, typename H, typename E>
HashMap<K,V,H,E>::HashMap() {
	array = new HashMapNode<K,V>*[16];
	arraylen = 16;
	count = 0;
}

template<typename K, typename V, typename H, typename E>
HashMap<K,V,H,E>::~HashMap() {
	// FIXME //
	delete [] array;
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
 * Inserts the specified element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::put(const K& k, const V& v) {
#if 0
	int hash = key == NULL ? 0 : hash_fnt(k);
	int index = key == NULL ? 0 : hash % arraylen;
	// check if the key is already contained: update the value
	for (HashMapNode<K,V,H,E> *n = array[index]; n != NULL; n = n->next) {
		if (hash == n->hash && (key == n.key ||
			(key != null && key.equals(e.key)))) {
				V oldValue = e.value;
				e.value = value;
				return oldValue;
		}
	}

	// insert the new mapping at the beginning of the list
	Entry<K,V> e = new Entry(hash, key, value, table[index]);
	table[index] = e;
	size++;
#endif
	return NULL;
}

/**
 * Returns the element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::get(const K& k) const {
	return NULL;
}

/**
 * Removes the element at the specified position in this map.
 */
template<typename K, typename V, typename H, typename E>
const V* HashMap<K,V,H,E>::remove(const K& k) {
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
	nextIndex = 1;
}

template<typename K, typename V>
HashMapIterator<K,V>::~HashMapIterator() {
}

template<typename K, typename V>
bool HashMapIterator<K,V>::hasNext() const {
	return nextIndex == map->count ? false : true;
}

template<typename K, typename V>
const V& HashMapIterator<K,V>::next() {
	nextIndex++;
	return NULL;
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
//template class HashMap<int, std::string>;
//template class HashMapIterator<int, std::string>;

