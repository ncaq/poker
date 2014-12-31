#pragma once

#include "actor.hpp"
#include <functional>

class player_area;

class player : public actor
{
public:
    player(player_area& player_input);
    virtual ~player();

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call();

private:
    player_area& player_input_;
};
