#pragma once

#include "new_window.hpp"
#include "sub_window.hpp"
#include <curses.h>
#include <memory>

namespace nctk
{
    template <typename T>
    class box
    {
    public:
        box(const T& c, const size_t y, const size_t x)
            :contents_(c), draw_area_(new sub_window(stdscr, contents_.width(), contents_.height(), y, x))
        {
        }

        void draw()const
        {
            draw_area_->add_string(contents_.to_string());
        }

    private:
        const T& contents_;

        std::unique_ptr<basic_window> draw_area_;
    };
}
