#!/usr/bin/env bash
set -euo pipefail

SRC_ROOT="$(pwd)"
BUILD_DIR="$SRC_ROOT/build"

CONFIGURE_ARGS=("--prefix=/usr" "--enable-release")

mkdir -p -- "$BUILD_DIR"

if test ! -x "$SRC_ROOT/configure" || test "$SRC_ROOT/configure.ac" -nt "$SRC_ROOT/configure" || test "$SRC_ROOT/Makefile.am" -nt "$SRC_ROOT/configure"; then
	./autogen.sh
fi

(
	cd "$BUILD_DIR"
	if test ! -f Makefile || test ! -f config.status || test "$SRC_ROOT/configure" -nt config.status; then
		"$SRC_ROOT/configure" "${CONFIGURE_ARGS[@]}"
	fi
	make -j"$(nproc)"
)
