#pragma once

#include <vector>

#include "Intersectable.h"

namespace lm {

class IntersectableCollection : public Intersectable {
public:
    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const;
    IntersectableCollection& add(Intersectable* object);

private:
    std::vector<Intersectable*> m_objects;
};

}  // namespace lm
