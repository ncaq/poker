#include "card.hpp"
#include "nctk/box.hpp"
#include <curses.h>
#include <unistd.h>
#include <vector>

using namespace std;

int main()
{
    initscr();
    
    // vector<nctk::box<card>> cs;
    // cs.push_back(nctk::box<card>(card(suit::spade, 1), 0, 0));
    // cs.push_back(card(suit::spade, 1));
    // cs.push_back(card(suit::spade, 1));

    // size_t cy = 0, cx = 0;
    // for(const auto& c : cs)
    // {
    //     c.draw();
    //     // cy = c.ey();
    //     // cx = c.ex();
    // }

    nctk::box<card>(card(suit::spade, 1), 10, 10).draw();
    
    refresh();
    sleep(1);
    endwin();
}
