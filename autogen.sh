#!/bin/sh

set -e

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

if ! test -d "$srcdir/m4"; then
	mkdir -p "$srcdir/m4"
fi

autoreconf -fi

echo "Now run: ./configure --disable-doc && make -j\$(nproc)"

