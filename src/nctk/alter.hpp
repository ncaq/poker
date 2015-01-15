#pragma once

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace nctk
{
    bool utf8_char(const size_t c);
    size_t size_utf8(const std::string& text);
    std::vector<std::string> read_texture(const std::string& path);

    template<typename ToBeString>
    std::string to_string(const ToBeString& tbs)
    {
        std::stringstream ss;
        ss << tbs;
        return ss.str();
    }
}
