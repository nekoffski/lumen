#pragma once

#include <vector>
#include <memory>

#include "Intersectable.h"

namespace lm {

class IntersectableCollection : public Intersectable {
public:
    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const;
    void add(Intersectable* object);

private:
    std::vector<Intersectable*> m_objects;
};

}  // namespace lm
