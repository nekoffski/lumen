#include "Image.h"

#include <kc/core/Log.h>
#include <stb_write.h>

namespace lm {

Image::Image(const Properties& props) :
    m_props(props), m_bufferSize(props.width * props.height * channels),
    m_buffer(m_bufferSize) {}

static Float applyGammaCorrection(Float value, Float gamma = 2.2f) {
    return std::pow(value, 1.0f / gamma);
}

void Image::set(const Coordinates<i64>& coords, const Vec3f& data) {
    const auto coordinate =
      ((m_props.height - coords.y - 1) * m_props.width + coords.x) * channels;
    ASSERT(
      coordinate + channels - 1 < m_bufferSize,
      "Tried to write outside of the buffer"
    );

    constexpr static Float gamma = 2.0f;

    for (u8 channel = 0; channel < channels; ++channel) {
        m_buffer[coordinate + channel] =
          static_cast<u8>(applyGammaCorrection(data[channel], gamma) * 255.999f);
    }
}

void Image::save(const std::string& file) const {
    const auto result = stbi_write_jpg(
      file.c_str(), m_props.width, m_props.height, channels, m_buffer.data(), 100
    );
    ASSERT(result != 0, "Could not save image");
}

}  // namespace lm
