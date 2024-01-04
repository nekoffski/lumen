#include <iostream>

#include <kc/core/Log.h>

int main() {
    kc::core::initLogging("lumen");

    LOG_TRACE("Hello world");

    return 0;
}
