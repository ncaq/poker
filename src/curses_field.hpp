#pragma once

#include "card.hpp"
#include "nctk/box.hpp"
#include "nctk/box_cursors.hpp"
#include "undefined_card.hpp"
#include <vector>

class curses_field
{
public:
    curses_field();

    void draw();

    void deal(const std::vector<card>& cs);
    void push(const card& c);
    std::vector<size_t> get_selected_index_IO();

private:
    nctk::box<undefined_card> deck_area_; // ハリボテ
    std::vector<nctk::box<card>> hand_area_;
    nctk::box_cursors<card> cursors_;
};
