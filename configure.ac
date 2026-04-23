AC_INIT([gparted],[1.8.0-git],[https://gitlab.gnome.org/GNOME/gparted/issues])
AC_PREREQ([2.50])

AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([1.9 foreign subdir-objects])
AM_MAINTAINER_MODE

AC_ARG_ENABLE(
	[release],
	AS_HELP_STRING(
		[--enable-release],
		[enable release build flags @<:@default=disabled@:>@]),
	[enable_release=$enableval],
	[enable_release=no]
)

AM_CONDITIONAL([RELEASE_BUILD], [test "x$enable_release" = 'xyes'])


dnl======================
dnl checks for programs
dnl======================
AC_PROG_CXX
AC_PROG_CC
LT_INIT
AC_PROG_AWK
dnl Check for pkg-config early to avoid splitting message when first used.
PKG_CHECK_EXISTS


dnl======================
dnl Find graphical privilege escalation program
dnl======================
dnl Check for pkexec >= 0.102 for it's ability to run X11 apps.
AM_CONDITIONAL([INSTALL_POLKIT_ACTIONS], false)
PKEXEC_REQUIRED_VERSION='0.102'
AC_MSG_CHECKING([for pkexec >= $PKEXEC_REQUIRED_VERSION])
PKEXEC_REQUIRED_INT=`echo "$PKEXEC_REQUIRED_VERSION" | $AWK -F. '{print $1 * 10000 + $2}'`
PKEXEC_VERSION_OUTPUT=`pkexec --version 2> /dev/null` ||
	AC_MSG_RESULT([not found])
if test "x$PKEXEC_VERSION_OUTPUT" != 'x'; then
	PKEXEC_FOUND_VERSION=`echo "$PKEXEC_VERSION_OUTPUT" | head -1 | cut -d' ' -f3`
	PKEXEC_FOUND_INT=`echo "$PKEXEC_FOUND_VERSION" | $AWK -F. '{print $1 * 10000 + $2}'`
	AC_MSG_RESULT([$PKEXEC_FOUND_VERSION found])
	if test "$PKEXEC_FOUND_INT" -ge "$PKEXEC_REQUIRED_INT"; then
		GKSUPROG='pkexec --disable-internal-agent'
		AC_SUBST([GKSUPROG])
		AM_CONDITIONAL([INSTALL_POLKIT_ACTIONS], true)
	fi
fi

dnl Check for alternative graphical privilege escalation programs.
if test "x$GKSUPROG" = 'x'; then
	AC_CHECK_PROGS([GKSUPROG], [gksudo gksu kdesudo "xdg-su -c"], [])
fi


dnl======================
dnl i18n stuff
dnl======================




dnl======================
dnl checks for libs
dnl======================
AC_CHECK_LIB([uuid], [uuid_generate], [], AC_MSG_ERROR([*** libuuid not found.]))
AC_CHECK_LIB([dl], [dlopen], [], AC_MSG_ERROR([*** libdl not found.]))
AC_CHECK_LIB([parted], [ped_device_read], [], AC_MSG_ERROR([*** libparted not found.]))
AC_CHECK_LIB([parted-fs-resize], [ped_file_system_resize], [],
             AC_MSG_ERROR([*** libparted-fs-resize not found.]))


dnl Check for minimum required libparted version.
dnl 1) Check using pkg-config.
dnl    (Older distros tend to not provide pkg-config information for libparted).
dnl 2) Check by linking and running a program to report libparted version directly.
LIBPARTED_REQUIRED_VERSION='3.2'
AC_MSG_CHECKING([for libparted >= $LIBPARTED_REQUIRED_VERSION (querying pkg-config)])
LIBPARTED_REQUIRED_INT=`echo "$LIBPARTED_REQUIRED_VERSION" |
	$AWK -F. '{print $1 * 1000000 + $2 * 10000 + $3}'`
