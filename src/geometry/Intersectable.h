#pragma once

#include <optional>

#include "core/Core.h"
#include "core/Interval.h"
#include "core/Ray.h"

#include "BoundingVolume.h"

#include "material/Material.h"

namespace lm {

class Intersection {
public:
    explicit Intersection(
      Float t, const Vec3f& intersectionPoint, bool isFrontFace, const Vec3f& normal,
      Material* material
    );

    Vec3f getColor() const;
    Vec3f getEmittedColor() const;

    std::optional<ScatterRecord> scatter(const Ray& ray) const;

    Float t;
    Vec3f intersectionPoint;
    Vec3f normal;
    bool isFrontFace;

private:
    Material* m_material;
};

struct Intersectable {
    virtual std::optional<Intersection> intersect(
      const Ray& ray, const Interval& interval
    ) const = 0;

    virtual const BoundingVolume* getBoundingVolume() const { return nullptr; }
};

}  // namespace lm
