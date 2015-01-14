#include "../model/actor.hpp"
#include "../model/ai.hpp"
#include "../model/player.hpp"
#include "../nctk/display.hpp"
#include "ai_window.hpp"
#include "card_window.hpp"
#include "main_window.hpp"
#include "player_window.hpp"
#include <numeric>

main_window::main_window()
{
    nctk::display::init();

    this->insert("deck",    std::make_shared<card_window> (card(suit_t::spade, 1), 9, 0, true));
    this->insert("pool",    std::make_shared<nctk::window>(0, 0, 10, 13));
    this->insert("message", std::make_shared<nctk::window>(0, 0, 14, 13));
    this->update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void main_window::init_game(std::shared_ptr<poker_mediator> model)
{
    this->model_ = model;
    this->insert("player", std::make_shared<player_window>(this->model_->player_ref(), *this, std::make_shared<nctk::window>(0, 0, 11, 13)));
    this->insert("ai",     std::make_shared<ai_window>    (this->model_->ai_ref(),     *this, std::make_shared<nctk::window>(0, 0, 12, 13)));
    this->at("pool")->set_contents(
        "pool   chip:  " + std::to_string(*this->player_()->model().pool()  +
                                          *this->ai_()    ->model().pool()) +
        " (player: "     + std::to_string(*this->player_()->model().pool()) +
        ", ai: "         + std::to_string(*this->ai_()    ->model().pool()) +
        ")");
}

bool main_window::draw()
{
    this->at("pool")->align_window();
    if(window::draw())
    {
        nctk::display::flush();
        return true;
    }
    else
    {
        nctk::display::flush();
        return this->draw();
    }
}

void main_window::update_message(const std::string& contents)
{
    this->at("message")->set_contents(contents);
    this->at("message")->align_window();
}

void main_window::new_deal()
{
    this->player_()->new_deal(this->deck_window());
    this->ai_()    ->new_deal(this->deck_window());
    while(!this->draw()){}
    this->player_()->sort_hand();
    this->ai_()    ->sort_hand();
    while(!this->draw()){}
}

void main_window::adjust_exchange()
{
    this->player_()->adjust_exchange();
    this->ai_()    ->adjust_exchange();
}

void main_window::report(const lead no_fold_actor)
{
    this->player_()->set_hide_cards(false);
    this->ai_()    ->set_hide_cards(false);

    lead high_card_actor = this->model_->comp_hand();
    std::string card_report;
    std::string pay_report;
    std::string to_pay_chip = std::to_string(this->model_->sum_pool());
    if(high_card_actor == lead::nothing)
    {
        card_report = "hand is draw. ";
        switch(no_fold_actor)
        {
        case lead::nothing:     pay_report = "chip is returned."                         ;break;
        case lead::player_lead: pay_report = "but, chip " + to_pay_chip + " is yours."   ;break;
        case lead::ai_lead:     pay_report = "but, chip " + to_pay_chip + " is dropped." ;break;
        }
    }
    else if(high_card_actor == lead::player_lead)
    {
        card_report = "your hand is higher ai's. ";
        switch(no_fold_actor)
        {
        case lead::nothing:     pay_report = "so, chip "  + to_pay_chip + " is yours."   ;break;
        case lead::player_lead: pay_report = "chip "      + to_pay_chip + " is yours."   ;break;
        case lead::ai_lead:     pay_report = "but, chip " + to_pay_chip + " is dropped." ;break;
        }
    }
    else if(high_card_actor == lead::ai_lead)
    {
        card_report = "your hand is lower ai's. ";
        switch(no_fold_actor)
        {
        case lead::nothing:     pay_report = "so, chip "  + to_pay_chip + " is dropped." ;break;
        case lead::player_lead: pay_report = "but, chip " + to_pay_chip + " is yours."   ;break;
        case lead::ai_lead:     pay_report = "chip "      + to_pay_chip + " is dropped." ;break;
        }
    }

    this->update_message(
        "player: " + this->player_()->show_down() + "\n" +
        "ai    : " + this->ai_()    ->show_down() + "\n" +
        card_report + pay_report);
}

std::shared_ptr<card_window> main_window::deck_window()const
{
    return this->at<card_window>("deck");
}

std::shared_ptr<player_window> main_window::player_()
{
    return this->at<player_window>("player");
}

std::shared_ptr<ai_window> main_window::ai_()
{
    return this->at<ai_window>("ai");
}
