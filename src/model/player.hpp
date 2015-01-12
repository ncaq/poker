#pragma once

#include "actor.hpp"
#include <functional>

class player_window;

class player : public actor
{
public:
    void set_controller(std::shared_ptr<player_window> controller);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call(const size_t enemy_pool);

private:
    std::shared_ptr<player_window> player_input_;
};
