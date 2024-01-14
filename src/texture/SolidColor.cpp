#include "SolidColor.h"

namespace lm {

SolidColor::SolidColor(const Vec3f& color) : m_color(color) {}
SolidColor::SolidColor(Float r, Float g, Float b) : m_color(r, g, b) {}
SolidColor::SolidColor(Float c) : m_color(c) {}

Vec3f SolidColor::getColor([[maybe_unused]] const Coordinates<Float>& uv) const {
    return m_color;
}

}  // namespace lm
