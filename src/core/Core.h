#pragma once

#include <cstdint>

#include <kc/core/Log.h>

namespace lm {

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8  = uint8_t;

using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8  = int8_t;

using Float = float;

template <typename T> struct Coordinates {
    T x;
    T y;
};

}  // namespace lm
