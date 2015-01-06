#pragma once

#include "card_view.hpp"
#include <deque>
#include <memory>

class actor;
class game_area;

class actor_area
{
public:
    actor_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::new_window<std::string> > chip_notation_area, const std::string& chip_notation);
    virtual ~actor_area()=0;

    virtual bool draw();
    virtual void set_hide_cards(bool hide);
    void new_deal(const std::shared_ptr<nctk::new_window<std::string> > deck_area);
    void push(std::shared_ptr<card_view> card);
    void sort_hand();           // 見栄え重視で挿入ソートする
    void adjust_exchange();

    virtual bool default_hide_setting()const = 0;
    virtual size_t hand_y_top()const = 0;

protected:
    game_area& whole()const;
    std::shared_ptr<const actor> model()const;

    std::deque<std::shared_ptr<card_view> > hand_;

private:
    game_area& whole_area_;
    std::shared_ptr<actor> model_;

    std::shared_ptr<nctk::new_window<std::string> > chip_notation_;
    std::shared_ptr<nctk::new_window<size_t> > chip_;
};
