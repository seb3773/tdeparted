#!/usr/bin/env bash
set -euo pipefail

PKG_NAME="tdeparted"
PKG_VERSION="1.0"
PKG_MAINTAINER="seb3773"
PKG_SECTION="admin"
PKG_PRIORITY="optional"

SRC_ROOT="$(pwd)"
ARCH="$(dpkg --print-architecture)"
BUILD_DIR="$SRC_ROOT/build"
PKGROOT="$BUILD_DIR/pkgroot"
PKGTMP="$BUILD_DIR/pkgtmp"

need_cmd() {
	command -v "$1" >/dev/null 2>&1 || {
		echo "error: missing required command: $1" >&2
		exit 1
	}
}

need_cmd sed
need_cmd make
need_cmd dpkg-deb
need_cmd dpkg-shlibdeps
need_cmd strip

mkdir -p -- "$BUILD_DIR"
rm -rf -- "$PKGTMP"
mkdir -p -- "$PKGTMP"

if test ! -x "$SRC_ROOT/configure" || test "$SRC_ROOT/configure.ac" -nt "$SRC_ROOT/configure" || test "$SRC_ROOT/Makefile.am" -nt "$SRC_ROOT/configure"; then
	./autogen.sh
fi

(
	cd "$BUILD_DIR"
	if test ! -f Makefile || test ! -f config.status || test "$SRC_ROOT/configure" -nt config.status; then
		"$SRC_ROOT/configure" --prefix=/usr --enable-release
	fi
	make clean >/dev/null 2>&1 || true
	make -j"$(nproc)"
)

BIN_PATH="$BUILD_DIR/src/tdepartedbin"

# Stage filesystem layout.
rm -rf -- "$PKGROOT"
mkdir -p -- \
	"$PKGROOT/DEBIAN" \
	"$PKGROOT/usr/bin" \
	"$PKGROOT/usr/lib/$PKG_NAME" \
	"$PKGROOT/usr/share/applications" \
	"$PKGROOT/usr/share/polkit-1/actions" \
	"$PKGROOT/usr/share/icons/hicolor"

# Generate wrapper script (tdeparted) from template without using make install.
# Substitutions mirror Makefile.am's do_subst.
WRAP_TMP="$PKGTMP/tdeparted"
sed -e 's,[@]libexecdir[@],/usr/lib/'"$PKG_NAME"',g' \
	-e 's,[@]bindir[@],/usr/bin,g' \
	-e 's,[@]gksuprog[@],pkexec --disable-internal-agent,g' \
	< "$SRC_ROOT/tdeparted.in" > "$WRAP_TMP"
chmod 0755 "$WRAP_TMP"
install -m 0755 "$WRAP_TMP" "$PKGROOT/usr/bin/tdeparted"

# Install desktop entry.
if test -f "$SRC_ROOT/tdeparted.desktop"; then
	install -m 0644 "$SRC_ROOT/tdeparted.desktop" "$PKGROOT/usr/share/applications/tdeparted.desktop"
fi

# Install binary.
install -m 0755 "$BIN_PATH" "$PKGROOT/usr/lib/$PKG_NAME/tdepartedbin"

# Generate and install polkit policy.
POLICY_TMP="$PKGTMP/org.trinity.tdeparted.policy"
sed -e 's,[@]libexecdir[@],/usr/lib/'"$PKG_NAME"',g' \
	-e 's,[@]bindir[@],/usr/bin,g' \
	-e 's,[@]gksuprog[@],pkexec --disable-internal-agent,g' \
	< "$SRC_ROOT/org.trinity.tdeparted.policy.in.in" > "$POLICY_TMP"
install -m 0644 "$POLICY_TMP" "$PKGROOT/usr/share/polkit-1/actions/org.trinity.tdeparted.policy"

# Install application icon.
# The .desktop file uses Icon=tdeparted.
ICON_SRC="$SRC_ROOT/icons/tdeparted_icon.png"
if test -f "$ICON_SRC"; then
	# Install the real file once (64x64) and symlink the other sizes to it.
	real_sz="64x64"
	real_dir="$PKGROOT/usr/share/icons/hicolor/$real_sz/apps"
	mkdir -p -- "$real_dir"
	install -m 0644 "$ICON_SRC" "$real_dir/tdeparted.png"
	for sz in 16x16 22x22 24x24 32x32 48x48; do
		dstdir="$PKGROOT/usr/share/icons/hicolor/$sz/apps"
		mkdir -p -- "$dstdir"
		ln -sf "../../$real_sz/apps/tdeparted.png" "$dstdir/tdeparted.png"
	done
else
	echo "warning: missing $ICON_SRC (application icon will not be installed)" >&2
fi

