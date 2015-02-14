/*
 * array-list-test.cc - unit test for Array List
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>

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
		std::string a[] = { "Hello", "Mr.", "Paolo", "Rovelli" };
		List<std::string> *l = new ArrayList<std::string>();

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(l->add(a[i]));
		CPPUNIT_ASSERT_EQUAL(l->size(), ARRAY_SIZE(a));

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT_EQUAL(l->get(i), a[i]);

		ListIterator<std::string> *itr = l->iterator();
		for (int i = 0; itr->hasNext(); i++)
			CPPUNIT_ASSERT_EQUAL(itr->next(), a[i]);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ArrayListTest);

