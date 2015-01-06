#pragma once

#include "basic_window.hpp"

namespace nctk
{
    template<typename ShowAble>
    class new_window : public basic_window<ShowAble>
    {
    public:
        new_window(const size_t lines, const size_t cols, const size_t y, const size_t x, const std::shared_ptr<ShowAble> init = std::make_shared<ShowAble>())
            : basic_window<ShowAble>(newwin(lines, cols, y, x), init)
        {}

        virtual ~new_window()
        {}
    };
}
