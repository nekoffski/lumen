#pragma once

#include "Texture.h"

namespace lm {

class SolidColor : public Texture {
public:
    explicit SolidColor(const Vec3f& color);
    explicit SolidColor(Float r, Float g, Float b);
    explicit SolidColor(Float c);

    Vec3f getColor(const Coordinates<Float>& uv) const override;

private:
    Vec3f m_color;
};

}  // namespace lm