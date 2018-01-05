dnl Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
dnl Distributed under the terms of the GNU Affero General Public License v3

AC_DEFUN([EX_WITH_FREETYPE], [
	AC_ARG_WITH([freetype],
		[AS_HELP_STRING([--with-freetype], [support for freetype2 library, required for UI/Font handling])],
		[with_ft=$withval],
		[with_ft=check]
	)

	AS_IF([test "x$with_ft" != xno], [PKG_CHECK_MODULES([FT2], [freetype2])])
])
