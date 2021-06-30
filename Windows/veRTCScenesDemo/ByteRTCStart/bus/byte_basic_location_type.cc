/*
 *  Copyright (c) 2020 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief Code Trace Location
 */

#include "byte_basic_location_type.h"

namespace bytertc {
namespace basic {
/**
 * @brief Code Location Type, Use template so it can be put in just on header file
*/
LocationType::LocationType() : file_name_(""), line_no_(0) { }
LocationType::LocationType( const char* file_name, int line_num ) 
    : file_name_(file_name), line_no_(line_num) { }
LocationType::LocationType( const LocationType& r ) 
    : file_name_(r.file_name_), line_no_(r.line_no_) { }
LocationType::LocationType( LocationType&& r )
    : file_name_(r.file_name_), line_no_(r.line_no_) { }
LocationType& LocationType::operator = ( const LocationType& r ) {
    if ( this == &r ) return *this;
    file_name_ = r.file_name_;
    line_no_ = r.line_no_;
    return *this;
}
LocationType& LocationType::operator = ( LocationType&& r ) {
    if ( this == &r ) return *this;
    file_name_ = r.file_name_;
    line_no_ = r.line_no_;
    return *this;
}
const char* LocationType::FileName() const { return file_name_; }
int LocationType::LineNumber() const { return line_no_; }
std::string LocationType::ToString() const { return this->str(); }
std::string LocationType::str() const {
    std::string output;
    output.resize(256);
    char *cbuf = const_cast<char *>(output.data());
    int len = snprintf(cbuf, 256, "%s:%d", file_name_, line_no_);
    output.resize(len);
    return output;
}
void LocationType::clear() {
    file_name_ = "";
    line_no_ = 0;
}

} // namespace basic
} // namespace bytertc
