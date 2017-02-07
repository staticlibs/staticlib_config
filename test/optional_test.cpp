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
 * File:   optional_test.cpp
 * Author: alex
 *
 * Created on February 4, 2017, 8:14 PM
 */

#include "staticlib/config/optional.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "staticlib/config/assert.hpp"

namespace sc = staticlib::config;

bool throws_exc(std::function<void() > fun) {
    try {
        fun();
    } catch (const sc::bad_optional_access_exception& e) {
        (void) e;
        return true;
    }
    return false;
}

void test_some() {
    auto some = sc::make_optional(42);
    slassert(some.has_value());
    slassert(some);
    slassert(42 == some.value());
    slassert(42 == some.value_or(43));
}

void test_none() {
    auto none = sc::optional<int>();
    slassert(!none.has_value());
    slassert(!none);
    bool caught = throws_exc([&none] { none.value(); });
    slassert(caught);
    slassert(43 == none.value_or(43));
}

void test_reset() {
    auto some = sc::make_optional(42);
    some.reset();
    slassert(!some.has_value());
    slassert(!some);
    bool caught = throws_exc([&some] { some.value(); });
    slassert(caught);
    slassert(43 == some.value_or(43));
}

void test_nocopy() {
    auto some = sc::make_optional(std::unique_ptr<std::string>(new std::string("42")));
    slassert(some.has_value());
    slassert(some);
    slassert("42" == *some.value());
    // will be moved out
    auto ptr = some.value_or(std::unique_ptr<std::string>(new std::string("43")));
    slassert("42" == *ptr);
    slassert(some);
    // value moved out, but not destructed
    slassert(nullptr == some.value().get());
}

int main() {
    try {
        test_some();
        test_none();
        test_reset();
        test_nocopy();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

