#include "curses_field.hpp"

curses_field::curses_field()
    :deck_area_(undefined_card(), 0, 0), cursors()
{
}

void curses_field::deal(const card& c)
{
    hand_area_.push_back(nctk::box<card>(c, 0, 0));
    if(hand_area_.size() <= 1)
    {
        hand_area_.at(0).moving_draw(14, 0);
    }
    else
    {
        (hand_area_.end() - 2)->move_to_right(hand_area_.back());
    }
}
