#pragma once

#include "curses_field.hpp"
#include "poker_manager.hpp"

class event_manager
{
public:
    void play();
    
private:
    poker_manager poker;
    curses_field field;
};
