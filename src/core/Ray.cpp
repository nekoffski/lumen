#include "Ray.h"

namespace lm {

Ray::Ray(const Vec3f& origin, const Vec3f& direction) :
    origin(origin), direction(normalize(direction)) {}

Vec3f Ray::at(Float t) const { return origin + t * direction; }

std::string toString(const Ray& ray) {
    return fmt::format("Ray: {} -> {}", ray.origin, ray.direction);
}

}  // namespace lm
