#pragma once

#include "../model/poker_mediator.hpp"
#include "../view/game_area.hpp"

class event_observer
{
public:
    event_observer();

    void play();

private:
    game_area game_area_;
    poker_mediator poker_;
};
