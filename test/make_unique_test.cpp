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
 * File:   make_unique_test.cpp
 * Author: alex
 *
 * Created on November 21, 2015, 8:34 PM
 */

#include "staticlib/config/make_unique.hpp"

#include <iostream>

#include "staticlib/config/assert.hpp"

namespace sc = staticlib::config;

void test_make_unique() {
    std::unique_ptr<std::string> ptr = sc::make_unique<std::string>("42");
    slassert("42" == *ptr.get());
}

int main() {
    try {
        test_make_unique();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

