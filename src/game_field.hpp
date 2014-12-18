#pragma once

#include "card_view.hpp"
#include "nctk/new_window.hpp"
#include "nctk/window_selecter_horizontally.hpp"
#include "undefined_card_view.hpp"
#include <deque>
#include <memory>

class game_field
{
public:
    game_field();

    void draw();

    void reset(const std::deque<std::shared_ptr<card> >& cs);
    std::deque<bool> selected_array_IO();

private:
    void push(const std::shared_ptr<card>& c);
    void swap(const card& c, const size_t index); // todo:

    undefined_card_view deck_area_; // ハリボテ
    std::deque<std::shared_ptr<card_view> > hand_area_; // 手札
    nctk::new_window description_;            // 操作説明
};

void test_selected_array_IO();
