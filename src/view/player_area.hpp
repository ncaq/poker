#pragma once

#include "actor_area.hpp"

class player_area : public actor_area
{
public:
    player_area(game_area& whole_area_);
    std::deque<bool> select_changing_cards();
    size_t raise();
    bool call();
};
