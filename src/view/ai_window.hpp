#pragma once

#include "actor_window.hpp"

/*!
  ai用のパラメータ
 */
class ai_window : public actor_window
{
public:
    ai_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window);

    virtual bool default_hide_setting()const;
    virtual size_t hand_y_top()const;
};
