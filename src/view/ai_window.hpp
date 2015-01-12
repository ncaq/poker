#pragma once

#include "actor_window.hpp"

class ai_window : public actor_window
{
public:
    ai_window(main_window& whole_window, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_window);

    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
