# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_AOEDE], [
	AC_ARG_WITH([aoede],
		[AS_HELP_STRING([--with-aoede], [location to look for aoede])],
		[with_aoede=$withval],
		[with_aoede=check]
	)

	AOEDE_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_aoede" != xcheck], [AS_IF([test "x$with_aoede" != xyes], [
		LDFLAGS="-L${with_aoede}/lib"
	])])
	AC_CHECK_LIB([aoede], [main], [
			AC_SUBST([AOEDE_LIBS], ["-laoede"])
			AC_SUBST([AOEDE_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-aoede: aoede not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	AOEDE_CPPFLAGS=
	CPPFLAGS_save="$CPPFLAGS"
	test "x$with_aoede" != xcheck && CPPFLAGS="-I${with_aoede}/include"
	AC_CHECK_HEADER([Entropy/Aoede/Exception.hh], [
			AC_SUBST([AOEDE_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-aoede: aoede not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
