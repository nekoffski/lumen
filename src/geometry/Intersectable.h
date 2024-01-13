#pragma once

#include <optional>

#include "core/Core.h"
#include "core/Interval.h"
#include "core/Ray.h"

namespace lm {

struct Intersection {
    Float t;
    Vec3f intersectionPoint;
    Vec3f color;
};

struct Intersectable {
    virtual std::optional<Intersection> intersect(
      const Ray& ray, const Interval& interval
    ) const = 0;
};

}  // namespace lm
