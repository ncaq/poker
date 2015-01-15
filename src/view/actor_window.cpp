#include "../model/actor.hpp"
#include "actor_window.hpp"
#include "main_window.hpp"

actor_window::actor_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window, const std::string& chip_description)
    : window()
    , model_(m)
    , whole_(whole_window)
{
    this->insert("chip_notation", chip_notation_window);
    this->at("chip_notation")->set_contents(chip_description);
    this->insert("chip",
                 this->at("chip_notation")->make_right<std::shared_ptr<nctk::window> >
                 ([this](const size_t y, const size_t x)
                  {
                      return std::make_shared<nctk::window>(y, x);
                  }));
    this->at("chip")->set_contents(this->model_.chip());
}

actor_window::~actor_window()
{}

void actor_window::new_deal(const std::shared_ptr<nctk::window> deck_window)
{
    this->clear_hand();
    const auto& new_hand = this->model_.hand_reffernce();
    for(const std::shared_ptr<card>& h : new_hand)
    {
        auto it = this->insert(
            "card_" + nctk::to_string(this->hand_.size()),
            std::make_shared<card_window>(*h, deck_window->y(), deck_window->x(), this->default_hide_setting())).first;

        this->hand_.push_back(std::dynamic_pointer_cast<card_window>(it->second));

        if(this->hand_.size() == 1)
        {
            this->hand_.front()->move_while_drawing(this->hand_y_top(), 0);
        }
        else
        {
            (*(this->hand_.end() - 2))->place_to_right(*this->hand_.back());
        }
    }
}

void actor_window::adjust_exchange()
{
    auto& new_hand = this->model_.hand_reffernce();
    for(size_t scaned = 0; scaned < this->hand_.size(); ++scaned)
    {
        auto new_card =
            std::make_shared<card_window>(*new_hand.at(scaned),
                                          this->whole_.deck_window()->y(),
                                          this->whole_.deck_window()->x(),
                                          this->default_hide_setting());
        if(*this->hand_.at(scaned) != *new_card)
        {
            this->hand_.at(scaned)->set_hide(true);
            swap_and_move(*this->hand_.at(scaned), *new_card, [this](){return this->whole_.draw();});
        }
    }
    this->sort_hand();
}

void actor_window::sort_hand()
{
    for(auto left = this->hand_.begin(); left != this->hand_.end(); ++left)
    {
        auto min_card_itr = std::min_element(left, this->hand_.end(),
                                             [](const std::shared_ptr<card_window> a, const std::shared_ptr<card_window> b)
                                             {
                                                 return *a < *b;
                                             });
        swap_and_move(*(*left), *(*min_card_itr), [this](){return this->whole_.draw();}); // 座標もswap
    }
    this->model_.sort();       // modelの方もsortしておかないとadjust_exchangeで差分が取れない
}

std::string actor_window::show_down()const
{
    return model_.show_down().readable();
}

void actor_window::set_hide_cards(bool hide)
{
    for(auto& h : this->hand_)
    {
        h->set_hide(hide);
    }
}

const actor& actor_window::model()const
{
    return this->model_;
}

void actor_window::clear_hand()
{
    for(size_t i = 0; i < hand_.size(); ++i)
    {
        this->erase("card_" + nctk::to_string(i));
    }
    this->hand_.clear();
}
