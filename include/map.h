/*
 * map.h - example of Map interface
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#ifndef MAP_H
#define MAP_H

template<typename K, typename V>
class MapIterator {
public:
	virtual ~MapIterator() = 0;
	virtual bool hasNext() const = 0;
	virtual const V& next() = 0;
};

template<typename K, typename V>
inline MapIterator<K,V>::~MapIterator() { }

template<typename K, typename V>
class Map {
public:
	virtual ~Map() = 0;
	virtual int size() const = 0;
	virtual bool isEmpty() const = 0;
	virtual const V* get(const K& k) const = 0;
	virtual const V* put(const K& k, const V& v) = 0;
	virtual const V* remove(const K& k) = 0;
	virtual MapIterator<K,V>* iterator() const = 0;
};

template<typename K, typename V>
inline Map<K,V>::~Map() { };

#endif /* MAP_H */

