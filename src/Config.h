#pragma once

#include "core/Core.h"

namespace lm {

struct Config {
    u64 width;
    u64 height;
    u64 recursionDepth;
    u64 samplesPerPixel;
    Float fov;
    std::string output;
    bool parallel;
    bool random;

    std::optional<std::string> inputPath;
};

}  // namespace lm
