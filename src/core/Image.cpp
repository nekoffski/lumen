#include "Image.h"

#include <kc/core/Log.h>
#include <stb_write.h>

namespace lm {

Image::Image(const Properties& props) :
    m_props(props), m_bufferSize(props.width * props.height * channels),
    m_buffer(m_bufferSize) {}

void Image::set(const Coordinates& coords, const Vec3f& data) {
    const auto coordinate = (coords.y * m_props.width + coords.x) * channels;
    ASSERT(
      coordinate + channels - 1 < m_bufferSize,
      "Tried to write outside of the buffer"
    );
    for (u8 channel = 0; channel < channels; ++channel) {
        m_buffer[coordinate + channel] = static_cast<u8>(data[channel] * 255.999f);
    }
}

void Image::save(const std::string& file) {
    const auto result = stbi_write_jpg(
      file.c_str(), m_props.width, m_props.height, channels, m_buffer.data(), 100
    );
    ASSERT(result != 0, "Could not save image");
}

}  // namespace lm
