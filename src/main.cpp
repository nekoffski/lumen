#include <iostream>

#include <kc/core/Log.h>

#include "core/Core.h"
#include "core/Image.h"
#include "core/Camera.h"

int main() {
    kc::core::initLogging("lumen");

    constexpr lm::u64 width  = 100;
    constexpr lm::u64 height = 100;

    lm::Image::Properties imageProps{ .width = width, .height = height };
    lm::Image image{ imageProps };

    lm::Camera::Properties cameraProps{
        .viewportWidth  = width,
        .viewportHeight = height,
        .position       = lm::Vec3f{ 0.0f }
    };
    lm::Camera camera{ cameraProps };

    for (lm::i64 y = 0; y < height; ++y) {
        for (lm::i64 x = 0; x < width; ++x) {
            lm::Coordinates coords{ .x = x, .y = y };
            const auto ray = camera.getRay(coords);

            static constexpr float R = 50.0f;

            lm::Vec3f c1{ 0.0f, 1.0f, 0.0f };
            lm::Vec3f c2{ 1.0f, 0.0f, 0.0f };

            const auto d =
              ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;

            if (d <= R * R) {
                const auto dd = glm::sqrt(d) / R;

                image.set(coords, c1 * dd + (1.0f - dd) * c2);
            } else {
                image.set(coords, lm::Vec3f{ 1.0f, 1.0f, 1.0f });
            }
        }
    }

    image.save("test.jpg");

    return 0;
}
