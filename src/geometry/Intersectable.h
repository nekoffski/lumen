#pragma once

#include <optional>

#include "core/Core.h"
#include "core/Interval.h"
#include "core/Ray.h"

#include "material/Material.h"

namespace lm {

class Intersection {
public:
    explicit Intersection(
      Float t, const Vec3f& intersectionPoint, const Vec3f& normal,
      Material* material
    );

    Vec3f getColor() const;

    std::optional<ScatterRecord> scatter(const Ray& ray) const;

    Float t;
    Vec3f intersectionPoint;
    Vec3f normal;

private:
    Material* m_material;
};

struct Intersectable {
    virtual std::optional<Intersection> intersect(
      const Ray& ray, const Interval& interval
    ) const = 0;
};

}  // namespace lm
