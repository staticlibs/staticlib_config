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
 * File:   optional.hpp
 * Author: alex
 *
 * Created on February 4, 2017, 7:40 PM
 */

#ifndef STATICLIB_CONFIG_OPTIONAL_HPP
#define	STATICLIB_CONFIG_OPTIONAL_HPP

#include <type_traits>

#include "staticlib/config/BaseException.hpp"
#include "staticlib/config/noexcept.hpp"

namespace staticlib {
namespace config {

/**
 * Optional-specific exception
 */
class BadOptionalAccessException : public BaseException {
public:
    /**
     * Default constructor
     */
    BadOptionalAccessException() :
    BaseException("Invalid attempt to access non-initialized value of 'optional' object") { }
};

/**
 * Basic implementation of optional, reference impl ( https://github.com/akrzemi1/Optional )
 * cannot be used, as it doesn't support MSVC2013
 */
template<typename T>
class optional {
    /**
     * Space for placement of T instance (to not require DefaultConstructible)
     */
    typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type value_space;
    
    /**
     * Pointer to value
     */
    T* value_ptr = nullptr;
    
public:
    
    /**
     * Constructs empty instance
     */
    optional() { }
    
    /**
     * Constructor
     * 
     * @param value to store in this instance
     */
    explicit optional(T&& value) :
    value_ptr(new (std::addressof(value_space)) T(std::move(value))) { }
    
    /**
     * Deleted copy constructor
     */
    optional(const optional&) = delete;
    
    /**
     * Deleted copy assignment operator
     */
    optional& operator=(const optional&) = delete;
    
    /**
     * Move constructor
     * 
     * @param other other instance
     */
    optional(optional&& other) {
        if(other.has_value())  {
            value_ptr = new (std::addressof(value_space)) T(std::move(other.value()));
            other.reset();
        }
    }
    
    /**
     * Move assignment operator
     * 
     * @param other other instance
     * @return  this instance
     */
    optional& operator=(optional&& other) {
        reset();
        if (other.has_value()) {
            value_ptr = new (std::addressof(value_space)) T(std::move(other.value()));
            other.reset();
        }
        return *this;
    }
    
    /**
     * Destructor
     */
    ~optional() STATICLIB_NOEXCEPT {
        if (has_value()) {
            value_ptr->~T();
        }
    }
    
    /**
     * Overloaded `bool` operator
     * 
     * @return true if this instance stores value, false otherwise
     */
    explicit operator bool() const {
        return has_value();
    }
    
    /**
     * Check whether this instance stores value
     * 
     * @return true if this instance stores value, false otherwise
     */
    bool has_value() const {
        return nullptr != value_ptr;
    }

    /**
     * Access stored value
     * 
     * @return value reference
     * @throws BadOptionalAccessException of this instance is empty
     */
    T& value() {
        if(has_value()) {
            return *value_ptr;
        } else {
            throw BadOptionalAccessException();
        }
    }

    /**
     * Access stored value
     * 
     * @return value const reference
     * @throws BadOptionalAccessException of this instance is empty
     */
    const T& value() const {
        if (has_value()) {
            return *value_ptr;
        } else {
            throw BadOptionalAccessException();
        }
    }

    /**
     * Access stored value; value will be copied out
     * 
     * @param default_value default value
     * @return stored value if has one, default value otherwise
     */
    T value_or(T&& default_value) const {
        if (has_value()) {
            // copy constructor called
            return *value_ptr;
        }
        return std::move(default_value);
    }

    /**
     * Access stored value; value will be moved out
     * of this instance and remaining value will be in
     * "valid, but unspecified state"
     * 
     * @param default_value default value
     * @return stored value if has one, default value otherwise
     */
    T value_or(T&& default_value) {
        if (has_value()) {
            return std::move(*value_ptr);
        }
        return std::move(default_value);
    }
            
    /**
     * Destructs stored value if any
     */
    void reset() {
        if (has_value()) {
            value_ptr->~T();
        }
        value_ptr = nullptr;
    }
    
};

/**
 * Helper function, constructs optional instance
 * 
 * @param value value to store
 * @return optional instance
 */
template<typename T>
optional<T> make_optional(T&& value) {
    return optional<T>(std::move(value));
}

} // namespace
}


#endif	/* STATICLIB_CONFIG_OPTIONAL_HPP */

