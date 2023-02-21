#pragma once

#include <cmath>
#include <cstdint>

#include <sstream>
#include <array>
#include <ranges>
#include <algorithm>

#include "lumen/core/Log.h"
#include "lumen/math/Float.h"

// https://github.com/mmp/pbrt-v3/blob/master/src/core/spectrum.h

namespace lumen::radiometry {

template <uint8_t samples> class CoefficientSpectrum {
   public:
    explicit CoefficientSpectrum(math::Float value = 0.0f) {
        m_samples.fill(value);
        LASSERT(not hasNaNs());
    }

    CoefficientSpectrum(std::initializer_list<math::Float> values) {
        LASSERT(values.size() == samples);
        std::ranges::copy(values, m_samples.begin());
    }

    CoefficientSpectrum(const CoefficientSpectrum &oth) {
        LASSERT(not oth.hasNaNs());
        std::ranges::copy(oth.m_samples, m_samples.begin());
    }

    std::string toString() const {
        std::stringstream stream;
        stream << "[";

        for (const auto &elem : m_samples) stream << elem << ", ";

        auto str = stream.str();
        return str.substr(0, str.size() - 2) + "]";
    }

    static int getSamplesCount() { return samples; }

    bool hasNaNs() const {
        return std::ranges::any_of(m_samples, [](const auto &elem) { return std::isnan(elem); });
    }

    auto begin() { return m_samples.begin(); }
    auto end() { return m_samples.end(); }

    const auto cbegin() const { return m_samples.cbegin(); }
    const auto cend() const { return m_samples.cend(); }

    math::Float &getSample(uint8_t sample) {
        LASSERT(sample <= samples);
        return m_samples[sample];
    }

    math::Float getSample(uint8_t sample) const {
        LASSERT(sample <= samples);
        return m_samples[sample];
    }

    CoefficientSpectrum &operator+=(const CoefficientSpectrum &oth) {
        LASSERT(!oth.hasNaNs());
        for (int i = 0; i < samples; ++i) m_samples[i] += oth.m_samples[i];
        return *this;
    }

    CoefficientSpectrum operator+(const CoefficientSpectrum &oth) const {
        LASSERT(!oth.hasNaNs());
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] += oth.m_samples[i];
        return ret;
    }

    CoefficientSpectrum operator-(const CoefficientSpectrum &oth) const {
        LASSERT(!oth.hasNaNs());
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] -= oth.m_samples[i];
        return ret;
    }

    CoefficientSpectrum operator/(const CoefficientSpectrum &oth) const {
        LASSERT(!oth.hasNaNs());
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) {
            LASSERT(oth.m_samples[i] != 0);
            ret.m_samples[i] /= oth.m_samples[i];
        }
        return ret;
    }

    CoefficientSpectrum operator*(const CoefficientSpectrum &sp) const {
        LASSERT(!sp.hasNaNs());
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] *= sp.m_samples[i];
        return ret;
    }

    CoefficientSpectrum &operator*=(const CoefficientSpectrum &sp) {
        LASSERT(!sp.hasNaNs());
        for (int i = 0; i < samples; ++i) m_samples[i] *= sp.m_samples[i];
        return *this;
    }

    CoefficientSpectrum operator*(math::Float a) const {
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] *= a;
        LASSERT(!ret.hasNaNs());
        return ret;
    }

    CoefficientSpectrum &operator*=(math::Float a) {
        for (int i = 0; i < samples; ++i) m_samples[i] *= a;
        LASSERT(!hasNaNs());
        return *this;
    }

    CoefficientSpectrum operator/(math::Float a) const {
        LASSERT(a != 0 && !std::isnan(a));
        CoefficientSpectrum ret = *this;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] /= a;
        LASSERT(!ret.hasNaNs());
        return ret;
    }

    CoefficientSpectrum &operator/=(math::Float a) {
        LASSERT(a != 0 && !std::isnan(a));
        for (int i = 0; i < samples; ++i) m_samples[i] /= a;
        return *this;
    }

    bool operator==(const CoefficientSpectrum &sp) const {
        for (int i = 0; i < samples; ++i)
            if (m_samples[i] != sp.m_samples[i]) return false;
        return true;
    }

    bool operator!=(const CoefficientSpectrum &sp) const { return not(*this == sp); }

    bool isBlack() const {
        return std::ranges::any_of(m_samples, [](const auto sample) { return sample != 0; });
    }

    CoefficientSpectrum sqrt() const {
        CoefficientSpectrum ret;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] = std::sqrt(m_samples[i]);
        LASSERT(!ret.hasNaNs());
        return ret;
    }

    CoefficientSpectrum pow(math::Float e) const {
        CoefficientSpectrum ret;
        for (int i = 0; i < samples; ++i) ret.c[i] = std::pow(m_samples[i], e);
        LASSERT(!ret.HasNaNs());
        return ret;
    }

    CoefficientSpectrum operator-() const {
        CoefficientSpectrum ret;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] = -m_samples[i];
        return ret;
    }

    friend CoefficientSpectrum exp(const CoefficientSpectrum &s) {
        CoefficientSpectrum ret;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] = std::exp(s.m_samples[i]);
        LASSERT(!ret.hasNaNs());
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const CoefficientSpectrum &s) {
        return os << s.toString();
    }

    CoefficientSpectrum clamp(math::Float low = 0, math::Float high = INFINITY) const {
        CoefficientSpectrum ret;
        for (int i = 0; i < samples; ++i) ret.m_samples[i] = std::clamp(m_samples[i], low, high);
        LASSERT(!ret.hasNaNs());
        return ret;
    }

    math::Float maxComponentValue() const { return *std::ranges::max_element(m_samples); }

   private:
    std::array<math::Float, samples> m_samples;
};

}  // namespace lumen::radiometry
