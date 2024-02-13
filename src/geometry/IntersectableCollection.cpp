#include "IntersectableCollection.h"

namespace lm {

std::optional<Intersection> IntersectableCollection::intersect(
  const Ray& ray, const Interval& interval
) const {
    if (not m_boundingVolume.intersects(ray, interval)) return {};

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

void IntersectableCollection::add(Intersectable* object) {
    m_objects.push_back(object);
}

void IntersectableCollection::buildBoundingVolume() {
    for (auto& object : m_objects) {
        auto aabb = static_cast<const AABB*>(object->getBoundingVolume());
        m_boundingVolume.mergeWith(*aabb);
    }
}

const std::vector<Intersectable*>& IntersectableCollection::getObjects() {
    return m_objects;
}

}  // namespace lm
