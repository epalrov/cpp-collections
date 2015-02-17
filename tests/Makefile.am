ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -Wall -std=gnu++0x -I$(top_builddir)/include $(CPPUNIT_CFLAGS)

TESTS = testc++-collections
bin_PROGRAMS = testc++-collections

testc___collections_SOURCES  = collections-test.cc \
                               linked-list-test.cc \
                               array-list-test.cc
testc___collections_LDADD = $(top_builddir)/src/libc++-collections.la \
                            $(CPPUNIT_LIBS)

