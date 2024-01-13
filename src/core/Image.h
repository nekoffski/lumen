#pragma once

#include <vector>

#include "Math.h"
#include "Core.h"

namespace lm {

class Image {
public:
    static constexpr u8 channels = 3;

    struct Properties {
        u64 width;
        u64 height;
    };

    explicit Image(const Properties& props);

    void set(const Coordinates<i64>& coords, const Vec3f& data);
    void save(const std::string& file) const;

private:
    Properties m_props;
    const u64 m_bufferSize;
    std::vector<u8> m_buffer;
};

}  // namespace lm
