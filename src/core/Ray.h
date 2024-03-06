#pragma once

#include "Core.h"
#include "Math.h"

namespace lm {

class Ray {
public:
    explicit Ray(const Vec3f& origin, const Vec3f& direction);

    Vec3f at(Float t) const;

    Vec3f origin;
    Vec3f direction;
};

std::string toString(const Ray& ray);

}  // namespace lm

TO_STRING_STREAM(lm::Ray);
