#pragma once

#include "new_window.hpp"
#include <string>

namespace nctk
{
    class form : public new_window<std::string>
    {
    public:
        form(const std::string& prompt_message)
            : new_window<std::string>(0, 0, getmaxy(stdscr) - 1, 0) // if 0 -> COLS - begin_x.
        {
            curs_set(1);
            this->set_contents(prompt_message);
            this->align_window();
            this->resize(this->height(), this->width() + 10);
            keypad(*this, true);
        }

        virtual ~form()
        {
            curs_set(0);
        }
    };
}
