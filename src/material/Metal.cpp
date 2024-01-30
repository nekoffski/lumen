#include "Metal.h"

#include "core/Math.h"

namespace lm {

Metal::Metal(Texture* texture, Float fuzziness) :
    m_texture(texture), m_fuzziness(fuzziness) {}

const Texture* Metal::getTexture() const { return m_texture; }

std::optional<ScatterRecord> Metal::scatter(
  const Ray& ray, const Vec3f& normal, const Vec3f& intersectionPoint
) const {
    const auto reflectedDirection =
      reflect(normalize(ray.direction), normal)
      + m_fuzziness * randomUnitSphereVec3();
    return ScatterRecord{ reflectedDirection };
}

}  // namespace lm
