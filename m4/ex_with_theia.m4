# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_THEIA], [
	AC_ARG_WITH([theia],
		[AS_HELP_STRING([--with-theia], [location to look for theia])],
		[with_theia=$withval],
		[with_theia=check]
	)

	THEIA_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_theia" != xcheck], [AS_IF([test "x$with_theia" != xyes], [
		LDFLAGS="-L${with_theia}/lib"
	])])
	AC_CHECK_LIB([theia], [main], [
			AC_SUBST([THEIA_LIBS], ["-ltheia"])
			AC_SUBST([THEIA_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-theia: theia not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	THEIA_CPPFLAGS="-std=c++14"
	test "x$with_theia" != xcheck && THEIA_CPPFLAGS="$THEIA_CPPFLAGS -I${with_theia}/include"
	CPPFLAGS_save="$CPPFLAGS"
	CPPFLAGS="$THEIA_CPPFLAGS"
	AC_CHECK_HEADERS([Entropy/Theia/Application.hh], [
			AC_SUBST([THEIA_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-theia: Entropy/Theia/Application.hh not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
