#include "actor_area.hpp"
#include "game_area.hpp"

actor_area::actor_area(game_area& whole_area)
    : whole_area_(whole_area)
{}

actor_area::~actor_area()
{}

bool actor_area::draw()
{
    return std::all_of(hand_.begin(), hand_.end(),
                       [](const std::shared_ptr<card_view> h)
                       {
                           return h->draw();
                       });
}

void actor_area::push(std::shared_ptr<card_view> card)
{
    hand_.push_back(card);
    if(hand_.size() <= 1)
    {
        hand_.at(0)->move_while_drawing(11, 0);
    }
    else
    {
        (*(hand_.end() - 2))->place_other_window_to_right_while_drawing(*hand_.back());
    }
}

void actor_area::clear()
{
    hand_.clear();
}

std::deque<std::shared_ptr<card_view> > actor_area::hand()const
{
    return hand_;
}

game_area& actor_area::whole()const
{
    return whole_area_;
}
