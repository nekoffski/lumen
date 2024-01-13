#include "Interval.h"

#include <limits>

namespace lm {

Interval::Interval(Float min, Float max) : min(min), max(max) {
    ASSERT(min <= max, "Invalid interval: min > max");
}

Interval::Interval(Float min) : min(min), max(std::numeric_limits<Float>::max()) {}

bool Interval::inBetween(const Float value) const {
    return min <= value && value <= max;
}

bool operator==(const Interval& lhs, const Interval& rhs) {
    return lhs.min == rhs.min && lhs.max == rhs.max;
}

}  // namespace lm
