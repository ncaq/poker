#include "event_manager.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

int main()
{
    setlocale(LC_ALL, "");

    try
    {
        initscr();

        event_manager game;
        game.play();
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception: " << typeid(e).name() << std::endl
                  << e.what() << std::endl;

        auto lvalue_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::ofstream("error.log", std::ios::app)
            << std::ctime(&lvalue_time) << ": "  << std::endl
            << typeid(e).name() << std::endl
            << e.what() << std::endl;

        endwin();
        throw;
    }
    catch(...)
    {
        std::cerr << "exception: " << std::endl
                  << "unclear error" << std::endl;

        auto lvalue_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::ofstream("error.log", std::ios::app)
            << std::ctime(&lvalue_time) << ": " << std::endl
            << "unclear error" << std::endl;

        endwin();
        throw;
    }
    usleep(100000);
    endwin();
}
