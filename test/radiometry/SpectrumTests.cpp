#include <gtest/gtest.h>

#include <algorithm>

#include <lumen/radiometry/Spectrum.hpp>

using namespace lumen::radiometry;

class SpectrumTests : public ::testing::Test {};

static constexpr float value = 1.0f;
static constexpr int samples = 4;
using Spectrum               = CoefficientSpectrum<4>;

TEST_F(SpectrumTests, whenCreatingSpectrum_shouldNotThrow) {
    ASSERT_NO_THROW({ Spectrum(value); });
}

TEST_F(SpectrumTests, givenSpectrum_whenCreating_shouldSetCorrectValues) {
    Spectrum spectrum(value);
    EXPECT_TRUE(std::all_of(spectrum.begin(), spectrum.end(), [](auto elem) {
        return elem == value;
    }));
}

TEST_F(SpectrumTests, givenDefaultCtor_whenCreatingSpectrum_shouldNotThrow) {
    ASSERT_NO_THROW({ Spectrum{}; });
}

TEST_F(SpectrumTests, givenSpectrum_whenCreatingWithDefaultCtor_shouldSetCorrectValues) {
    Spectrum spectrum{};
    EXPECT_TRUE(std::all_of(spectrum.begin(), spectrum.end(), [](auto elem) {
        return elem == 0.0f;
    }));
}

TEST_F(SpectrumTests, givenSpectrum_whenGettingSamplesCount_shouldMatch) {
    EXPECT_EQ(CoefficientSpectrum<1>::getSamplesCount(), 1);
    EXPECT_EQ(CoefficientSpectrum<7>::getSamplesCount(), 7);
    EXPECT_EQ(CoefficientSpectrum<11>::getSamplesCount(), 11);
}

TEST_F(SpectrumTests, givenSpectrum_whenTransformingToString_shouldReturnCorrectString) {
    EXPECT_EQ(Spectrum({1, 2, 3, 4}).toString(), "[1, 2, 3, 4]");
}

TEST_F(SpectrumTests, givenTwoSpectrums_whenAdding_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    Spectrum s2({4, 3, 2, 1});

    auto s = s1 + s2;

    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) + s2.getSample(i));
}

TEST_F(SpectrumTests, givenTwoSpectrums_whenSubstracting_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    Spectrum s2({4, 3, 2, 1});

    auto s = s1 - s2;

    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) - s2.getSample(i));
}

TEST_F(SpectrumTests, givenTwoSpectrums_whenMultiplying_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    Spectrum s2({4, 3, 2, 1});

    auto s = s1 * s2;

    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) * s2.getSample(i));
}

TEST_F(SpectrumTests, givenTwoSpectrums_whenDividing_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    Spectrum s2({4, 3, 2, 1});

    auto s = s1 / s2;

    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) / s2.getSample(i));
}

TEST_F(SpectrumTests, givenTwoSameSpectrums_whenComapring_shouldGiveCorrectResult) {
    EXPECT_TRUE(Spectrum({1, 2, 3, 4}) == Spectrum({1, 2, 3, 4}));
}

TEST_F(SpectrumTests, givenTwoDifferentSpectrums_whenComapring_shouldGiveCorrectResult) {
    EXPECT_TRUE(Spectrum({1, 2, 3, 4}) != Spectrum({1.1, 2, 3, 4}));
}

TEST_F(SpectrumTests, givenSpectrum_whenMultiplyingByNumber_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    lumen::math::Float value = 2.5f;

    auto s = s1 * value;
    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) * value);
}

TEST_F(SpectrumTests, givenSpectrum_whenDividingByNumber_shouldGiveCorrectResult) {
    Spectrum s1({1, 2, 3, 4});
    lumen::math::Float value = 2.5f;

    auto s = s1 / value;
    for (int i = 0; i < samples; ++i) EXPECT_EQ(s.getSample(i), s1.getSample(i) / value);
}
