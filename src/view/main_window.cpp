#include "../model/actor.hpp"
#include "../model/ai.hpp"
#include "../model/player.hpp"
#include "../nctk/window.hpp"
#include "ai_window.hpp"
#include "main_window.hpp"
#include "player_window.hpp"
#include <numeric>
#include <unistd.h>

main_window::main_window()
    : deck_window_(std::make_shared<card_window>(std::make_shared<card>(suit_t::spade, 1), 9, 0))
    , pool_chip_(0, 0, 10, 13)
    , message_(0, 0, 14, 13)
{
    deck_window_->set_hide(true);
    this->update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void main_window::init_game(std::shared_ptr<poker_mediator> model)
{
    this->model_ = model;
    this->player_ = std::make_shared<player_window>(*this, this->model_->player_ptr(), std::make_shared<nctk::window>(0, 0, 11, 13));
    this->ai_ = std::make_shared<ai_window>(*this, this->model_->ai_ptr(), std::make_shared<nctk::window>(0, 0, 12, 13));
}

bool main_window::draw()
{
    this->pool_chip_.set_contents(
        "pool   chip:  " + std::to_string(*this->player_->model()->pool_chip() + *this->ai_->model()->pool_chip()) +
        " (player: " + std::to_string(*this->player_->model()->pool_chip()) +
        ", ai: " + std::to_string(*this->ai_->model()->pool_chip()) +
        ")");
    this->pool_chip_.align_window();

    usleep(100000);
    clear();
    refresh();
    bool done = true;
    done = this->deck_window_->draw() && done;
    done = this->player_->draw() && done;
    done = this->ai_->draw() && done;
    done = this->message_.draw() && done;
    done = this->pool_chip_.draw() && done;
    if(done)
    {        
        return true;
    }else
    {
        return this->draw();
    }
}

void main_window::update_message(const std::string& contents)
{
    message_.set_contents(contents);
    message_.align_window();
}

void main_window::new_deal()
{
    this->player_->new_deal(this->deck_window_);
    this->ai_->new_deal(this->deck_window_);
    while(!this->draw()){}
    this->player_->sort_hand();
    this->ai_->sort_hand();
    while(!this->draw()){}
}

void main_window::adjust_exchange()
{
    this->player_->adjust_exchange();
    this->ai_->adjust_exchange();
}

void main_window::report(const lead no_fold_actor)
{
    this->player_->set_hide_cards(false);
    this->ai_->set_hide_cards(false);

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
        "player: " + this->player_->show_down() + "\n" +
        "ai    : " + this->ai_->show_down() + "\n" +
        card_report + pay_report);
}

std::shared_ptr<player_window> main_window::player_input()
{
    return player_;
}

std::shared_ptr<card_window> main_window::deck_window()const
{
    return deck_window_;
}
