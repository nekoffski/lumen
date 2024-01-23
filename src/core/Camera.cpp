#include "Camera.h"

#include "core/Math.h"

namespace lm {

Camera::Camera(const Properties& props) : m_props(props) {
    auto theta           = glm::radians(props.verticalFOV);
    auto h               = std::tan(theta / 2);
    Float viewportHeight = 2.0f * h;
    Float viewportWidth  = m_props.aspectRatio * viewportHeight;

    m_w = normalize(props.position - props.target);
    m_u = normalize(cross(Vec3f{ 0.0, 1.0f, 0.0f }, m_w));
    m_v = cross(m_w, m_u);

    auto focal_length = 1.0f;

    m_horizontal = props.focusDistance * viewportWidth * m_u;
    m_vertical   = props.focusDistance * viewportHeight * m_v;
    m_center     = props.position - props.focusDistance * m_w;
}

Ray Camera::getRay(const Coordinates<Float>& coords) {
    const auto direction =
      m_center + coords.y * m_vertical + coords.x * m_horizontal - m_props.position;
    return Ray{ m_props.position, direction };
}

}  // namespace lm
