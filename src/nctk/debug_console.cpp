#include "debug_console.hpp"

namespace nctk
{
    debug_console::debug_console()
    {
        if(!window)
        {
            window.reset(new new_window(3, 10, getmaxy(stdscr) - 3, getmaxx(stdscr) - 10));
        }
    }

    std::unique_ptr<basic_window> debug_console::window;
}
