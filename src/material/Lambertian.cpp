#include "Lambertian.h"

#include "core/Math.h"

namespace lm {

Lambertian::Lambertian(Texture* texture) : m_texture(texture) {}

Texture* Lambertian::getTexture() const { return m_texture; }

std::optional<ScatterRecord> Lambertian::scatter(
  const Vec3f& normal, [[maybe_unused]] const Vec3f& intersectionPoint
) const {
    return ScatterRecord{ randomUnitHemisphereVec3(normal) };
}

}  // namespace lm
