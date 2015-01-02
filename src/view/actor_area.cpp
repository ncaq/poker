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
#include "../nctk/debug_stream.hpp"
void actor_area::push(std::shared_ptr<card_view> card)
{
    static nctk::debug_stream dout;
    dout << "y: " << card->y() << ", x: " << card->x() << std::endl;
    hand_.push_back(card);
    if(hand_.size() == 1)
    {
        hand_.front()->move_while_drawing(this->hand_y_top(), 0);
    }
    else
    {
        (*(hand_.end() - 2))->place_to_right(*hand_.back());
    }
}

void actor_area::clear()
{
    hand_.clear();
}

size_t actor_area::hand_y_top()const
{
    return 0;
}

std::deque<std::shared_ptr<card_view> > actor_area::hand()const
{
    return hand_;
}

game_area& actor_area::whole()const
{
    return whole_area_;
}
