#include "Input.h"

#include <iostream>

namespace lm {

constexpr u64 defaultWidth           = 600;
constexpr u64 defaultHeight          = 600;
constexpr u64 defaultRecursionDepth  = 8;
constexpr u64 defaultSamplesPerPixel = 8;
constexpr bool defaultParallel       = false;
constexpr bool defaultRandom         = false;

static const std::string defaultOutput = "out.jpg";

Input::Input(int argc, char** argv) {
    m_optionsDescription.add_options()("help", "Print help")(
      "width", po::value<u64>(&m_config.width)->default_value(defaultWidth),
      "Output image width"
    )("height", po::value<u64>(&m_config.height)->default_value(defaultHeight),
      "Output image height"
    )("recursionDepth",
      po::value<u64>(&m_config.recursionDepth)->default_value(defaultRecursionDepth),
      "Max ray tracing recursion depth"
    )("samplesPerPixel",
      po::value<u64>(&m_config.samplesPerPixel)
        ->default_value(defaultSamplesPerPixel),
      "Ray samples casted by pixel"
    )("output",
      po::value<std::string>(&m_config.output)->default_value(defaultOutput),
      "Output image path"
    )("scene", po::value<std::string>(), "Scene path to render"
    )("parallel",
      po::bool_switch(&m_config.parallel)->default_value(defaultParallel),
      "Render on multiple cores"
    )("random", po::bool_switch(&m_config.random)->default_value(defaultRandom),
      "Use randomly generated scene");

    po::store(po::parse_command_line(argc, argv, m_optionsDescription), m_vm);
    po::notify(m_vm);
}

std::optional<Config> Input::getConfig() && {
    if (m_vm.contains("help")) {
        std::cout << "Usage:\n";
        std::cout << m_optionsDescription;
        return {};
    }
    m_config.fov = static_cast<Float>(m_config.width) / m_config.height;

    if (not m_config.random) {
        if (not m_vm.contains("scene")) {
            std::cout
              << "Input scene path missing, provide scene to render or use --random to generate random one\n";
            return {};
        }
        m_config.inputPath = m_vm["scene"].as<std::string>();
    }
    return m_config;
}

}  // namespace lm