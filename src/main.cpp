#include "controller/event_manager.hpp"
#include "nctk/debug_stream.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try
    {
        initscr();
        curs_set(0);

        event_manager game;
        game.play();
    }
    catch(const std::exception& e)
    {
        nctk::debug_stream() << "exception: " << typeid(e).name() << std::endl
                             << e.what() << std::endl;
        endwin();
        throw;
    }
    catch(...)
    {
        nctk::debug_stream() << "unclear error" << std::endl;
        endwin();
        throw;
    }
    endwin();
}
