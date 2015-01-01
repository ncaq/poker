#pragma once

#include <memory>

class game_area;
class poker_mediator;
class event;

class event_manager
{
    friend event;

public:
    event_manager();

    void play();

private:
    std::shared_ptr<game_area> game_area_;
    std::shared_ptr<poker_mediator> poker_;
    std::unique_ptr<event> event_scene_;
};
