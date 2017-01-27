Staticlibs Config headers library
=================================

This project is a part of [Staticlibs](http://staticlibs.net/).

This project contains a number of headers to detect operating system and to 
add features missed on some platforms.

This library is header-only and has no dependencies.

Link to the [API documentation](http://staticlibs.github.io/staticlib_config/docs/html/namespacestaticlib_1_1config.html).

Features
--------

Library include:

    #include "staticlib/config.hpp"

####OS detection

Defines `STATICLIB_<OS_NAME>` macro, where OS_NAME is one of:

 - `WINDOWS`
 - `IOS`
 - `MAC`
 - `ANDROID`
 - `LINUX`

####noexcept macros

Defines `STATICLIB_NOEXCEPT` and `STATICLIB_NOEXCEPT_FALSE` with `noexcept` and `noexcept(false)`
corresponding values on all supported compilers except MSVC 2013 where these macros are empty.

####to_string macro

Implements `to_string` template that calls `std::to_string` on all supported platforms except Android, 
where `std::to_string` is missed for some versions of NDK. `std::stringstream` implementation
is used for Android.

####defer template

Implements a lambda function holder, that will execute specified lambda on destruction.

####BaseException

Exception class that extends `std::exception` and implements constructor that takes `std::string`
and `what` method that returns that string. All module-specific exception classed in Staticlibs 
extends `BaseException`.

####Current function macro

`STATICLIB_CURRENT_FUNCTION` macro (borrowed from Boost) that extracts compiler-specific
name of the current function.

####TRACEMSG

`TRACEMSG` macro takes a message and adds to it a file location information and function name.
Multiple "traced" messages can be combined together to look similar to Java stacktraces.

####Assert macro for tests

`slassert` macro that works similar to `<cassert>` one, but throws `AssertException` with
`TRACEMSG` tracing instead of calling `std::abort`. This macro is not included with `config.hpp`, use:

    #include "staticlib/config/assert.hpp"

License information
-------------------

This project is released under the [Apache License 2.0](http://www.apache.org/licenses/LICENSE-2.0).

Changelog
---------

**2017-01-27**

 * version 1.0.2
 * `make_unique` removed
 * `defer` added

**2016-01-16**

 * version 1.0.1
 * minor CMake changes

**2015-11-21**

 * version 1.0.0
 * initial public version
