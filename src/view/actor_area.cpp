#include "../model/actor.hpp"
#include "actor_area.hpp"
#include "game_area.hpp"

actor_area::actor_area(game_area& whole_area, std::shared_ptr<const actor> m)
    : whole_area_(whole_area)
    , model_(m)
{}

actor_area::~actor_area()
{}

bool actor_area::draw()
{
    return std::all_of(this->hand_.begin(), this->hand_.end(),
                       [](const std::shared_ptr<card_view> h)
                       {
                           return h->draw();
                       });
}

void actor_area::set_hide_cards(bool hide)
{
    for(auto& h : this->hand_)
    {
        h->set_hide(hide);
    }
}

void actor_area::new_deal(const nctk::new_window<std::string>& deck_area)
{
    for(const std::shared_ptr<card>& h : this->model()->hand())
    {
        this->push(std::make_shared<card_view>(h, deck_area.y(), deck_area.x()));
    }
}

void actor_area::push(std::shared_ptr<card_view> card)
{
    this->hand_.push_back(card);
    this->hand_.back()->set_hide(this->default_hide_setting());
    if(this->hand_.size() == 1)
    {
        this->hand_.front()->move_while_drawing(this->hand_y_top(), 0);
    }
    else
    {
        (*(this->hand_.end() - 2))->place_to_right(*this->hand_.back());
    }
}
#include "../nctk/debug_stream.hpp"
void actor_area::sort_hand()
{
    for(auto left = this->hand_.begin(); left != this->hand_.end(); ++left)
    {
        auto min_card_itr = std::min_element(left, this->hand_.end(),
                                             [](const std::shared_ptr<card_view> a, const std::shared_ptr<card_view> b)
                                             {
                                                 return *a < *b;
                                             });
        ::swap(*(*left), *(*min_card_itr), [this](){return this->whole().draw();}); // 座標のswap
        std::swap(*left, *min_card_itr);
    }
    nctk::debug_stream dout;
    for(auto h : this->hand_)
    {
        dout << h->show_contents() << std::endl;
    }
}

bool actor_area::default_hide_setting()const
{
    return true;
}

size_t actor_area::hand_y_top()const
{
    return 0;
}

game_area& actor_area::whole()const
{
    return whole_area_;
}

std::shared_ptr<const actor> actor_area::model()const
{
    return model_;
}
