#include "AABB.h"

namespace lm {

AABB::AABB() : m_min(0.0f), m_max(0.0f) {}

AABB::AABB(const Vec3f& min, const Vec3f& max) : m_min(min), m_max(max) {
    static constexpr Float delta = 0.0001f;

    for (u8 axis = 0; axis < 3; ++axis) {
        if ((m_max[axis] - m_min[axis]) < delta) {
            m_max[axis] += delta;
            m_min[axis] -= delta;
        }
    }
}

void AABB::mergeWith(const AABB& oth) {
    for (int i = 0; i < 3; ++i) {
        m_min[i] = std::min(m_min[i], oth.m_min[i]);
        m_max[i] = std::max(m_max[i], oth.m_max[i]);
    }
}

bool AABB::intersects(const Ray& ray, const Interval& interval) const {
    auto localInterval = interval;

    for (int axis = 0; axis < 3; ++axis) {
        localInterval.min = std::max(localInterval.min, m_min[axis]);
        localInterval.max = std::min(localInterval.max, m_max[axis]);

        if (localInterval.max < localInterval.min) return false;
    }
    return true;
}

const Vec3f& AABB::getMin() const { return m_min; }
const Vec3f& AABB::getMax() const { return m_max; }

}  // namespace lm
