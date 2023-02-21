#pragma once

#include <kc/core/Log.h>

namespace lumen::core {

void initLogger();

#define LASSERT(x) ASSERT(x, "Assertion failed {}:{} - {}(...)", __FILE__, __LINE__, __func__)

}  // namespace lumen::core