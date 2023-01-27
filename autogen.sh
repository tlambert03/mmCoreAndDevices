#!/bin/sh

echo "Bootstrapping autoconf/automake build system for mmCoreAndDevices..." 1>&2

autoreconf --force --install --verbose

if [ $? -eq 0 ] # Command succeeded.
then
	echo
	echo "Bootstrapping complete! You can now run ./configure" 1>&2
else
	echo "Bootstrapping failed"
fi
