#pragma once

#include "core/Ray.h"
#include "core/Interval.h"

namespace lm {

struct BoundingVolume {
    virtual bool intersects(const Ray& ray, const Interval& interval) const = 0;
};

}  // namespace lm
