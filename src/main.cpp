#include "event_manager.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    try
    {
        initscr();

        event_manager game;
        game.play();

        mvaddstr(0, 0, "test");

        usleep(1000000);
    }
    catch(const std::exception& e)
    {
        cerr                  << "exception: " << typeid(e).name() << endl << e.what() << endl;
        ofstream("error.log", std::ios::app) << "exception( " << time << "): "  << std::endl << typeid(e).name() << endl << e.what() << endl;

        sleep(1);
        endwin();
        throw;
    }
    usleep(1000000);
    endwin();
}
