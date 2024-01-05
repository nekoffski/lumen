#include "Camera.h"

namespace lm {

Camera::Camera(const Properties& props) :
    m_props(props), m_halfWidth(props.viewportWidth / 2.0f),
    m_halfHeight(props.viewportHeight / 2.0f) {}

Ray Camera::getRay(const Coordinates& coords) {
    const Float x = static_cast<Float>(coords.x) - m_halfWidth + 0.5f;
    const Float y = static_cast<Float>(coords.y) - m_halfHeight + 0.5f;
    const Float z = 1.0f;

    return Ray{
        m_props.position, Vec3f{x, -y, z}
    };
}

}  // namespace lm
