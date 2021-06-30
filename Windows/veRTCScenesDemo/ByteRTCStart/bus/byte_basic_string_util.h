/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief String handler
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <functional>

#pragma once
namespace bytertc {
namespace basic {

// Address string size
enum {
    ADDR_SIZE       = sizeof(intptr_t) * 2 + 2
};

template < typename T >
inline std::string ptr_str(const T* p) {
    std::string _ptrs(ADDR_SIZE, '\0');
    if ( sizeof(intptr_t) == 4 ) {
        // 32Bit
        sprintf(&_ptrs[0], "0x%08x", (unsigned int)(intptr_t)p);
    } else {
        // 64Bit
        sprintf(&_ptrs[0], "0x%016lx", (unsigned long)(intptr_t)p);
    }
    return _ptrs;
}

// Pre define Join Function
template< typename ComIterator, typename Connector_t >
inline std::string join(ComIterator begin, ComIterator end, Connector_t c);

template < typename Component_t, typename Connector_t >
inline std::string join(const Component_t& parts, Connector_t c);


namespace type_traits {
    // Use void_type in template metaprogramming to detect ill-formed types in SFINAE context
    // Until CWG 1558, unused parameters in alias templates were not guaranteed to ensure
    // SFINAE and could be ignored, so we need a more complex definition
    // template < class... > using void_type = void;
    template< typename... __Ty > struct make_void_type { typedef void type; };
    template< typename... __Ty > using void_type = typename make_void_type<__Ty...>::type;

    // Default type checker, match ill-format, any __TyOp and __TyArgs will match
    // this default template
    template < typename __TyVoid, template< class... > class __TyOp, class... __TyArgs >
    struct supported_checker {
        using value_t = std::false_type;
    };

    // If the __TyOp and __TyArgs can match the metafunction type, then means
    // we find the validate expression
    template < template< class... > class __TyOp, class... __TyArgs >
    struct supported_checker< void_type<__TyOp<__TyArgs...>>, __TyOp, __TyArgs... > {
        using value_t = std::true_type;
    };
} // namespace type_traits

// Check if support given expression
template < template< class... > class __TyOp, class... __TyArgs >
using is_supported = typename type_traits::supported_checker< void, __TyOp, __TyArgs... >::value_t;

/**
 * @brief ADL Helper Namespace, inside the namespace, use std::to_sting globally
*/
namespace adl_to_string_helper {
    using std::to_string;

    // const char *
    template < typename T >
    inline typename std::enable_if< std::is_same<T, char>::value, std::string>::type
    cvt_string( const T* t ) { return std::string(t); }

    // function pointer
    template < typename T >
    inline typename std::enable_if< std::is_function<T>::value, std::string>::type
    cvt_string( const T* t ) { return std::string("function_type"); }

    // other unknow pointer
    template < typename T >
    inline typename std::enable_if<
        !std::is_function<T>::value && 
        !std::is_same<T, char>::value,  
        std::string>::type
    cvt_string( const T* t ) { return ptr_str(t); }

    // Check if support to_string
    template < typename T >
    using has_to_string_expr = decltype( to_string( std::declval<T>() ) );
    template < typename T >
    constexpr bool support_to_string = is_supported< has_to_string_expr, T >::value;

    // Default cvt_string for any type has an override to_string function
    template < typename T >
    inline typename std::enable_if< support_to_string<T>, std::string >::type 
    cvt_string( const T& t ) { return to_string(t); }

    // Override for string
    template <typename T>
    inline typename std::enable_if<
        !support_to_string<T> && 
        std::is_same<T, std::string>::value, std::string>::type 
    cvt_string( const T& t ) { return t; }

    // Override for bool
    template <typename T>
    inline typename std::enable_if<
        !support_to_string<T> &&
        std::is_same<T, bool>::value, std::string>::type
    cvt_string( const T& t ) { return std::string( t ? "true" : "false"); }

