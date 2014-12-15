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

    void deal(const card& c);

private:
    nctk::box<undefined_card> deck_area_; // ハリボテ
    std::vector<nctk::box<card>> hand_area_;
    nctk::box_cursors<card> cursors;
};
