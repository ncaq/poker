#pragma once

#include "actor.hpp"
#include <functional>

class player_area;

class player : public actor
{
public:
    void set_controller(std::shared_ptr<player_area> controller);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call();

private:
    std::shared_ptr<player_area> player_input_;
};
