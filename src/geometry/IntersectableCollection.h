#pragma once

#include <vector>
#include <memory>

#include "Intersectable.h"
#include "AABB.h"

namespace lm {

class IntersectableCollection : public Intersectable {
public:
    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const;
    void add(Intersectable* object);
    void buildBoundingVolume();

    const std::vector<Intersectable*>& getObjects();
    const BoundingVolume* getBoundingVolume() const override;

private:
    std::vector<Intersectable*> m_objects;
    AABB m_boundingVolume;
};

}  // namespace lm
