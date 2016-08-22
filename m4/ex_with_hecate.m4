# Copyright 2016 (c) Michael Thomas (malinka) <malinka@hecate-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_HECATE], [
	AC_ARG_WITH([hecate],
		[AS_HELP_STRING([--with-hecate], [location to look for hecate])],
		[with_hecate=$withval],
		[with_hecate=check]
	)

	HECATE_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_hecate" != xcheck], [AS_IF([test "x$with_hecate" != xyes], [
		LDFLAGS="-L${with_hecate}/lib"
	])])
	AC_CHECK_LIB([hecate], [main], [
			AC_SUBST([HECATE_LIBS], ["-lhecate"])
			AC_SUBST([HECATE_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-hecate: hecate not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	HECATE_CPPFLAGS="-std=c++14"
	test "x$with_hecate" != xcheck && HECATE_CPPFLAGS="$HECATE_CPPFLAGS -I${with_hecate}/include"
	CPPFLAGS_save="$CPPFLAGS"
	CPPFLAGS="$HECATE_CPPFLAGS"
	AC_CHECK_HEADER([Entropy/Hecate/Character.hh], [
			AC_SUBST([HECATE_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-hecate: Entropy/Hecate/Character.hh not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
