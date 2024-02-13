#pragma once

#include "core/Math.h"

#include "BoundingVolume.h"

namespace lm {

class AABB : public BoundingVolume {
public:
    explicit AABB();
    explicit AABB(const Vec3f& min, const Vec3f& max);

    void mergeWith(const AABB& oth);

    bool intersects(const Ray& ray, const Interval& interval) const override;

    const Vec3f& getMin() const;
    const Vec3f& getMax() const;

private:
    Vec3f m_min;
    Vec3f m_max;
};

}  // namespace lm