#include "controller/event_manager.hpp"
#include <fstream>
#include <iostream>
#include <string>
// #include "nctk/debug_stream.hpp"

int main()
{
    // 特定の環境でutf-8表示するのに必要
    setlocale(LC_ALL, "");

    try
    {
        event_manager game;
        game.play();
    }
    catch(const std::exception& e)
    {
        // nctk::debug_stream() << "exception: " << typeid(e).name() << std::endl
        //                      << e.what() << std::endl;

        std::cerr << e.what() << std::endl;
        throw;
    }
    catch(...)
    {
        // nctk::debug_stream() << "unclear error" << std::endl;
        throw;
    }
}
