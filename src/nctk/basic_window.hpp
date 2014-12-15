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

        void yx(const size_t y, const size_t x);
        size_t y(const size_t n);
        size_t x(const size_t n);
        size_t y()const;
        size_t x()const;
        size_t under()const;
        size_t right()const;

    private:
        WINDOW* window_ptr_;

        size_t height_, width_, y_, x_;
    };
}
