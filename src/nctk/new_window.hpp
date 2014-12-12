#pragma once

#include "basic_window.hpp"

namespace nctk
{
    class new_window : public basic_window
    {
    public:
        new_window(const size_t lines, const size_t cols, const size_t y, const size_t x);

        virtual ~new_window();
    };
}
