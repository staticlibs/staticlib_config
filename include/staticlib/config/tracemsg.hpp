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
 * File:   tracemsg.hpp
 * Author: alex
 *
 * Created on January 2, 2015, 11:53 AM
 */

#ifndef STATICLIB_CONFIG_TRACEMSG_HPP
#define STATICLIB_CONFIG_TRACEMSG_HPP

#include <limits>
#include <string>

#include "staticlib/config/current_function.hpp"
#include "staticlib/config/os.hpp"

#ifdef STATICLIB_ANDROID
#include <sstream>
#endif // STATICLIB_ANDROID

#define TRACEMSG(message) staticlib::config::tracemsg(std::string() + message, __FILE__, STATICLIB_CURRENT_FUNCTION, __LINE__)

namespace staticlib {
namespace config {

/**
 * Prepends specified message with formatted current function name, source file name and line number.
 * Can be used through macro shortcut as `TRACEMSG("Hi")`
 * 
 * @param message input message
 * @param file source filename, `__FILE__` macro is used in `TRACEMSG` macro
 * @param func current function name, `STATICLIB_CURRENT_FUNCTION` macro is used in `TRACEMSG` macro
 * @param line current line in source file, `__LINE__` macro is used in `TRACEMSG` macro
 * @return message string prepended with specified data
 */
inline std::string tracemsg(const std::string& message, const std::string& file, const std::string& func, int line) {
    // cleanup function name
    auto paren_ind = func.find("(");    
    auto fun_end_pos = std::string::npos != paren_ind ? paren_ind : message.length();
    auto space_ind = func.find_last_of(" ", fun_end_pos);
    auto fun_start_pos = (std::string::npos != space_ind && fun_end_pos > space_ind) ? space_ind + 1 : 0;
    // cleanup filename
    std::string::size_type filename_start_pos = 0;
    auto slash_ind = file.find_last_of("/");
    if (std::string::npos != slash_ind && file.length() > slash_ind) {
        filename_start_pos = slash_ind + 1;
    } else {
        auto backslash_ind = file.find_last_of("\\");
        if (std::string::npos != backslash_ind && file.length() > backslash_ind) {
            filename_start_pos = backslash_ind + 1;
        }
    }
    // to_string moved to sl::support
#ifdef STATICLIB_ANDROID    
    std::stringstream linestream;
    linestream << line;
    std::string linest = linestream.str();
#else //!STATICLIB_ANDROID
    std::string linest = std::to_string(line);
#endif // STATICLIB_ANDROID    
    // format message
    return std::string()
            .append(message)
            .append("\n    at ")
            .append(func, fun_start_pos, fun_end_pos - fun_start_pos)
            .append("(")
            .append(file, filename_start_pos, file.length() - filename_start_pos)
            .append(":")
            .append(linest)
            .append(")");
}

} //namespace
}

#endif /* STATICLIB_CONFIG_TRACEMSG_HPP */