dnl 1) Check using pkg-config.
PKG_CHECK_EXISTS(
	[libparted],
	[LIBPARTED_FOUND_VERSION=`$PKG_CONFIG --modversion libparted`
	 LIBPARTED_FOUND_INT=`echo "$LIBPARTED_FOUND_VERSION" |
		$AWK -F. '{print $1 * 1000000 + $2 * 10000 + $3}'`
	 AC_MSG_RESULT([$LIBPARTED_FOUND_VERSION])
	 test "$LIBPARTED_FOUND_INT" -ge "$LIBPARTED_REQUIRED_INT" ||
		AC_MSG_ERROR([*** libparted too old.  Require libparted >= $LIBPARTED_REQUIRED_VERSION but only found libparted $LIBPARTED_FOUND_VERSION.])
	],
	[AC_MSG_RESULT([not found])
	 dnl 2) Check by linking and running a program to report libparted version
	 dnl    directly.
	 AC_MSG_CHECKING([for libparted >= $LIBPARTED_REQUIRED_VERSION (querying libparted)])
	 AC_RUN_IFELSE(
		[AC_LANG_SOURCE(
			[[
#include <stdio.h>
#include <stdlib.h>
#include <parted/parted.h>

int main()
{
	const char *version = ped_get_version();
	if (version == NULL)
	{
		fprintf(stderr, "ERROR: ped_get_version() returned NULL\n");
		return EXIT_FAILURE;
	}
	printf("%s\n", version);
	return EXIT_SUCCESS;
}
			]]
		)],
		dnl Run test program again to cache libparted version.
		[LIBPARTED_FOUND_VERSION=`./conftest$EXEEXT`
		 LIBPARTED_FOUND_INT=`echo "$LIBPARTED_FOUND_VERSION" |
			$AWK -F. '{print $1 * 1000000 + $2 * 10000 + $3}'`
		 test "$LIBPARTED_FOUND_INT" -ge "$LIBPARTED_REQUIRED_INT" ||
			AC_MSG_ERROR([*** libparted too old.  Require libparted >= $LIBPARTED_REQUIRED_VERSION but only found libparted $LIBPARTED_FOUND_VERSION.])
		],
		[AC_MSG_ERROR([*** Error querying libparted version.  Check config.log for details.])]
	)]
)


dnl gthread
PKG_CHECK_MODULES([GTHREAD], [gthread-2.0])
AC_SUBST([GTHREAD_LIBS])
AC_SUBST([GTHREAD_CFLAGS])


dnl TQt3 (Trinity)
PKG_CHECK_MODULES([TQT], [tqt])
AC_SUBST([TQT_LIBS])
AC_SUBST([TQT_CFLAGS])


dnl TDE (Trinity) headers/libs for TDEApplication
AC_PATH_PROG([TDE_CONFIG], [tde-config], [no])
if test "x$TDE_CONFIG" = xno; then
	AC_MSG_ERROR([*** tde-config not found.  Trinity development environment required.])
fi
TDE_PREFIX=`$TDE_CONFIG --prefix`
TDE_LIBSUFFIX=`$TDE_CONFIG --libsuffix 2>/dev/null`
if test "x$TDE_LIBSUFFIX" = x; then
	TDE_LIBSUFFIX=""
fi
TDE_CFLAGS="-I$TDE_PREFIX/include"
TDE_LIBS="-L$TDE_PREFIX/lib$TDE_LIBSUFFIX -ltdeio -ltdeui -ltdecore"
AC_SUBST([TDE_CFLAGS])
AC_SUBST([TDE_LIBS])


dnl Check for glibmm minimum required version.
PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 >= 2.32.0])


dnl Require C++14 compilation.
AX_CXX_COMPILE_STDCXX_14()

dnl Enable large file support (ensures off_t is 64-bit on all architectures).
AC_SYS_LARGEFILE



dnl======================
dnl check whether to use native libparted dmraid support
dnl======================
AC_ARG_ENABLE(
	[libparted_dmraid],
	AS_HELP_STRING(
		[--enable-libparted-dmraid],
		[use native libparted /dev/mapper dmraid support @<:@default=disabled@:>@]),
	[enable_libparted_dmraid=$enableval],
	[enable_libparted_dmraid=no]
)

AC_MSG_CHECKING([whether to use native libparted /dev/mapper dmraid support])
if test "x$enable_libparted_dmraid" = xyes; then
	AC_DEFINE([USE_LIBPARTED_DMRAID], [1],
	          [Define to 1 to use native libparted /dev/mapper dmraid support])
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
fi

AC_CONFIG_FILES([
Makefile
include/Makefile
src/Makefile
])

AC_OUTPUT


dnl======================
dnl Summary
dnl======================

echo ""
echo "======================== Final configuration ==========================="
echo "                         Installing into prefix  :  $prefix"
echo ""
echo "           Use native libparted dmraid support?  :  $enable_libparted_dmraid"
echo ""
echo " If all settings are OK, type make and then (as root) make install"
echo "========================================================================"
