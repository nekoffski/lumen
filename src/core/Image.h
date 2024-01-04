#pragma once

#include <vector>

#include <kc/core/Log.h>
#include <stb_write.h>

#include "Math.h"

namespace lm {

class Image {
public:
    static constexpr u8 channels = 3;

    struct Properties {
        u64 width;
        u64 height;
    };

    struct Coordinates {
        u64 x;
        u64 y;
    };

    explicit Image(const Properties& props) :
        m_props(props), m_bufferSize(props.width * props.height * channels),
        m_buffer(m_bufferSize) {}

    void set(const Coordinates& coords, const Vec3f& data) {
        const auto coordinate = (coords.y * m_props.width + coords.x) * channels;
        ASSERT(
          coordinate + channels - 1 < m_bufferSize,
          "Tried to write outside of the buffer"
        );
        for (u8 channel = 0; channel < channels; ++channel) {
            m_buffer[coordinate + channel] =
              static_cast<u8>(data[channel] * 255.999f);
        }
    }

    void save(const std::string& file) {
        const auto result = stbi_write_jpg(
          file.c_str(), m_props.width, m_props.height, channels, m_buffer.data(), 100
        );
        ASSERT(result != 0, "Could not save image");
    }

private:
    Properties m_props;
    const u64 m_bufferSize;
    std::vector<u8> m_buffer;
};

}  // namespace lm
