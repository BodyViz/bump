Bump
====

Bump is a [FreeBSD](http://en.wikipedia.org/wiki/BSD_licenses) licensed C++ library designed to help make the common things easier. It uses Boost behind the scenes to help with some of the heavy lifting, but you do **NOT** have to write a single line of Boost code to use Bump as a user! Boost is completely hidden behind the Bump interface. This makes it much easier to start using for both novice and advanced C++ developers. Bump comes with an extensive list of example applications designed to quickly introduce a user to the feature sets of Bump. To ensure the quality of Bump, most of the classes have full coverage unit tests written using the Google Test library.

Motivation
----------

Have you ever used a language other than C++ and found how easy it is to do string parsing? How about creating a simple timer? Sending an event notification? What about creating files, directories and symlinks? How about in a cross-platform manner? In other languages, many of these features are built directly into the language itself. In C++ this is simply not the case. So what are your options as a guru C++ programmer?

1. You could write your own cross-platform functions to handle all these types of things
2. You could use boost to handle some of them
3. You could just use Qt

The problem with **#1** is that developers just don't have the time to build such a library. Most of us would like to, but let's face it, it's just tough to find the time. The issue with **#2** is that boost can be very daunting for users. The syntax is challenging and can deter users from even attempting to use it. Finally, the issue with **#3** is that not all projects and libraries want Qt as a dependency. It tends to suffer from the case of using a sledgehammer to pound in a nail. Especially when you don't need QtGui support. If this is the case, then you really don't have many options as a C++ developer. For example, let's say you're new to C++ development and your teacher gives you an assignment to manipulate the file system using C++ and you can't use Qt......ouch! Good luck as a new C++ developer digging your way through the boost::filesystem API.

Requirements
------------

| | Version | Notes |
|---|---|---|
| **CMake** | 3.30 or newer | |
| **C++** | C++20 | Propagated to consumers; you do not set `CMAKE_CXX_STANDARD` yourself |
| **Boost** | 1.91 or newer | `date_time filesystem regex thread timer` |
| **Google Test** | 1.17 | Only when `BUMP_BUILD_TESTS=ON`. What Bump is tested against; no floor is enforced |
| **Doxygen** | 1.9 or newer | Only when `BUMP_BUILD_DOCS=ON`. No floor is enforced; `WARN_AS_ERROR=FAIL_ON_WARNINGS` is what wants a recent one. Graphviz is not required |

Compilers: AppleClang, Clang, GCC, and MSVC (Visual Studio 2022, `v143`).

`smallsha1` is vendored in `src/smallsha1` and needs nothing from you.

Building
--------

Bump ships a `CMakePresets.json`, but every preset in it is **hidden**, because everything a visible
preset would have to state — where Boost and Google Test live, which architecture they were built
for, where to install — is specific to your machine, and Bump asserts none of it. Copy
`CMakeUserPresets.json.example` to `CMakeUserPresets.json` (that name is gitignored), edit the paths,
and inherit whichever base you want:

| Inheritable preset | Generator | Flavour |
|---|---|---|
| `macos-ninja` | Ninja Multi-Config | static |
| `macos-ninja-shared` | Ninja Multi-Config | shared |
| `macos-ninja-framework` | Ninja Multi-Config | `bump.framework` |
| `macos-xcode` | Xcode | static |
| `windows-vs2022` | Visual Studio 17 2022, x64 | static |
| `windows-vs2022-shared` | Visual Studio 17 2022, x64 | DLL |

```bash
cmake --preset ninja                       # a name you defined in CMakeUserPresets.json
cmake --build build/ninja --config Release
ctest --test-dir build/ninja -C Release -j8
cmake --install build/ninja --config Release
```

Or without any presets at all, supplying the dependency locations yourself:

```bash
cmake -S . -B build/release -G "Ninja Multi-Config" \
      -DCMAKE_PREFIX_PATH="/path/to/boost;/path/to/googletest" \
      -DCMAKE_INSTALL_PREFIX=/path/to/install
```

`CMAKE_PREFIX_PATH` is also an environment variable CMake consults, so a fresh clone with no user
presets configures without a single `-D`:

```bash
CMAKE_PREFIX_PATH=/path/to/boost:/path/to/googletest \
    cmake -S . -B build/release -G "Ninja Multi-Config"
```

Note the separator is the platform's — `:` on Unix, `;` on Windows — not the `;` a CMake list uses.
The committed presets are all hidden, so `cmake --preset ninja` is not a command you can run;
inherit from it in your own `CMakeUserPresets.json` instead.

**The committed presets are configure presets only.** There are deliberately no committed build, test
or package presets: they multiply with every flavour and configuration, and `--config`/`-C` says the
same thing without a committed entry per combination. Define your own in `CMakeUserPresets.json` if
you would rather type `cmake --build --preset ninja-release`.

### Options

| Option | Default | Effect |
|---|---|---|
| `BUILD_SHARED_LIBS` | `OFF` | Build a shared library instead of a static one. CMake's standard control. |
| `BUMP_BUILD_EXAMPLES` | `ON` | Build the example applications |
| `BUMP_BUILD_TESTS` | `OFF` | Build the test suites and register CTest tests |
| `BUMP_BUILD_DOCS` | `OFF` | Build the Doxygen reference documentation |
| `BUMP_HIDE_PRIVATE_SYMBOLS` | `ON` | Export only `BUMP_EXPORT`-annotated symbols |
| `BUMP_BUILD_FRAMEWORK` | `OFF` | macOS only; requires `BUILD_SHARED_LIBS`. Builds `bump.framework` |
| `BUMP_WIN32_USE_MP` | `ON` | MSVC only; compile with `/MP` |

Static, shared and framework are one-at-a-time — Bump is a single target whose type is chosen at
configure time — so give each flavour its own install prefix. **Debug and Release do coexist in one
prefix**, which is the point of the `d` suffix on the debug library: install one and then the other
and `find_package` resolves both.

Bump respects `CMAKE_COMPILE_WARNING_AS_ERROR`, which the committed presets turn **on**. To see every
warning at once instead of stopping at the first, configure a second tree with
`--compile-no-warning-as-error` — note that is a `cmake` *configure* option, not a `cmake --build`
one:

```bash
cmake -S . --preset ninja -B build/ninja-warn --compile-no-warning-as-error
cmake --build build/ninja-warn --config Release
```

Bump deliberately does **not** set `CMAKE_OSX_ARCHITECTURES` or `CMAKE_OSX_DEPLOYMENT_TARGET`. Both
follow from whichever Boost you built against, not from anything Bump requires, so they belong in
your presets or toolchain file. Set them to match your Boost or the linker will warn.

Using Bump in your own project
------------------------------

```cmake
find_package(Bump 2 REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE Bump::bump)
```

That is the whole integration. Include directories, C++20, the export macro definition and Boost all
arrive through the imported target, so there is nothing to add: no `-I`, no `-D`, no
`CMAKE_CXX_STANDARD`, no Boost hint. Point CMake at the install prefix with `CMAKE_PREFIX_PATH` (or
`Bump_DIR`) and write `#include <bump/bump.h>`.

The version constraint is `SameMajorVersion`, so `find_package(Bump 2)` keeps working across future
2.x releases while correctly rejecting a request for `Bump 1.x` or `Bump 3`. Asking for a *newer*
minor than the one installed — `find_package(Bump 2.1)` against 2.0.0 — is also rejected.

`tests/package-test/` is a complete working example: a standalone project that links the installed
package and nothing else.

Testing
-------

Configure with `-DBUMP_BUILD_TESTS=ON` and the suites become **individually addressable CTest
tests**, one per `TEST_F`:

```bash
ctest --test-dir build/ninja -C Release -j8                    # everything
ctest --test-dir build/ninja -C Release -R "^StringTest\."     # one suite
ctest --test-dir build/ninja -C Release --rerun-failed
```

Anchor the filter on the suite name — `-R String` also matches tests in other suites that happen to
have `String` in the name. Each suite is also its own executable, so you can run or debug one on its
own from Xcode or Visual Studio without running the others. JUnit XML for every test lands in
`build/<preset>/test-results/`.

**On Windows, some of the filesystem tests need Developer Mode enabled** (or an elevated process),
because they create symbolic links. Each test that touches the filesystem works in a uniquely named
directory under the system temporary location, created and removed by the fixture, so nothing is
written beside the binary and the build tree itself may live on a network drive or VM shared folder.

Documentation
-------------

```bash
cmake -S . -B build/docs -DBUMP_BUILD_DOCS=ON -DCMAKE_PREFIX_PATH="/path/to/boost"
cmake --build build/docs --target bump_docs
open build/docs/doc/BumpReferenceDocs/index.html
```

Doxygen is a soft dependency: without it the configure warns and skips the target rather than
failing. There is no checked-in Doxyfile — CMake generates one from whichever Doxygen is installed,
so the config cannot go stale. The docs are also part of the default build target whenever
`BUMP_BUILD_DOCS` is on, and install as the `bump-doc` component:

```bash
cmake --install build/docs --config Release --component bump-doc
```

**Documentation warnings are errors.** `WARN_AS_ERROR=FAIL_ON_WARNINGS` means a stale `@param`, a
`@return` on a `void`, or a new public class or method with no doc comment fails the build. So
document public API as you add it. The current baseline is zero warnings, so this is cheap to keep
green. Private and protected data members
are excluded by name rather than by being undocumented, which is what lets an undocumented *public*
member be reported instead of silently omitted.

Usage
-----

There are many cool features inside Bump. The best way to learn how to use Bump is to look at all the
examples. Go ahead and compile them and run them. Then step through them in a debugger to get
familiar with how the Bump API works. Another helpful tool is to build the documentation and open it
in your browser. If you really want to dig deep, then take a look at the GTest unit test suites. In
the meantime, here's a quick breakdown of most of the functionality within Bump...

* **AutoTimer**
	* Want to quickly know how long something takes?
	* Simple! Create a bump::AutoTimer on the stack. When it's destructed, it prints out the elapsed time in your choice of precision.
* **CryptographicHash**
	* Need to generate a hex string hash for textual or binary data?
	* Just pass off your data and call the result method...simple and efficient sha1 hex string hashing.
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
	* Handles all logging with customizations including multiple log levels and output redirection.
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
* **TextFileReader**
	* Reads a text file into a single string or into a list of lines, with an optional line limit.
* **Timeline**
	* Useful for controlling animation behaviors such as linear, ease in, ease out and ease in and out interpolations.
	* Just set your direction, duration, output range and curve shape and the Timeline class will do the rest.
* **Timer**
	* Measures elapsed time and provides many different precision queries.
	* Also contains a singleton timer for ease of use.
* **Uuid**
	* If you need to generate some random UUIDs in your code, then the Uuid class is for you.
	* It can also convert Uuid objects to and from string objects.

Every one of these is reachable through the `<bump/bump.h>` umbrella header.

Code Style
----------

Bump uses `clang-format` to keep formatting consistent. The style is defined in `.clang-format` at the repository root, so no arguments are needed:

	$ git ls-files '*.h' '*.cpp' | grep -v smallsha1 | xargs clang-format -i

That covers the library, the examples and the tests, and picks up new files as they are added. The vendored `src/smallsha1` sources are deliberately excluded from formatting.

Because the whole codebase was reformatted in a single commit, `git blame` needs to be told to skip it. Run this once per clone:

	$ git config blame.ignoreRevsFile .git-blame-ignore-revs

GitHub applies `.git-blame-ignore-revs` automatically in its own blame view.

Credits
-------

Bump is written by:

* Christian Noon

Major portions of this work were supported by [BodyViz](http://www.bodyviz.com/) for the development of their internal volume rendering engine VIPRE.
