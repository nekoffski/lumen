#pragma once

#include <optional>

#include <boost/program_options.hpp>

#include "core/Core.h"
#include "Config.h"

namespace lm {

namespace po = boost::program_options;

class Input {
public:
    explicit Input(int argc, char** argv);

    std::optional<Config> getConfig() &&;

private:
    Config m_config;

    po::options_description m_optionsDescription;
    po::variables_map m_vm;
};

}  // namespace lm
