#pragma once

#include "../nctk/window.hpp"
#include "../nctk/window_list.hpp"
#include "card_window.hpp"
#include <deque>
#include <memory>

class actor;
class main_window;

/*!
  手札の管理
 */
class actor_window : public nctk::window
{
public:
    actor_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window, const std::string& chip_description);
    virtual ~actor_window()=0;

    void new_deal();
    void adjust_exchange();
    void sort_hand();           //!< 見栄え重視で挿入ソートする
    std::string show_down()const;
    virtual void set_hide_cards(bool hide);

    virtual bool default_hide_setting()const = 0;
    virtual size_t hand_y_top()const = 0;

    const actor& model()const;

protected:
    actor& model_;
    main_window& whole_;
    std::shared_ptr<nctk::window_list<card_window> > hand_; //!< window_selecterにdequeを渡す必要があるので別に持っておく
};
