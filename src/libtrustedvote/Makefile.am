TESTS = libtrustedvote-test

lib_LTLIBRARIES = libtrustedvote.la
check_PROGRAMS = libtrustedvote-test

# libtrustedvote.la

libtrustedvote_la_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CPPFLAGS)
libtrustedvote_la_LDFLAGS = -version-info 0:0:0 $(BOOST_LDFLAGS)
libtrustedvote_la_SOURCES = \
	config.cpp

# libtrustedvote-test

libtrustedvote_test_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-DBOOST_TEST_DYN_LINK \
	$(BOOST_CPPFLAGS)

libtrustedvote_test_LDFLAGS = $(BOOST_LDFLAGS)

libtrustedvote_test_LDADD = \
	libtrustedvote.la \
	-lstdc++fs \
	$(BOOST_UNIT_TEST_FRAMEWORK_LIB)

libtrustedvote_test_SOURCES = \
	config.test.cpp \
	test-main.cpp
