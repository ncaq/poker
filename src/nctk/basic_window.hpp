#pragma once

#include <curses.h>
#include <string>

namespace nctk
{
    class basic_window
    {
    public:
        basic_window(WINDOW* win, const size_t lines, const size_t cols, const size_t y, const size_t x);

        virtual ~basic_window() = 0;

        void add_string(const std::string& str);

        operator WINDOW*();

        void yx(const size_t y, const size_t x)
        {
            y_ = y;
            x_ = x;
            mvwin(*this, y_, x_);
        }
        
        size_t y(const size_t n)
        {
            yx(n, x_);
            return y_;
        }

        size_t x(const size_t n)
        {
            yx(y_, n);
            return x_;
        }
        
        size_t y()const
        {
            return y_;
        }

        size_t x()const
        {
            return x_;
        }

    private:
        WINDOW* window_ptr_;

        size_t width_, height_, y_, x_;
    };
}
