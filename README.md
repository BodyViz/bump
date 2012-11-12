bump
====

Bump is a C++ library designed to help make the common things easier. It
is built ontop of Boost to help with some backend heavy lifting.

For information about the project, updates, and in-depth documentation
about compiling and running the examples, please refer to the Bump wiki
on Github:

	https://github.com/cnoon/bump

The rest of this document is broken down as follows:

	1. A short tutorial of how to build Bump
	2. An overview of how to use Bump

Christian Noon
Project Lead
November 7th, 2012

--

Section 1. How to build Bump
==========================================================================

Bump uses the CMake build system to make cross-platform compiling as
easy as possible for users. The CMakeLists.txt files you will find in
most of the Bump directories contain specific information for compiling
on many different platforms.

If you don't already have CMake install on your system, you can download
it from:

	http://www.cmake.org

Please note that to compile Bump, you must have CMake 2.8.0 or greater
installed. Otherwise certain portions of the CMakeLists.txt files are not
supported.

For generating an "in-source" build, you can use the configure script
provided in the Bump installation directory. This runs the cmake command
line tool provided by the CMake installation. The configure script is
very short running the command "cmake . -DCMAKE_BUILD_TYPE=Release" to
ensure you get the best performance and smallest size for your Bump
libraries and example applications.

	cd bump
	./configure
	if Unix
		make
		sudo make install
	if Mac with Xcode
		Open the bump.xcodeproj file with Xcode
		Switch the build to "install"
		Build
	if Windows with Visual Studio
		Open the ALL_BUILD.vcproj file with Visual Studio
		Go to Build->Batch Build
		Check INSTALL
		Hit the Build button

For generating an "out-of-source" build, you can still use the configure
script, but first need to make an out-of-source build directory. This
is useful for keeping all the CMake build system files out of the
original Bump library source.

	cd bump
	mkdir build.myOS
	cd build.myOS
	../configure
	if Unix
		make
		sudo make install
	if Mac with Xcode
		Open the bump.xcodeproj file with Xcode
		Switch the build to "install"
		Build
	if Windows with Visual Studio
		Open the ALL_BUILD.vcproj file with Visual Studio
		Go to Build->Batch Build
		Check INSTALL
		Hit the Build button

Section 2. How to use Bump
==========================================================================

There are several example applications designed to show you how to
use all the tools Bump provides. Here is a quick breakdown of all the
functionality...

bump::String - TODO

bump::Environment - TODO

bump::Uuid - TODO

bump::Log - TODO

bump::NotificationCenter - TODO
