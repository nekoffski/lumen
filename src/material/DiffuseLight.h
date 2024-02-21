#pragma once

#include "Material.h"

#include "core/Core.h"
#include "core/Math.h"

namespace lm {

class DiffuseLight : public Material {
public:
    explicit DiffuseLight(Texture* lightSource) : m_lightSource(lightSource) {}

    Vec3f getEmittedColor(
      const Coordinates<Float>& uv, [[maybe_unused]] const Vec3f& hitPoint
    ) const override {
        return m_lightSource->getColor(uv);
    }

    const Texture* getTexture() const override { return m_lightSource; }

    std::optional<ScatterRecord> scatter(
      [[maybe_unused]] const Ray& ray, [[maybe_unused]] const Vec3f& normal,
      [[maybe_unused]] const Vec3f& intersectionPoint
    ) const {
        return {};
    }

private:
    Texture* m_lightSource;
};

}  // namespace lm