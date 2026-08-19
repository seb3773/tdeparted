#!/usr/bin/env bash
set -euo pipefail

# Clean working tree for source upload (no build artifacts).
# Keeps any generated Debian packages at the repository root (tdeparted_*.deb).

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$ROOT_DIR"

rm -rf -- \
	build \
	doc/build \
	autom4te.cache

rm -f -- \
	aclocal.m4 \
	configure \
	config.h.in \
	config.h.in~ \
	config.rpath \
	Makefile.in

rm -f -- \
	include/Makefile.in \
	src/Makefile.in

rm -rf -- \
	build-aux

find src -maxdepth 1 -type f -name '*_png.inc' -delete

exit 0
