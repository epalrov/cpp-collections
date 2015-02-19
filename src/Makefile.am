ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -Wall -std=gnu++0x -I$(top_builddir)/include

lib_LTLIBRARIES = libc++-collections.la

libc___collections_la_SOURCES = array-list.cc \
                                linked-list.cc \
                                hash-map.cc
libc___collections_la_LDFLAGS = -no-undefined -version-info 1:0:0

