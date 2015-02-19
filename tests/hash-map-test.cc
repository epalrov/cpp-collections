/*
 * hash-map-test.cc - unit test for Hash Map
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>

#include "map.h"
#include "hash-map.h"

#include <cppunit/extensions/HelperMacros.h>

#define ARRAY_SIZE(x) (int)(sizeof(x)/sizeof(x[0]))

class HashMapTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(HashMapTest);
	CPPUNIT_TEST(testHashMap);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {
	}

	void tearDown() {
	}

	void testHashMap() {
		std::string a[] = { "Hello", "Mr.", "Paolo", "Rovelli" };
		Map<int, std::string> *h = new HashMap<int, std::string>(3);

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(h->put(i, a[i]) == NULL);
		CPPUNIT_ASSERT_EQUAL(h->size(), ARRAY_SIZE(a));

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT_EQUAL(*(h->get(i)), a[i]);

		MapIterator<int, std::string> *itr = h->iterator();
		CPPUNIT_ASSERT(itr != NULL);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HashMapTest);

