#pragma once

#include "actor_window.hpp"

class player_window : public actor_window
{
public:
    player_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window);

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call(const size_t ai_pool);

    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
