# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

AC_DEFUN([EX_WITH_MNEMOSYNE], [
	AC_ARG_WITH([mnemosyne],
		[AS_HELP_STRING([--with-mnemosyne], [location to look for mnemosyne])],
		[with_mnemosyne=$withval],
		[with_mnemosyne=check]
	)

	MNEMOSYNE_LIBS=
	LDFLAGS_save="$LDFLAGS"
	AS_IF([test "x$with_mnemosyne" != xcheck], [AS_IF([test "x$with_mnemosyne" != xyes], [
		LDFLAGS="-L${with_mnemosyne}/lib"
	])])
	AC_CHECK_LIB([mnemosyne], [main], [
			AC_SUBST([MNEMOSYNE_LIBS], ["-lmnemosyne"])
			AC_SUBST([MNEMOSYNE_LDFLAGS], ["$LDFLAGS"])
		],
		AC_MSG_FAILURE(["--with-mnemosyne: mnemosyne not found"])
	)
	LDFLAGS="$LDFLAGS_save"
	MNEMOSYNE_CPPFLAGS=
	CPPFLAGS_save="$CPPFLAGS"
	test "x$with_mnemosyne" != xcheck && CPPFLAGS="-I${with_mnemosyne}/include"
	AC_CHECK_HEADER([Entropy/Aoede/Exception.hh], [
			AC_SUBST([MNEMOSYNE_CPPFLAGS], ["$CPPFLAGS"])
		],
		AC_MSG_FAILURE(["--with-mnemosyne: mnemosyne not found"])
	)
	CPPFLAGS="$CPPFLAGS_save"
])
