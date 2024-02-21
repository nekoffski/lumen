#pragma once

#include <optional>

#include "core/Core.h"
#include "core/Ray.h"
#include "texture/Texture.h"

namespace lm {

struct ScatterRecord {
    Vec3f direction;
};

struct Material {
    virtual const Texture* getTexture() const = 0;
    virtual std::optional<ScatterRecord> scatter(
      const Ray& ray, const Vec3f& normal, const Vec3f& intersectionPoint
    ) const = 0;
    // no-emitting material by default
    virtual Vec3f getEmittedColor(
      const Coordinates<Float>& uv, const Vec3f& hitPoint
    ) const {
        return Vec3f{ 0.0f };
    }
};

}  // namespace lm
