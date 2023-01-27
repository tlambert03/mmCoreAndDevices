AC_PREREQ([2.69])
AC_INIT([Micro-Manager], [2])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([MMCore/MMCore.cpp])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AM_INIT_AUTOMAKE([foreign 1.11])
LT_PREREQ([2.2.6])
LT_INIT([disable-static])
AC_PROG_MKDIR_P

AC_PROG_CC([cc gcc clang])
AC_PROG_CXX([c++ g++ clang++])
AX_CXX_COMPILE_STDCXX([14], [noext])


# Testing (googletest, googlemock)
# See testing/setuptesting.sh
MM_GMOCK([$srcdir/testing/googletest], [\$(top_srcdir)/testing/googletest])
AM_CONDITIONAL([BUILD_CPP_TESTS], [test "x$have_gmock" = xyes])

# AppleHost dependencies
case $host in
   *apple-darwin*) MMCORE_APPLEHOST_LDFLAGS="-framework CoreFoundation -framework IOKit" ;;
   *) MMCORE_APPLEHOST_LDFLAGS="" ;;
esac
AC_SUBST([MMCORE_APPLEHOST_LDFLAGS])

build_mmcore=yes
AM_CONDITIONAL([BUILD_MMCORE], [test "x$build_mmcore" = xyes])


# Set the default install directories used in Makefile.am's.
MM_INSTALL_DIRS


##
## Leftover stuff (needs cleanup)
##

AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_CHECK_FUNCS([memset])
AC_CHECK_LIB(dl, dlopen)


# Install Device Adapter API library and headers
install_mmdevapi=false
# TODO reinstate this flag in some better form
#AC_ARG_ENABLE(inst-devapi,
#    [  --enable-inst-devapi    Install the Device Adapter API library and headers ],
#    [ install_mmdevapi=true ])
AM_CONDITIONAL([INSTALL_MMDEVAPI], [test x$install_mmdevapi = xtrue])


##
## Subdirectory configuration
##
AM_CONDITIONAL([BUILD_ADAPTERS], [test "x$build_adapters" = xyes])
if test "x$build_adapters" = xyes; then
   AC_CONFIG_SUBDIRS([DeviceAdapters])
fi


##
## Output generation
##

AC_CONFIG_FILES(m4_strip([
   Makefile
   MMDevice/Makefile
   MMDevice/unittest/Makefile
   MMCore/Makefile
   MMCore/unittest/Makefile
]))

AC_OUTPUT

echo ""
echo "m4_text_box([Micro-Manager configuration])"
echo ""

echo "   Build device adapters:                  yes"
echo ""


echo "Now you can build and install by typing:"
echo "    make"
echo "    make install"
echo ""