/*!
  @file alter.hpp
  cygwinのgccがバグってるのでto_stringを適当に再実装
  後は何処に置けばよいかわからないようなutils
*/

#pragma once

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace nctk
{
    bool utf8_char(const size_t c);
    size_t size_utf8(const std::string& text);
    int stoi(const std::string& str, size_t* idx = nullptr, int base = 10);
    std::vector<std::string> read_texture(const std::string& path);

    template<typename ToBeString>
    std::string to_string(const ToBeString& tbs)
    {
        std::stringstream ss;
        ss << tbs;
        return ss.str();
    }
}
