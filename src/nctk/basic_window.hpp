#pragma once

#include <curses.h>
#include <string>

namespace nctk
{
    class basic_window
    {
    public:
        basic_window(WINDOW* win);

        virtual ~basic_window() = 0;

        void echo(const std::string& str);
        void clear();
        char get_char();

        operator WINDOW*();
        operator const WINDOW*()const;

        void yx(const size_t y, const size_t x);
        void y(const size_t y);
        void x(const size_t x);
        size_t y()const;
        size_t x()const;
        size_t under()const;
        size_t right()const;

    private:
        WINDOW* window_ptr_;
    };
}
