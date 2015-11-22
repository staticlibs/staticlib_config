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
 * File:   os_test.cpp
 * Author: alex
 *
 * Created on November 22, 2015, 9:39 PM
 */

#include "staticlib/config/os.hpp"

#include <iostream>

int main() {

    std::cout
#ifdef STATICLIB_WINDOWS 
    << "STATICLIB_WINDOWS"
#endif            
#ifdef STATICLIB_IOS
    << "STATICLIB_IOS"
#endif            
#ifdef STATICLIB_MAC
    << "STATICLIB_MAC"
#endif            
#ifdef STATICLIB_ANDROID
    << "STATICLIB_ANDROID"
#endif            
#ifdef STATICLIB_LINUX
    << "STATICLIB_LINUX"
#endif
<< std::endl;

    return 0;
}

