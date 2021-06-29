#pragma once

#ifdef WIN32
#define BYTEAUDIO_API __declspec(dllexport)
#else
#define BYTEAUDIO_API __attribute__((__visibility__("default")))
#endif

#include <stdint.h>

#include <string>
#include <vector>

namespace bae {

enum class ByteAudioValueType {
    kNull,
    kBool,
    kInt,
    kUint32,
    kInt64,
    kFloat,
    kDouble,
    kPointer,
    kCString,
};

class BYTEAUDIO_API ByteAudioValue {
public:
    // construct a int value
    explicit ByteAudioValue(bool value);

    // construct a int value
    explicit ByteAudioValue(int value);

    // construct a uint32_t value
    explicit ByteAudioValue(uint32_t value);

    // construct a int64_t value
    explicit ByteAudioValue(int64_t value);

    // construct a float value
    explicit ByteAudioValue(float value);

    // construct a double value
    explicit ByteAudioValue(double value);

    // construct a pointer value, no copy
    explicit ByteAudioValue(const void* pointer, size_t size);

    // construct a c-string value, no string copy
    explicit ByteAudioValue(const char* str, size_t length);

    explicit ByteAudioValue();

    ByteAudioValue(const ByteAudioValue& o) = default;
    ByteAudioValue(ByteAudioValue&& o) = default;

    ByteAudioValue& operator=(const ByteAudioValue&) = default;
    ByteAudioValue& operator=(ByteAudioValue&&) = default;

    // get the bool value if type is kBool
    bool bool_value() const;

    // get the int value if type is kInt
    int int_value() const;

    // get the uint32 value if type is kUint32
    uint32_t uint32_value() const;

    // get the int64 value if type is kInt64
    int64_t int64_value() const;

    // get the float value if type is kFloat
    float float_value() const;

    // get the double value if type is kDouble
    double double_value() const;

    // get the pointer value if type is kPointer
    const void* pointer_value() const;

    // get the cstring value if type is kCString
    const char* cstring_value() const;

    // get the value's type
    ByteAudioValueType get_type() const;

    // get the value's size
    size_t get_size() const;

    // whether has value
    bool has_value() const;

    // to string for print
    const std::string to_string() const;

private:
    ByteAudioValueType type_;

    union Data {
        Data(bool v) : bool_value(v) {
        }
        Data(int v) : int_value(v) {
        }
        Data(uint32_t v) : uint32_value(v) {
        }
        Data(int64_t v) : int64_value(v) {
        }
        Data(float v) : float_value(v) {
        }
        Data(double v) : double_value(v) {
        }
        Data(const void* v) : pointer_value(v) {
        }
        Data(const char* v) : cstring_value(v) {
        }
        bool bool_value;
        int int_value;
        uint32_t uint32_value;
        int64_t int64_value;
        float float_value;
        double double_value;
        const void* pointer_value;
        const char* cstring_value;
    } data_;
    size_t size_;
};

}  // namespace bae
