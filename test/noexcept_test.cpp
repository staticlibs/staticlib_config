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
 * File:   noexcept_test.cpp
 * Author: alex
 *
 * Created on November 22, 2015, 9:39 PM
 */

#include "staticlib/config/noexcept.hpp"

#include <iostream>

void test_compiles_noexcept() STATICLIB_NOEXCEPT {
    // pass
}

void test_compiles_noexcept_false() STATICLIB_NOEXCEPT_FALSE {
    // pass
}

int main() {
    try {
        test_compiles_noexcept();
        test_compiles_noexcept_false();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

