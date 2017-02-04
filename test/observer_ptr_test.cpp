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
 * File:   observer_ptr_test.cpp
 * Author: alex
 *
 * Created on February 4, 2017, 9:12 PM
 */

#include "staticlib/config/observer_ptr.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "staticlib/config/assert.hpp"

namespace sc = staticlib::config;

bool throws_exc(std::function<void() > fun) {
    try {
        fun();
    } catch (const sc::BadObservedPointerAccessException& e) {
        (void) e;
        return true;
    }
    return false;
}

void test_some() {
    auto owner = std::unique_ptr<std::string>(new std::string("42"));
    auto observer = sc::make_observer_ptr(owner.get());
    slassert(observer.has_value());
    slassert(observer);
    slassert("42" == *observer);
    observer.reset();
    slassert(!observer.has_value());
    slassert(!observer);
}

void test_none() {
    auto none = sc::observer_ptr<int>();
    slassert(!none.has_value());
    slassert(!none);
    bool caught = throws_exc([&none] { *none; });
    slassert(caught);
}

void test_copy() {
    auto owner = std::unique_ptr<std::string>(new std::string("42"));
    auto observer1 = sc::make_observer_ptr(owner.get());
    auto observer2 = observer1;

    slassert(observer1.has_value());
    slassert(observer1);
    slassert("42" == *observer1);

    slassert(observer2.has_value());
    slassert(observer2);
    slassert("42" == *observer2);
}

int main() {
    try {
        test_some();
        test_none();
        test_copy();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

