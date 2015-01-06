#pragma once

#include <memory>

class game_area;
class poker_mediator;

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
