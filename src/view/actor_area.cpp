#include "../model/actor.hpp"
#include "actor_area.hpp"
#include "game_area.hpp"

actor_area::actor_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::new_window<std::string> > chip_notation_area, const std::string& chip_notation)
    : whole_area_(whole_area)
    , model_(m)
    , chip_notation_(chip_notation_area)
{
    this->chip_notation_->set_contents(chip_notation);
    this->chip_notation_->align_window();
    this->chip_ = this->chip_notation_->make_right<std::shared_ptr<nctk::new_window<size_t> > >([](const size_t y, const size_t x){return std::make_shared<nctk::new_window<size_t> >(0, 0, y, x);});
    this->chip_->set_reference(this->model_->chip());
    this->chip_->align_window();
}

actor_area::~actor_area()
{}

bool actor_area::draw()
{
    bool result = true;
    for(auto& h : this->hand_)
    {        
        result = h->draw() && result;
    }
    result = this->chip_notation_->draw() && result;
    result = this->chip_->draw() && result;
    return result;
}

void actor_area::set_hide_cards(bool hide)
{
    for(auto& h : this->hand_)
    {
        h->set_hide(hide);
    }
}

void actor_area::new_deal(const std::shared_ptr<nctk::new_window<std::string> > deck_area)
{
    for(const std::shared_ptr<card>& h : this->model()->hand())
    {
        this->push(std::make_shared<card_view>(h, deck_area->y(), deck_area->x(), this->default_hide_setting()));
    }
}

void actor_area::push(std::shared_ptr<card_view> card)
{
    this->hand_.push_back(card);
    if(this->hand_.size() == 1)
    {
        this->hand_.front()->move_while_drawing(this->hand_y_top(), 0);
    }
    else
    {
        (*(this->hand_.end() - 2))->place_to_right(*this->hand_.back());
    }
}

void actor_area::sort_hand()
{
    for(auto left = this->hand_.begin(); left != this->hand_.end(); ++left)
    {
        auto min_card_itr = std::min_element(left, this->hand_.end(),
                                             [](const std::shared_ptr<card_view> a, const std::shared_ptr<card_view> b)
                                             {
                                                 return *a < *b;
                                             });
        ::swap(*(*left), *(*min_card_itr), [this](){return this->whole().draw();}); // 座標もswap
    }
    this->model_->sort();       // modelの方もsortしておかないとadjust_exchangeで差分が取れない
}

void actor_area::adjust_exchange()
{
    auto new_hand = this->model_->hand();
    for(size_t scaned = 0; scaned < this->hand_.size(); ++scaned)
    {
        auto new_card = std::make_shared<card_view>(new_hand.at(scaned), this->whole().deck_area()->y(), this->whole().deck_area()->x(), this->default_hide_setting());
        if(*this->hand_.at(scaned) != *new_card)
        {
            this->hand_.at(scaned)->set_hide(true);
            ::swap(*this->hand_.at(scaned), *new_card, [this](){return this->whole().draw();});
        }
    }
    this->sort_hand();
}

std::shared_ptr<const actor> actor_area::model()const
{
    return model_;
}

game_area& actor_area::whole()const
{
    return whole_area_;
}
