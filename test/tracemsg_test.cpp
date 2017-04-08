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
 * File:   tracemsg_test.cpp
 * Author: alex
 * 
 * Created on January 2, 2015, 12:04 PM
 */

#include "staticlib/config/tracemsg.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include "staticlib/config/assert.hpp"

namespace sl = staticlib;

namespace myfancynamespace {

void test() {
    auto line = __LINE__;
    auto msg = TRACEMSG("foo");
    std::stringstream ss;
    ss << (line + 1);
    auto expected = std::string("foo\n") 
            .append("    at myfancynamespace::test(tracemsg_test.cpp:")
            .append(ss.str())
            .append(")");
    slassert(expected == msg);
    // std::cout << msg << std::endl;
}

namespace { //anonymous

void test_anon() {
    auto msg = TRACEMSG("foo");
    // std::cout << msg << std::endl;
}

} // namespace

template<typename T>
void test_template() {
    auto msg = TRACEMSG("foo");
    // std::cout << msg << std::endl;
}

template<typename T>
class test_template_class {
public:
    void run() {
        auto msg = TRACEMSG("foo");
        // std::cout << msg << std::endl;
    }
};

} // namespace

int main() {
    try {
        myfancynamespace::test();
        myfancynamespace::test_anon();
        myfancynamespace::test_template<int>();
        myfancynamespace::test_template_class<int>().run();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

