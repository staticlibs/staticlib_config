/*
 * Copyright 2017, alex at staticlibs.net
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
 * File:   defer.hpp
 * Author: alex
 *
 * Created on January 27, 2017, 12:07 PM
 */

#ifndef STATICLIB_CONFIG_DEFER_HPP
#define	STATICLIB_CONFIG_DEFER_HPP

#include "staticlib/config/noexcept.hpp"

#include <utility>

namespace staticlib {
namespace config {

namespace detail {

// http://stackoverflow.com/a/17356259/314015
/**
 * Holder object for a lambda, that will
 * be executed on destruction. Lambda must be "noexcept".
 */
template<typename T>
class defer_guard {
    T func;
    
public:
    /**
     * Constructor
     * 
     * @param func lambda function to execute on destruction
     */
    defer_guard(T func) :
    func(std::move(func)) { }

    /**
     * Deleted copy constructor
     */
    defer_guard(const defer_guard&) = delete;
    
    /**
     * Deleted copy-assignment operator
     */
    defer_guard& operator=(const defer_guard&) = delete;
    
    /**
     * Move constructor
     * 
     * @param other other instance
     */
    defer_guard(defer_guard&& other) :
    func(std::move(other.func)) { }

    /**
     * Destructor, will execute lambda function
     */
    ~defer_guard() STATICLIB_NOEXCEPT {
        static_assert(noexcept(func()),
                "Please check that the defer block cannot throw, "
                "and mark the lambda as noexcept.");
        func();
    }
};

} // namespace

/**
 * Creates a "guard object", that will execute
 * specified lambda function on destruction.
 * 
 * @param func lambda function to execute on destruction,
 *        must be "noexcept"
 * @return guard object
 */
template<typename T>
detail::defer_guard<T> defer(T func) {
    return detail::defer_guard<T>(std::move(func));
}

} // namespace
}

#endif	/* STATICLIB_CONFIG_DEFER_HPP */

