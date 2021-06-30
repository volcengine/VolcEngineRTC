/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Code Trace Location
 */

#pragma once

#include <iostream>
#include <string>
#include "byte_basic_string_util.h"

namespace bytertc {
namespace basic {

/**
 * @brief Code Location Type, Use template so it can be put in just on header file
*/
class LocationType {
public:
    LocationType();
    LocationType( const char* file_name, int line_num );
    LocationType( const LocationType& r );
    LocationType( LocationType&& r );
    LocationType& operator = ( const LocationType& r );
    LocationType& operator = ( LocationType&& r );
    const char* FileName() const;
    int LineNumber() const;
    std::string ToString() const;
    std::string str() const;
    void clear();

private:
    const char* file_name_;
    int line_no_;
};

typedef LocationType    TraceLocation;
/**
 * @brief Define a macro to record the current source location.
*/
#ifdef __FILE_NAME__
#define __PURE_FILE_NAME__      __FILE_NAME__
#else
#define __PURE_FILE_NAME__      __FILE__
#endif

#define CODE_FROM_HERE \
    ::bytertc::basic::LocationType(__PURE_FILE_NAME__, __LINE__)

/**
 * @brief std::to_string for LocationType
*/
template < >
inline std::string as_string( const bytertc::basic::LocationType & l ) {
    return l.str();
}

} // namespace basick
} // namespace bytertc
