Bump
====

Bump is a [FreeBSD](http://en.wikipedia.org/wiki/BSD_licenses) licensed C++ library designed to help make the common things easier. It uses Boost behind the scenes to help with some of the heavy lifting, but you do **NOT** have to write a single line of Boost code to use Bump as a user! Boost is completely hidden behind the Bump interface. This makes it much easier to start using for both novice and advanced C++ developers. Bump comes with an extensive list of example applications designed to quickly introduce a user to the feature sets of Bump. To ensure the quality of Bump, most of the classes have full coverage unit tests written using the Google Test library.

For more information about the project, updates, pending tickets and in-depth documentation about compiling dependencies, compiling Bump, building the documentation and even running the examples, please refer to the following:

* Bump [Home](https://github.com/cnoon/bump)
* Bump [Wiki](https://github.com/cnoon/bump/wiki)

Motiviation
-----------

Have you ever used a language other than C++ and found how easy it is to do string parsing? How about creating a simple timer? Sending an event notification? What about creating files, directories and symlinks? How about in a cross-platform manner? In other languages, many of these features are built directly into the language itself. In C++ this is simply not the case. So what are your options as a guru C++ programmer?

1. You could write your own cross-platform functions to handle all these types of things
2. You could use boost to handle some of them
3. You could just use Qt

The problem with **#1** is that developers just don't have the time to build such a library. Most of us would like to, but let's face it, it's just tough to find the time. The issue with **#2** is that boost can be very daunting for users. The syntax is challenging and can deter users from even attempting to use it. Finally, the issue with **#3** is that not all projects and libraries want Qt as a dependency. It tends to suffer from the case of using a sledgehammer to pound in a nail. Especially when you don't need QtGui support. If this is the case, then you really don't have many options as a C++ developer. For example, let's say your new to C++ development and your teacher gives you an assignment to manipulate the file system using C++ and you can't use Qt......ouch! Good luck as a new C++ developer digging your way through the boost::filesystem API.

Dependencies
------------

Here is a quick list of the dependencies and applications used to build Bump.

**Libraries**

* [Boost](http://www.boost.org/) (required - headers and libraries)
* [Google Test](http://code.google.com/p/googletest/) (optional - necessary to compile the unit tests)

**Applications**

* [CMake](http://cmake.org/) (required - necessary to build Bump)
* [Doxygen](http://www.stack.nl/~dimitri/doxygen/) (optional - necessary to build the documentation)

Installation
------------

Bump uses the CMake build system to make cross-platform compiling as easy as possible for users. The CMakeLists.txt files you will find in most of the Bump directories contain specific information for compiling on many different platforms. If you don't already have CMake install on your system, you can download it from:

* [CMake Downloads](http://CMake.org/CMake/resources/software.html)

Please note that to compile Bump, you must have CMake 2.8.0 or greater installed. Otherwise certain portions of the CMakeLists.txt files are not supported.

### Generating an "in-source" build

For generating an "in-source" build, you can use the configure script provided in the Bump installation directory. This runs the CMake command line tool provided by the CMake installation. The configure script is very short running the command "CMake . -DCMAKE_BUILD_TYPE=Release" to ensure you get the best performance and smallest size for your Bump libraries and example applications.

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
		Right click on the INSTALL project and select "Build"

### Generating an "out-of-source" build

For generating an "out-of-source" build, you can still use the configure script, but first need to make an out-of-source build directory. This is useful for keeping all the CMake build system files out of the original Bump library source.

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
		Right click on the INSTALL project and select "Build"

Usage
-----

There are many cool features inside Bump. The best way to learn how to use Bump is to look at all the examples. Go ahead and compile them and run them. Then step through them in a debugger to get familiar with how the Bump API works. Another helpful tool is to build the documentation with CMake using Doxygen. Then open up the docs with your browser to learn about all the different pieces of Bump. If you really want to dig deep, then I suggest you take a look at the GTest unit test suites. In the meantime, here's a quick breakdown of most of the functionality within Bump...

* **AutoTimer**
	* Want to quickly know how long something takes?
	* Simple! Create a bump::AutoTimer on the stack. When it's destructed, it prints out the elapsed time in your choice of precision.
* **Environment**
	* Gets and sets environment variables and usernames.
* **Exception**
	* Custom exceptions capable of printing out what function, file and line it was thrown on (much easier to debug).
	* They can be re-thrown, and you can even tack on additional messages when re-throwing.
* **FileInfo**
	* Want to know something about a filepath? Then the FileInfo class is what you want. Just pass it a filepath string.
	* You can query all sorts of stuff: File size? Is a directory? Is a file? Basename? Filename? Modified date?
* **FileSystem**
	* Can join filepaths as well as get the current path (cwd) or the temporary path for the current operating system.
	* Manipulates the file system by creating, renaming, copying and removing directories, files and symbolic links.
	* Ever wanted an easy way to copy or remove a directory that is **NOT** empty? Bump's got it!
* **Log**
	* Handles all logging with customizations including 5 different log levels and output redirection.
	* Uses thread-safe access to the stream buffer, can add a timestamp to the message or a custom prefix.
	* Uses convenience macros providing a very concise syntax.
	* Can be controlled at runtime through the use of environment variables.
* **NotificationCenter**
	* Ever use the Objective-C NotificationCenter? Wouldn't it be cool if that existed in C++? Well now it does!
	* Allows you to register observer's methods to receive notifications based on a key.
	* Notifications can be posted with or without an object of any type through the NotificationCenter.
	* All the typecasting is managed internally and is guarded to ensure the proper type was sent to the registered observers.
	* Let me repeat, an abstracted notification system with no typecasting necessary!
* **String**
	* As a subclass of std::string, it can be substituted very easily without breaking pre-existing logic.
	* Constructors support primitive numeric types such as int and long and boolean types such as true or false.
	* Constructors support numeric precision formatting for floats and doubles, bump::String(45.6987348567, 3) // "45.699".
	* Formatting support using the arg methods as well as the << operator.
	* Comparisons with the compare(), startsWith() and endsWith() methods.
	* Manipulation methods such as prepend(), append(), remove(), chop(), trimmed().
	* Substring extraction with the section(), left() and right() methods.
	* Find and replace methods such as indexOf(), lastIndexOf() and replace().
	* Also supports capitalization methods as well as join and split methods.
* **Timeline**
	* Useful for controlling animation behaviors such as linear, ease in, ease out and ease in and out interpolations.
	* Just set your direction, duration, output range and curve shape and the Timeline class will do the rest.
* **Timer**
	* Measures elapsed time and provides many different precision queries.
	* Also contains a singleton timer for ease of use.
* **Uuid**
	* If you need to generate some random UUIDs in your code, then the Uuid class is for you.
	* It can also convert Uuid objects to and from string objects.

Testing
-------

Bump uses the Google Test library to provide a comprehensive set of unittest suites. To execute all the unittests, compile the bumpAllTests application and execute it:

	$ ./bumpAllTests

Support
-------

If you wish to report a bug or request a feature enhancement, please feel free to contact us at <https://github.com/cnoon/bump>.

Credits
-------

Bump is written by:

* Christian Noon

Major portions of this work were supported by [BodyViz](http://www.bodyviz.com/) for the development of their internal volume rendering engine VIPRE.
