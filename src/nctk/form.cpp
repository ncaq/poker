#include "form.hpp"
#include <curses.h>

namespace nctk
{
    form::form(const size_t y, const size_t x)
        :new_window::new_window(1, getmaxx(stdscr) - x, y, x)
    {
        keypad(*this, true);
    }

    form::~form()
    {
    }
}
