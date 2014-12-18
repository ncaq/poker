#include "form.hpp"
#include <curses.h>

namespace nctk
{
    form::form(const size_t y, const size_t x)
        : new_window::new_window(1, 0, y, x) // if 0 -> COLS - begin_x.
    {
        keypad(*this, true);
    }

    form::~form()
    {
    }
}
