AC_INIT([trusted-vote], [0.1])
AM_INIT_AUTOMAKE([foreign no-define nostdinc subdir-objects -Wall])

AC_CONFIG_MACRO_DIRS([share/autoconf/autoconf])

AC_PROG_CXX
AM_PROG_AR

LT_INIT

AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

AX_PTHREAD

AX_BOOST_BASE([1.67])
AX_BOOST_ASIO
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_UNIT_TEST_FRAMEWORK

AC_CONFIG_FILES([
	Makefile
	include/Makefile
	src/Makefile
])

AC_OUTPUT
