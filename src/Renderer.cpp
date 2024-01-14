#include "Renderer.h"

#include "core/Math.h"

namespace lm {

Renderer::Renderer(const Properties& properties, Camera* camera) :
    m_props(properties), m_camera(camera),
    m_frameWidthNumeric(static_cast<Float>(properties.frameWidth)),
    m_frameHeightNumeric(static_cast<Float>(properties.frameHeight)),
    m_halfFrameWidth(m_frameWidthNumeric / 2.0f),
    m_halfFrameHeight(m_frameHeightNumeric / 2.0f) {}

Image Renderer::render(const Scene& scene) {
    lm::Image::Properties imageProps{
        .width = m_props.frameWidth, .height = m_props.frameHeight
    };
    lm::Image image{ imageProps };

    for (i64 y = 0; y < m_props.frameHeight; ++y) {
        for (i64 x = 0; x < m_props.frameWidth; ++x) {
            lm::Coordinates<i64> coords{ .x = x, .y = y };
            const auto ray   = m_camera->getRay(toNDC(coords));
            const auto color = traceRay(ray, scene.world, m_props.recursionDepth);
            image.set(coords, color);
        }
    }
    return image;
}

Coordinates<Float> Renderer::toNDC(const Coordinates<i64>& coordinates) {
    return Coordinates<Float>{
        .x = (coordinates.x - m_halfFrameWidth) / m_frameWidthNumeric,
        .y = (coordinates.y - m_halfFrameHeight) / m_frameHeightNumeric
    };
}

Vec3f Renderer::traceRay(
  const Ray& ray, const Intersectable& world, u64 recursionDepth
) {
    static Vec3f background{ 0.3f, 0.4f, 0.5f };

    if (recursionDepth <= 0) return background;

    lm::Interval interval{ 0.0001f };
    if (auto record = world.intersect(ray, interval); record) {
        const auto newDirection = randomUnitHemisphereVec3(record->normal);
        Ray ray{ record->intersectionPoint, newDirection };

        return record->getColor() * traceRay(ray, world, recursionDepth - 1);
    }
    return background;
}

}  // namespace lm
