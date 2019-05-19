TESTS = libtrustedvote-test

lib_LTLIBRARIES = libtrustedvote.la
check_PROGRAMS = libtrustedvote-test

libtrustedvote_la_CPPFLAGS = -I$(top_srcdir)/include
libtrustedvote_la_LDFLAGS = -version-info 0:0:0
libtrustedvote_la_SOURCES = chain/param.cpp

libtrustedvote_test_CPPFLAGS = -I$(top_srcdir)/include -DBOOST_TEST_NO_MAIN -DBOOST_TEST_ALTERNATIVE_INIT_API
libtrustedvote_test_SOURCES = test.cpp
