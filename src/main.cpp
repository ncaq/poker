#include "controller/event_manager.hpp"
#include "nctk/debug_stream.hpp"
#include <clocale>
#include <fstream>
#include <iostream>
#include <string>

int main()                      //!< main関数は例外キャッチ用です.event_managerがメイン処理をします
{
    std::setlocale(LC_ALL, ""); //! 特定の環境でutf-8表示するのに必要

    try
    {
        event_manager game;
        game.play();
    }
    catch(const std::exception& e)
    {
        nctk::debug_stream() << "exception: " << typeid(e).name() << std::endl
                             << e.what() << std::endl;

        std::cerr << e.what() << std::endl;
        throw;
    }
    catch(...)
    {
        nctk::debug_stream() << "unclear error" << std::endl;
        throw;
    }
}
