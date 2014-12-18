#pragma once

#include "game_field.hpp"
#include "game_manager.hpp"

class event_manager
{
public:
    void play();

private:
    game_manager poker;
    game_field field;
};
