#pragma once

#include "Material.h"
#include "texture/Texture.h"

namespace lm {

class Metal : public Material {
public:
    explicit Metal(Texture* texture, Float fuzziness);

    const Texture* getTexture() const override;

    std::optional<ScatterRecord> scatter(
      const Ray& ray, const Vec3f& normal, const Vec3f& intersectionPoint
    ) const override;

private:
    Texture* m_texture;
    Float m_fuzziness;
};

}  // namespace lm
