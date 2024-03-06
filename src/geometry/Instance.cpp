#include "Instance.h"

namespace lm {

Instance::Instance(Intersectable* object) : m_object(object) {
    m_aabb = *static_cast<const AABB*>(m_object->getBoundingVolume());
}

std::optional<Intersection> Instance::intersect(
  const Ray& ray, const Interval& interval
) const {
    const auto intersection =
      m_object->intersect(m_transform.transformRay(ray), interval);

    return intersection.has_value()
             ? m_transform.transformIntersection(*intersection)
             : intersection;
}

const BoundingVolume* Instance::getBoundingVolume() const {
    return m_object->getBoundingVolume();
}

}  // namespace lm