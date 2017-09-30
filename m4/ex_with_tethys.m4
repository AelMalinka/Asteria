# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_TETHYS], [
	AC_ARG_WITH([tethys],
		[AS_HELP_STRING([--with-tethys], [location to look for tethys])],
		[with_tethys=$withval],
		[with_tethys=check]
	)

	TETHYS_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_tethys" != xcheck], [AS_IF([test "x$with_tethys" != xyes], [
		LDFLAGS="-L${with_tethys}/lib"
	])])
	AC_CHECK_LIB([tethys], [main], [
			AC_SUBST([TETHYS_LIBS], ["-ltethys"])
			AC_SUBST([TETHYS_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-tethys: tethys not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	TETHYS_CPPFLAGS=
	CPPFLAGS_save="$CPPFLAGS"
	test "x$with_tethys" != xcheck && CPPFLAGS="-I${with_tethys}/include"
	AC_CHECK_HEADER([Entropy/Tethys/Exception.hh], [
			AC_SUBST([TETHYS_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-tethys: tethys not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
