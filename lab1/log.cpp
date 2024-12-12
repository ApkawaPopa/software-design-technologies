#include "log.h"

#include <iostream>

void log(const std::wstring &&message) {
    std::wcout << message << std::endl;
}