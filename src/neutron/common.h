#pragma once

#include <string>
#include <fstream>
#include <algorithm>
#include <string>
#include <list>

#include "pal.h"
#include "include/cef_base.h"

constexpr const char16* operator "" _x(const char16_t* lit, std::size_t size) {
    return (const char16*)lit;
}
