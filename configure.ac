#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT([libfall4c], [0.1-alpha], [kurapix@gmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Make sure $ACLOCAL_FLAGS are used during a rebuild.
#AC_SUBST([ACLOCAL_AMFLAGS], ["-I $ac_macro_dir \${ACLOCAL_FLAGS}"])
AC_SUBST([ACLOCAL_AMFLAGS], ["-I \${AC_CONFIG_MACRO_DIR} \${ACLOCAL_FLAGS}"])

#
AM_INIT_AUTOMAKE

# Debug
AC_ARG_ENABLE([debug],AS_HELP_STRING([--enable-debug],[Debug flags]),[enable_debug=$enableval],[enable_debug="no"])

AC_MSG_CHECKING(debug)
AC_MSG_RESULT($enable_debug)

if test "x$enable_debug" = "xyes"
then
    DEBUG_CFLAGS="-g -Wall -DDEBUG"
fi
    AC_SUBST([DEBUG_CFLAGS])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.

# libtool
# AC_DISABLE_SHARED
LT_PREREQ ([2.2.6])
LT_INIT
AC_PROG_LIBTOOL
# AC_ENABLE_SHARED
AM_PROG_CC_C_O

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
