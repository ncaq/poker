#pragma once

#include "actor_area.hpp"

class ai_area : public actor_area
{
public:
    ai_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::new_window<std::string> > chip_area);

    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
