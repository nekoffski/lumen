#pragma once

#include "Intersectable.h"
#include "Transform.h"

namespace lm {

class Instance : public Intersectable {
public:
    explicit Instance(Intersectable* object);

    std::optional<Intersection> intersect(const Ray& ray, const Interval& interval)
      const override;
    const BoundingVolume* getBoundingVolume() const override;

    template <typename T, typename... Args> void addTransform(Args&&... args) {
        m_aabb =
          m_transform.add<T>(std::forward<Args>(args)...)
            ->transformBoundingBox(m_aabb);
    }

private:
    Intersectable* m_object;
    TransformChain m_transform;
    AABB m_aabb;
};

}  // namespace lm