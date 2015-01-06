#pragma once

#include "actor_area.hpp"

class player_area : public actor_area
{
public:
    player_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::new_window<std::string> > chip_area);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call(const size_t ai_pool);

    virtual void set_hide_cards(bool);
    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