    template <typename T>
    inline typename std::enable_if<
        !support_to_string<T> && !std::is_pointer<T>::value, std::string>::type
    cvt_string( const T& t ) { return std::string("unknow_conversion"); }
} // namespace adl_to_string_helper

/**
 * @brief  Treat pointer types differently for fix a bug, for example:
 *  int *ptr = nullptr;
 *  auto temp = basic::as_string(ptr);
 *  The value of temp is "false", while the expected value is "0x0000000000000000".
 *  adl_to_string_helper::cvt_string(ptr) matches cvt_string( const T& t ), rather than
 *  cvt_string( const T* t ).
 */
template <typename T, typename std::enable_if<std::is_pointer<T>::value && !std::is_same<
                    typename std::decay<T>::type, char>::value, int>::type = 0>
inline std::string as_string( const T& t ) { 
    return ptr_str((const void*)t);
}

template <typename T, typename std::enable_if<std::is_same<T, char>::value, int>::type = 0>
inline std::string as_string(const T* t) { 
    return std::string(t);
}

/**
 * @brief Export to_string function in current namespace
*/
template <typename T, typename std::enable_if<!std::is_pointer<T>::value, int>::type = 0>
inline std::string as_string( const T& t ) { 
    return adl_to_string_helper::cvt_string( t ); }

// Override for STL container
template < template< class, class > class __TyContainer, class __TyType, class __TyAllocator >
inline std::string as_string( const __TyContainer< __TyType, __TyAllocator >& c ) {
    return std::string("{") + join(c, ",") + std::string("}");
}

template <>
inline std::string as_string(const std::string& str) {
    return str;
}

// Override for STL function
template < template< class, class... > class __TyF, class __TyRet, class... __TyArgs,
    typename std::enable_if<!std::is_same<__TyF<__TyRet, __TyArgs...>, std::string>::value, int>::type = 0>
inline std::string as_string( const __TyF<__TyRet, __TyArgs...> & f ) {
    return std::string("function_type");
}

// Get the carry size
template < typename carry_t > inline size_t carry_size( const carry_t& c ) { return sizeof(c); }
template < > inline size_t carry_size<std::string>(const std::string& c) { return c.size(); }

/**
 * @brief Split a given string with specified carry
*/
template < typename carry_iterator_t >
inline std::vector< std::string > split(const std::string& value, carry_iterator_t b, carry_iterator_t e) {
    std::vector< std::string > components_;
    if ( value.size() == 0 ) return components_;
    std::string::size_type _pos = 0;
    do {
        std::string::size_type _lastPos = std::string::npos;
        size_t _carry_size = 0;
        for ( carry_iterator_t i = b; i != e; ++i ) {
            std::string::size_type _nextCarry = value.find(*i, _pos);
            if ( _nextCarry != std::string::npos && _nextCarry < _lastPos ) {
                _lastPos = _nextCarry;
                _carry_size = carry_size(*i);
            }
        }
        if ( _lastPos == std::string::npos ) _lastPos = value.size();
        if ( _lastPos > _pos ) {
            std::string _com = value.substr( _pos, _lastPos - _pos );
            components_.emplace_back(_com);
        }
        _pos = _lastPos + _carry_size;
    } while( _pos < value.size() );
    return components_;
}

template < typename carry_t >
inline std::vector< std::string > split(const std::string& value, const carry_t& carry) {
    return split(value, std::begin(carry), std::end(carry));
}

// Join Items as String
template< typename ComIterator, typename Connector_t >
inline std::string join(ComIterator begin, ComIterator end, Connector_t c) {
    std::string _final_string;
    if ( begin == end ) return _final_string;
    std::string _cstr = as_string(c);
    auto i = begin, j = (++begin);
    for ( ; j != end; ++i, ++j ) {
        _final_string += as_string(*i);
        _final_string += _cstr;
    }
    _final_string += as_string(*i);
    return _final_string;
}

template < typename Component_t, typename Connector_t >
inline std::string join(const Component_t& parts, Connector_t c) {
    return join(std::begin(parts), std::end(parts), c);
}

} // namespace basic
} // namespace bytertc
 
