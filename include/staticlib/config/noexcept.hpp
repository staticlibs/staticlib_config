/*
 * Copyright 2015, alex at staticlibs.net
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * File:   noexcept.hpp
 * Author: alex
 *
 * Created on November 21, 2015, 6:40 PM
 */

#ifndef STATICLIB_CONFIG_NOEXCEPT_HPP
#define	STATICLIB_CONFIG_NOEXCEPT_HPP

// http://stackoverflow.com/a/18387764/314015
// Compliant C++11 compilers put noexcept specifiers on error_category
// VS2013 is _MSC_VER 1800, VS2015 is _MSC_VER 1900
#ifndef _MSC_VER
#  define STATICLIB_NOEXCEPT noexcept
#  define STATICLIB_NOEXCEPT_FALSE noexcept(false)
#  define STATICLIB_NOEXCEPT_SUPPORTED
#else
#  if (_MSC_VER >= 1900)
#    define STATICLIB_NOEXCEPT noexcept(true)
#    define STATICLIB_NOEXCEPT_FALSE noexcept(false)
#    define STATICLIB_NOEXCEPT_SUPPORTED
#  endif //(_MSC_VER >= 1900)
#endif // _MSC_VER
# if !defined(STATICLIB_NOEXCEPT)
#  define STATICLIB_NOEXCEPT
#endif //!defined(STATICLIB_NOEXCEPT)


#endif	/* STATICLIB_CONFIG_NOEXCEPT_HPP */

