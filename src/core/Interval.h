#pragma once

#include "Core.h"

namespace lm {

struct Interval {
    explicit Interval(Float min, Float max);
    explicit Interval(Float min);

    bool inBetween(const float value) const;

    Float min;
    Float max;
};

bool operator==(const Interval& lhs, const Interval& rhs);

}  // namespace lm
