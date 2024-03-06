#pragma once

#include <memory>

#include "Intersectable.h"
#include "AABB.h"

namespace lm {

class BVHNode : public Intersectable {
public:
    explicit BVHNode(const std::vector<Intersectable*>& objects);
    explicit BVHNode(const std::vector<Intersectable*>& objects, u64 start, u64 end);

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const override;

    const BoundingVolume* getBoundingVolume() const override;

private:
    static bool boxCompare(Intersectable* a, Intersectable* b, u16 axis);
    static bool xBoxCompare(Intersectable* a, Intersectable* b);
    static bool yBoxCompare(Intersectable* a, Intersectable* b);
    static bool zBoxCompare(Intersectable* a, Intersectable* b);

    std::shared_ptr<Intersectable> m_left;
    std::shared_ptr<Intersectable> m_right;

    AABB m_boundingVolume;
};

}  // namespace lm
