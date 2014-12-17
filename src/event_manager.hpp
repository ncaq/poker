#pragma once

#include "game_field.hpp"
#include "poker_manager.hpp"

class event_manager
{
public:
    void play();

private:
    poker_manager poker;
    game_field field;
};
