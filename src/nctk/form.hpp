#pragma once

#include "new_window.hpp"
#include <string>

namespace nctk
{
    class form : public new_window<std::string>
    {
    public:
        form(const std::string& prompt_message)
            : new_window<std::string>(1, 0, getmaxy(stdscr), 0) // if 0 -> COLS - begin_x.
        {
            this->set_contents(prompt_message);
            keypad(*this, true);
        }

        virtual ~form(){}
    };
}
