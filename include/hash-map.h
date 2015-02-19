/*
 * hash-map.h - example of Hash Map interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <functional>

#include "map.h"

template<typename K, typename V,
	typename H = std::hash<K>,
	typename E = std::equal_to<K>>
class HashMap;

template<typename K, typename V>
struct HashMapNode {
	int hash;
	const K *key;
	const V *value;
	HashMapNode<K,V> *next;

	HashMapNode();
	HashMapNode(int hash, const K *key, const V *value,
		HashMapNode<K,V> *node);
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
	int index;
	HashMapNode<K,V> *nextNode;
	HashMapNode<K,V> *currNode;
};

template<typename K, typename V, typename H, typename E>
class HashMap : public Map<K,V> {
public:
	HashMap();
	HashMap(int capacity);
	~HashMap();
	// query
	int size() const;
	bool isEmpty() const;
	const V* get(const K& key) const;
	// modification
	const V* put(const K& key, const V& value);
	const V* remove(const K& key);
	// iterator
	friend class HashMapIterator<K,V>;
	MapIterator<K,V>* iterator() const;
private:
	HashMapNode<K,V> **table;
	int tablelen;
	int count;
	// functors
	H hashCode;
        E equals;
};

#endif /* HASH_MAP_H */

