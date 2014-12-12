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

        size_t y(const size_t n)
        {
            mvwin(*this, n, x());
            return y_ = n;
        }

        size_t x(const size_t n)
        {
            mvwin(*this, y(), n);
            return x_ = n;
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
