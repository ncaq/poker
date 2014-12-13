#include "card.hpp"
#include "nctk/box.hpp"
#include <curses.h>
#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

int main()
{
    initscr();

    nctk::box<card> b(nctk::box<card>(card(suit::spade, 1), 0, 0));
    b.draw();
    refresh();
    usleep(100000);
    b.moving_draw(100, 100);
    
    refresh();
    usleep(100000);
    endwin();
}
