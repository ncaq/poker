#pragma once

#include "actor_window.hpp"

class player_window : public actor_window
{
public:
    player_window(main_window& whole_window, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_window);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call(const size_t ai_pool);

    virtual void set_hide_cards(bool);
    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
