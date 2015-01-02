#pragma once

#include "../model/poker_mediator.hpp"
#include "../view/game_area.hpp"
#include <memory>

class event_manager
{
public:
    event_manager();

    void play();

    std::shared_ptr<game_area> gui();
    std::shared_ptr<poker_mediator> poker();

private:
    std::shared_ptr<game_area> game_area_;
    std::shared_ptr<poker_mediator> poker_;
};
