#include "form.hpp"
#include <curses.h>

namespace nctk
{
    form::form(const std::string& prompt_message)
        : new_window::new_window(1, 0, getmaxy(stdscr), 0) // if 0 -> COLS - begin_x.
    {
        this->set_contents(prompt_message);
        keypad(*this, true);
    }

    form::~form()
    {
    }
}
