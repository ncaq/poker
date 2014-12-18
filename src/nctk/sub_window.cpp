#include "sub_window.hpp"

namespace nctk
{
    sub_window::sub_window(WINDOW* origin, const size_t lines, const size_t cols, const size_t y, const size_t x)
        :basic_window::basic_window(subwin(origin, lines, cols, y, x))
    {
        parent_window_ptr = origin;
    }

    sub_window::~sub_window()
    {
    
    }
}
