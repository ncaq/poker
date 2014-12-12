#include "new_window.hpp"
#include <curses.h>

namespace nctk
{
    new_window::new_window(const size_t lines, const size_t cols, const size_t y, const size_t x)
        :basic_window::basic_window(newwin(lines, cols, y, x), lines, cols, y, x)
    {
    }

    new_window::~new_window()
    {
    
    }
}
