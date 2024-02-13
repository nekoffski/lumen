#include "Renderer.h"

#include <kc/core/Clock.h>
#include <kc/async/TaskScheduler.hpp>
#include <kc/async/Utils.hpp>

#include "core/Math.h"

namespace lm {

Renderer::Renderer(const Properties& properties, Camera* camera) :
    m_props(properties), m_camera(camera),
    m_frameWidthNumeric(static_cast<Float>(properties.frameWidth)),
    m_frameHeightNumeric(static_cast<Float>(properties.frameHeight)),
    m_halfFrameWidth(m_frameWidthNumeric / 2.0f),
    m_halfFrameHeight(m_frameHeightNumeric / 2.0f) {}

Image Renderer::render(const RenderPacket& renderPacket) {
    lm::Image::Properties imageProps{
        .width = m_props.frameWidth, .height = m_props.frameHeight
    };
    lm::Image image{ imageProps };

    const auto renderRow = [&](i64 y) -> void {
        for (i64 x = 0; x < m_props.frameWidth; ++x) {
            lm::Coordinates<i64> coords{ .x = x, .y = y };

            Vec3f pixelColor{ 0.0f };

            for (i64 sample = 0; sample < m_props.samplesPerPixel; ++sample) {
                const auto ray = m_camera->getRay(toNDC(coords));
                pixelColor +=
                  traceRay(ray, renderPacket.world, m_props.recursionDepth);
            }
            image.set(
              coords, pixelColor / static_cast<Float>(m_props.samplesPerPixel)
            );
        }
    };

    kc::core::Clock clock;
    const auto start = clock.now();

    if (m_props.parallel) {
        kc::async::TaskScheduler ts;
        LOG_INFO("Rendering in parallel on {} threads", ts.getWorkerCount());

        kc::async::loop(ts, m_props.frameHeight, [&](uint64_t index) -> void {
            renderRow(static_cast<i64>(index));
        }).wait();
    } else {
        LOG_INFO("Rendering on single thread");
        for (i64 y = 0; y < m_props.frameHeight; ++y) renderRow(y);
    }

    const auto elapsed = clock.now() - start;
    LOG_INFO("Image rendered in: {}s", kc::core::toSeconds(elapsed));
    return image;
}

Float Renderer::getRandomThrottle() const {
    static constexpr Float range = 1.0f;
    static constexpr Float max   = range / 2.0f;
    static constexpr Float min   = -max;

    return random<Float>(min, max);
}

Coordinates<Float> Renderer::toNDC(const Coordinates<i64>& coordinates) {
    const auto shiftedX = coordinates.x - m_halfFrameWidth + getRandomThrottle();
    const auto shiftedY = coordinates.y - m_halfFrameHeight + getRandomThrottle();

    return Coordinates<Float>{
        .x = shiftedX / m_frameWidthNumeric, .y = shiftedY / m_frameHeightNumeric
    };
}

Vec3f Renderer::traceRay(const Ray& ray, Intersectable* world, u64 recursionDepth) {
    static Vec3f background{ 0.7f, 0.7f, 0.5f };

    if (recursionDepth <= 0) return Vec3f{ 0.0f };

    lm::Interval interval{ 0.0001f };

    if (auto intersection = world->intersect(ray, interval); intersection) {
        const auto color = intersection->getColor();

        if (auto scatterRecord = intersection->scatter(ray); scatterRecord) {
            Ray scatteredRay{
                intersection->intersectionPoint, scatterRecord->direction
            };
            return color * traceRay(scatteredRay, world, recursionDepth - 1);
        }
        return color;
    }
    return background;
}

}  // namespace lm
