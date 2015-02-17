/*
 * hash-map.h - example of Hash Map interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "map.h"

template<typename K, typename V, typename H = int, typename E = int>
class HashMap;

template<typename K, typename V>
struct HashMapNode {
	int hash;
	const K *key;
	const V *value;
	HashMapNode<K,V> *next;

	HashMapNode();
	HashMapNode(int h, const K *k, const V *v, HashMapNode<K,V> *n);
	~HashMapNode();
};

template<typename K, typename V>
class HashMapIterator : public MapIterator<K,V> {
public:
	HashMapIterator(const HashMap<K,V> *map);
	~HashMapIterator();
	bool hasNext() const;
	const V& next();
private:
	const HashMap<K,V> *map;
	HashMapNode<K,V> *nextNode;
	HashMapNode<K,V> *currNode;
	int nextIndex;
};

template<typename K, typename V, typename H, typename E>
class HashMap : public Map<K,V,H,E> {
public:
	HashMap();
	~HashMap();
	// query
	int size() const;
	bool isEmpty() const;
	const V* get(const K& k) const;
	// modification
	const V* put(const K& k, const V& v);
	const V* remove(const K& k);
	// iterator
	friend class HashMapIterator<K,V>;
	MapIterator<K,V>* iterator() const;
private:
	HashMapNode<K,V> **array;
	int arraylen;
	int count;
	// functors
	H hashCode;
        E equals;
};

#endif /* HASH_MAP_H */

