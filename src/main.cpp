#include "card.hpp"
#include "nctk/box.hpp"
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

        nctk::box<card> b(nctk::box<card>(card(suit::spade, 1), 0, 0));
        b.draw();
        refresh();
        usleep(100000);
        b.moving_draw(20, 20);
    
        refresh();
        usleep(100000);
    }
    catch(const std::exception& e)
    {
        cerr                  << "exception: " << typeid(e).name() << endl << e.what() << endl;
        ofstream("error.log") << "exception: " << typeid(e).name() << endl << e.what() << endl;

        sleep(1);
        endwin();
        throw;
    }
    sleep(10);
    endwin();
}
