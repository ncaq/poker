#pragma once

#include "window.hpp"
#include <string>

namespace nctk
{
    class form : public window
    {
    public:
        form(const std::string& prompt_message)
            : window(0, 0, getmaxy(stdscr) - 1, 0) // if 0 -> COLS - begin_x.
        {
            curs_set(1);
            this->set_contents(prompt_message);
            keypad(*this, true);
        }

        virtual ~form()
        {
            curs_set(0);
        }
    };
}
