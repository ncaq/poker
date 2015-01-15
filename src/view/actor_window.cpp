#include "../model/actor.hpp"
#include "actor_window.hpp"
#include "main_window.hpp"

actor_window::actor_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window, const std::string& chip_description)
    : window()
    , model_(m)
    , whole_(whole_window)
{
    this->add(chip_notation_window)->set_contents(chip_description);
    this->add(std::make_shared<nctk::window>(chip_notation_window->y(), chip_notation_window->to_right()))->set_contents(this->model_.chip());
}

actor_window::~actor_window()
{}

void actor_window::new_deal()
{
    this->erase(this->hand_);
    this->hand_ = this->add(std::make_shared<nctk::window_list<card_window> >(this->hand_y_top(), 0));
    for(const std::shared_ptr<card>& h : this->model_.hand_reffernce())
    {
        this->hand_->push(std::make_shared<card_window>(*h, this->whole_.deck_->y(), this->whole_.deck_->x(), this->default_hide_setting()));
    }
}

void actor_window::adjust_exchange()
{
    const auto& new_hand = this->model_.hand_reffernce();
    for(size_t scaned = 0; scaned < this->hand_->size(); ++scaned)
    {
        auto old_card = this->hand_->at(scaned);
        auto new_card = std::make_shared<card_window>(*new_hand.at(scaned), this->whole_.deck_->y(), this->whole_.deck_->x(), this->default_hide_setting());
        if(*old_card != *new_card)
        {
            this->hand_->replace(scaned, new_card);
        }
    }
}

void actor_window::sort_hand()
{
    this->hand_->sort();
    this->model_.sort(); // modelの方もsortしておかないとadjust_exchangeで差分が取れない
}

std::string actor_window::show_down()const
{
    return model_.show_down().readable();
}

void actor_window::set_hide_cards(bool hide)
{
    for(auto h : *this->hand_)
    {
        std::dynamic_pointer_cast<card_window>(h)->set_hide(hide);
    }
}

const actor& actor_window::model()const
{
    return this->model_;
}
