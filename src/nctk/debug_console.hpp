#pragma once

#include "new_window.hpp"
#include <curses.h>
#include <fstream>
#include <memory>
#include <string>

namespace nctk
{
    class debug_console
    {
    public:
        debug_console();

        const debug_console& operator<<(const std::string& message)const // todo: iostream的にする
        {
            window->echo(message);
            std::ofstream("error.log", std::ios::app) << "debug_console( " << time << "): " << message << std::endl;
            return *this;
        }

        static std::unique_ptr<basic_window> window;
    };
}
