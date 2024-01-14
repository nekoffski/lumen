#include "Lambertian.h"

namespace lm {

Lambertian::Lambertian(Texture* texture) : m_texture(texture) {}

Texture* Lambertian::getTexture() const { return m_texture; }

}  // namespace lm
