#include "IntersectableCollection.h"

namespace lm {

std::optional<Intersection> IntersectableCollection::intersect(
  const Ray& ray, const Interval& interval
) const {
    auto localInterval                     = interval;
    std::optional<Intersection> closestHit = {};
    for (const auto& object : m_objects) {
        if (auto record = object->intersect(ray, localInterval); record) {
            localInterval.max = record->t;
            closestHit        = record;
        }
    }
    return closestHit;
}

IntersectableCollection& IntersectableCollection::add(Intersectable* object) {
    m_objects.push_back(object);
    return *this;
}

}  // namespace lm
