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
            window->set_contents(message).draw();
            auto lvalue_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // bad know-how
            std::ofstream("error.log", std::ios::app)
                << std::ctime(&lvalue_time) <<
                ": debug_console" << std::endl
                << message << std::endl;
            return *this;
        }

        static std::unique_ptr<basic_window> window;
    };
}
