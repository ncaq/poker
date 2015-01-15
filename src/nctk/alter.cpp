#include "alter.hpp"

namespace nctk
{
    bool utf8_char(const size_t c)
    {
        return c < 0xffffffffffffff80 || 0xffffffffffffffbf < c;
    }

    size_t size_utf8(const std::string& text)
    {
        return std::count_if(text.begin(), text.end(), utf8_char);
    }

    int stoi(const std::string& str, size_t* , int base)
    {
        return std::strtol(str.c_str(), nullptr, base);
    }

    std::vector<std::string> read_texture(const std::string& path)
    {
        std::ifstream file_stream(path);
        std::vector<std::string> result;
        std::string stash;
        while(std::getline(file_stream, stash))
        {
            result.push_back(stash);
        }
        return result;
    }
}
