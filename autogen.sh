#!/bin/bash
# Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
#
# Copying and distribution of this file, with or without modification, are
# permitted in any medium without royalty provided the copyright notice
# and this notice are preserved. This file is offered as-is, without any
# warranty.

mkdir -p build-aux
aclocal -I m4
libtoolize
autoconf
autoheader
automake --add-missing
