#pragma once

#include <string>
#include <vector>

namespace nctk
{
    class window;

    class display
    {
    public:
        void flush();

    private:
        std::vector<std::string> buffer_;
        size_t lines_;
        size_t cols_;
    };
}
