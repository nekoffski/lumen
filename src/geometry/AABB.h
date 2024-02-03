#pragma once

#include "core/Math.h"

#include "BoundingVolume.h"

namespace lm {

class AABB : public BoundingVolume {
public:
    explicit AABB(const Vec3f& min, const Vec3f& max);

    bool intersects(const Ray& ray, const Interval& interval) override;

private:
    Vec3f m_min;
    Vec3f m_max;
};

}  // namespace lm