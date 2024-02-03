#include "AABB.h"

namespace lm {

AABB::AABB(const Vec3f& min, const Vec3f& max) : m_min(min), m_max(max) {}

bool AABB::intersects(const Ray& ray, const Interval& interval) {
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.direction[a];
        auto orig = ray.origin[a];

        auto t0 = (m_min[a] - orig) * invD;
        auto t1 = (m_max[a] - orig) * invD;

        if (invD < 0) std::swap(t0, t1);

        if (t0 < interval.min) t0 = interval.min;
        if (t1 > interval.max) t1 = interval.max;

        if (t1 <= t0) return false;
    }
    return true;
}

}  // namespace lm
