#pragma once

#include "../nctk/window.hpp"
#include "card_window.hpp"
#include <deque>
#include <memory>

class actor;
class main_window;

class actor_window : public nctk::window
{
public:
    actor_window(main_window& whole_window, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_notation_window, const std::string& chip_description);
    virtual ~actor_window()=0;

    void new_deal(const std::shared_ptr<nctk::window> deck_window);
    void adjust_exchange();
    void sort_hand();           //!< 見栄え重視で挿入ソートする

    std::string show_down()const;

    virtual void set_hide_cards(bool hide);
    virtual bool default_hide_setting()const = 0;
    virtual size_t hand_y_top()const = 0;

    std::shared_ptr<const actor> model()const;

protected:
    main_window& whole()const;
    std::shared_ptr<card_window> lookup_card(const size_t index);
    void push_card(std::shared_ptr<card_window> card);
    void clear_hand();

    std::deque<std::shared_ptr<card_window> > hand_; //!< window_selecterにdequeを渡す必要があるので別に持っておく

private:
    main_window& whole_window_;
    std::shared_ptr<actor> model_;
};
