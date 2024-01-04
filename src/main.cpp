#include <iostream>

#include <kc/core/Log.h>

#include "core/Core.h"
#include "core/Image.h"

int main() {
    kc::core::initLogging("lumen");

    lm::Image::Properties props{ .width = 800, .height = 600 };
    lm::Image image{ props };

    for (lm::u64 y = 0; y < props.height; ++y) {
        for (lm::u64 x = 0; x < props.width; ++x) {
            lm::Image::Coordinates coords{ .x = x, .y = y };
            image.set(coords, lm::Vec3f{ 1.0f, 0.0f, 0.0f });
        }
    }

    image.save("test.jpg");

    return 0;
}
