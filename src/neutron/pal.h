#pragma once

#include <string>

namespace pal {
#if WIN32
    const wchar_t directory_separator = L'\\';
    const char directory_separator_utf8 = '\\';
#else
    const char directory_separator = '/';
#endif
};
