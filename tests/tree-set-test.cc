/*
 * tree-set-test.cc - unit test for Tree Set
 *
 * Copyright (C) 2015 Paolo Rovelli
 *
 * Author: Paolo Rovelli <paolorovelli@yahoo.it>
 */

#include <string>

#include "set.h"
#include "tree-set.h"

#include <cppunit/extensions/HelperMacros.h>

#define ARRAY_SIZE(x) (int)(sizeof(x)/sizeof(x[0]))

class TreeSetTest : public CppUnit::TestFixture {

	CPPUNIT_TEST_SUITE(TreeSetTest);
	CPPUNIT_TEST(testTreeSet);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() {
	}

	void tearDown() {
	}

	void testTreeSet() {
		std::string a[] = { "Hello", "Mr.", "Paolo", "Rovelli" };
		Set<std::string> *s = new TreeSet<std::string>();

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(s->add(a[i]));
		CPPUNIT_ASSERT_EQUAL(s->size(), ARRAY_SIZE(a));

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(s->contains(a[i]));

		SetIterator<std::string> *itr = s->iterator();
		for (int i = 0; itr->hasNext(); i++)
			CPPUNIT_ASSERT_EQUAL(itr->next(), a[i]);

		for (int i = 0; i < ARRAY_SIZE(a); i++)
			CPPUNIT_ASSERT(s->remove(a[i]));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TreeSetTest);