# Install Trinity handbook (DocBook).
HANDBOOK_ROOT="$SRC_ROOT/doc"
if test -d "$HANDBOOK_ROOT"; then
	for lang in en fr; do
		src_db="$HANDBOOK_ROOT/$lang/index.docbook"
		if test -f "$src_db"; then
			dest_dir="$PKGROOT/usr/share/doc/tde/HTML/$lang/$PKG_NAME"
			install -d "$dest_dir"
			install -m 0644 "$src_db" "$dest_dir/index.docbook"
			if test -d "$HANDBOOK_ROOT/$lang/figures"; then
				install -d "$dest_dir/figures"
				cp -a "$HANDBOOK_ROOT/$lang/figures/." "$dest_dir/figures/"
			fi
		fi
	done
fi

# Compute runtime dependencies from the built binary.
DEBIAN_TMP_DIR="$PKGTMP/debian"
mkdir -p -- "$DEBIAN_TMP_DIR"
cat > "$DEBIAN_TMP_DIR/control" <<EOF
Source: $PKG_NAME
Section: $PKG_SECTION
Priority: $PKG_PRIORITY
Maintainer: $PKG_MAINTAINER
Standards-Version: 4.6.0

Package: $PKG_NAME
Architecture: $ARCH
Description: tdeParted (Trinity/TQt3 partition editor)
EOF

: > "$DEBIAN_TMP_DIR/substvars"

STAGED_BIN="$PKGROOT/usr/lib/$PKG_NAME/tdepartedbin"
SHLIBS_DEPENDS=""
if test -x "$STAGED_BIN"; then
	SHLIBS_DEPENDS="$(
		(cd "$PKGTMP" && dpkg-shlibdeps -O -T "$DEBIAN_TMP_DIR/substvars" -S"$PKGROOT" -e "$STAGED_BIN" 2>/dev/null) |
		sed -n 's/^shlibs:Depends=//p'
	)" || SHLIBS_DEPENDS=""
fi

if test -z "$SHLIBS_DEPENDS"; then
	# Fallback: keep minimal hard dependency on policykit-1.
	SHLIBS_DEPENDS=""
fi

DEPENDS="$SHLIBS_DEPENDS"
if test -n "$DEPENDS"; then
	DEPENDS="$DEPENDS, policykit-1"
else
	DEPENDS="policykit-1"
fi

# Strip the staged binary after dependency extraction.
if command -v sstrip >/dev/null 2>&1; then
	echo "info: stripping with sstrip"
	sstrip "$STAGED_BIN" >/dev/null 2>&1 || true
else
	echo "info: sstrip not found, using strip --strip-all"
	strip --strip-all "$STAGED_BIN" >/dev/null 2>&1 || true
fi

# Debian control file.
INSTALLED_SIZE_KB="$(du -sk "$PKGROOT/usr" | awk '{print $1}')"
cat > "$PKGROOT/DEBIAN/control" <<EOF
Package: $PKG_NAME
Version: $PKG_VERSION
Section: $PKG_SECTION
Priority: $PKG_PRIORITY
Architecture: $ARCH
Maintainer: $PKG_MAINTAINER
Installed-Size: $INSTALLED_SIZE_KB
Depends: $DEPENDS
Description: tdeParted (Trinity/TQt3 partition editor)
 tdeParted is a Trinity Desktop (TDE) / TQt3 fork of GParted.
EOF

# postinst: refresh icon cache if available.
cat > "$PKGROOT/DEBIAN/postinst" <<'EOF'
#!/bin/sh
set -e
if command -v gtk-update-icon-cache >/dev/null 2>&1; then
	gtk-update-icon-cache -f -t /usr/share/icons/hicolor >/dev/null 2>&1 || true
fi
if command -v update-desktop-database >/dev/null 2>&1; then
	update-desktop-database -q /usr/share/applications >/dev/null 2>&1 || true
fi
exit 0
EOF
chmod 0755 "$PKGROOT/DEBIAN/postinst"

# prerm: refresh icon cache on removal (best effort).
cat > "$PKGROOT/DEBIAN/prerm" <<'EOF'
#!/bin/sh
set -e
if command -v gtk-update-icon-cache >/dev/null 2>&1; then
	gtk-update-icon-cache -f -t /usr/share/icons/hicolor >/dev/null 2>&1 || true
fi
if command -v update-desktop-database >/dev/null 2>&1; then
	update-desktop-database -q /usr/share/applications >/dev/null 2>&1 || true
fi
exit 0
EOF
chmod 0755 "$PKGROOT/DEBIAN/prerm"

OUT_DEB="$SRC_ROOT/${PKG_NAME}_${PKG_VERSION}_${ARCH}.deb"
rm -f -- "$OUT_DEB"

dpkg-deb --build "$PKGROOT" "$OUT_DEB" >/dev/null

echo "$OUT_DEB"
