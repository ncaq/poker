#pragma once

#include "actor_area.hpp"

class player_area : public actor_area
{
public:
    player_area(game_area& whole_area, std::shared_ptr<const actor> m);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call();

    virtual void set_hide_cards(bool);
    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
