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
    this->deck_ = this->add(std::make_shared<card_window> (card(suit_t::spade, 1), 9, 0, true));
    this->message_ = this->add(std::make_shared<nctk::window>(14, 13));
    this->update_message({"up: select card to change",
                "right and left: move cursor",
                "down or enter: done selecting"
                }); // 初期メッセージは操作説明
}

void main_window::init_game(std::shared_ptr<poker_mediator> model)
{
    this->model_ = model;
    this->player_ = this->add(std::make_shared<player_window>(this->model_->player_ref(), *this, std::make_shared<nctk::window>(11, 13)));
    this->ai_     = this->add(std::make_shared<ai_window>    (this->model_->ai_ref(),     *this, std::make_shared<nctk::window>(12, 13)));

    std::function<std::vector<std::string>()> pool_message_callback = [this]()
        {
            return std::vector<std::string>
            ({
                "pool   chip:  " + nctk::to_string(*this->player_->model().pool()  +
                                                   *this->ai_    ->model().pool()) +
                    " (player: " + nctk::to_string(*this->player_->model().pool()) +
                    ", ai: "     + nctk::to_string(*this->ai_    ->model().pool()) +
                    ")"
                    });
        };
    this->add(std::make_shared<nctk::window>(10, 13, pool_message_callback)); // pool
}

bool main_window::draw()
{
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

void main_window::update_message(const std::vector<std::string>& contents)
{
    this->message_->set_contents(contents);
}

void main_window::new_deal()
{
    this->player_->new_deal();
    this->ai_    ->new_deal();
    while(!this->draw()){}
    this->player_->sort_hand();
    this->ai_    ->sort_hand();
    while(!this->draw()){}
}

void main_window::adjust_exchange()
{
    this->player_->adjust_exchange();
    this->ai_    ->adjust_exchange();
    while(!this->draw()){}
    this->player_->sort_hand();
    this->ai_    ->sort_hand();
    while(!this->draw()){}
}

void main_window::report(const lead no_fold_actor)
{
    this->player_->set_hide_cards(false);
    this->ai_    ->set_hide_cards(false);

    lead high_card_actor = this->model_->comp_hand();
    std::string card_report;
    std::string pay_report;
    std::string to_pay_chip = nctk::to_string(this->model_->sum_pool());
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

    this->update_message({
            {"player: " + this->player_->show_down()},
            {"ai    : " + this->ai_    ->show_down()},
            {card_report + pay_report}}
        );
}
