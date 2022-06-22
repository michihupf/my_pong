AC_INIT([mypong], [1.0], [michihupf@protonmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CXX
PKG_PROG_PKG_CONFIG

## CHECK FOR MODULES
PKG_CHECK_MODULES([MY_PONG], [
    gtk+-3.0
    cairo
])

AC_CONFIG_FILES([
    Makefile
])
AC_OUTPUT
