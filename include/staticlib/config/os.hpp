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
 * File:   os.hpp
 * Author: alex
 *
 * Created on November 21, 2015, 6:45 PM
 */

#ifndef STATICLIB_CONFIG_OS_HPP
#define	STATICLIB_CONFIG_OS_HPP

// http://stackoverflow.com/a/5920028/314015
#ifdef _WIN32
#define STATICLIB_WINDOWS
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#define STATICLIB_IOS
#elif TARGET_OS_IPHONE
#define STATICLIB_IOS
#elif TARGET_OS_MAC
#define STATICLIB_MAC
#endif
#elif __ANDROID__
#define STATICLIB_ANDROID
#elif __linux
#define STATICLIB_LINUX
#endif

#endif	/* STATICLIB_CONFIG_OS_HPP */

