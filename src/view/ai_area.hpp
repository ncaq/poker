#pragma once

#include "actor_window.hpp"

class ai_area : public actor_window
{
public:
    ai_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_area);

    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
