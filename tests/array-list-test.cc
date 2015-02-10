/*
 * array-list-test.cc - unit test for Array List
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include "list.h"
#include "array-list.h"

#include <cppunit/extensions/HelperMacros.h>

#define ARRAY_SIZE(x) (int)(sizeof(x)/sizeof(x[0]))

class ArrayListTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(ArrayListTest);
	CPPUNIT_TEST(testArrayList);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {
	}

	void tearDown() {
	}

	void testArrayList() {
		int a[] = { 4, 3, 2, 1 };
		List<int> *l = new ArrayList<int>();

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(l->add(a[i]));
		CPPUNIT_ASSERT_EQUAL(l->size(), ARRAY_SIZE(a));

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT_EQUAL(l->get(i), a[i]);

		ListIterator<int> *itr = l->iterator();
		for (int i = 0; itr->hasNext(); i++)
			CPPUNIT_ASSERT_EQUAL(itr->next(), a[i]);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayListTest);

