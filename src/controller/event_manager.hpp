#pragma once

#include "../model/poker_mediator.hpp"
#include "../view/game_area.hpp"

class event_manager
{
public:
    event_manager();

    void play();

private:
    game_area game_area_;
    poker_mediator poker_;
};
