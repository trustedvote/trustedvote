AC_INIT([trusted-vote], [0.1])
AM_INIT_AUTOMAKE([foreign no-define nostdinc subdir-objects -Wall])
AC_CONFIG_MACRO_DIRS([share/autoconf/autoconf])

AC_PROG_CXX

AX_PTHREAD

AX_BOOST_BASE([1.69])
AX_BOOST_ASIO

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/trusted-vote/Makefile
])

AC_OUTPUT
