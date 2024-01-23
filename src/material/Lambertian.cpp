#include "Lambertian.h"

#include "core/Math.h"

namespace lm {

Lambertian::Lambertian(Texture* texture) : m_texture(texture) {}

Texture* Lambertian::getTexture() const { return m_texture; }

std::optional<ScatterRecord> Lambertian::scatter(
  [[maybe_unused]] const Ray& ray, const Vec3f& normal,
  [[maybe_unused]] const Vec3f& intersectionPoint
) const {
    return ScatterRecord{ normal + randomUnitSphereVec3() };
}

}  // namespace lm
