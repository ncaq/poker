#include "../model/actor.hpp"
#include "../model/ai.hpp"
#include "../model/player.hpp"
#include "../nctk/window.hpp"
#include "ai_area.hpp"
#include "game_area.hpp"
#include "player_area.hpp"
#include <numeric>
#include <unistd.h>

game_area::game_area()
    : deck_area_(std::make_shared<card_window>(std::make_shared<card>(suit_t::spade, 1), 9, 0))
    , pool_chip_(0, 0, 10, 13)
    , message_(0, 0, 14, 13)
{
    deck_area_->set_hide(true);
    this->update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void game_area::init_game(std::shared_ptr<poker_mediator> model)
{
    this->model_ = model;
    this->player_ = std::make_shared<player_area>(*this, this->model_->player_ptr(), std::make_shared<nctk::window>(0, 0, 11, 13));
    this->ai_ = std::make_shared<ai_area>(*this, this->model_->ai_ptr(), std::make_shared<nctk::window>(0, 0, 12, 13));
}

bool game_area::draw()
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
    done = this->deck_area_->draw() && done;
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

void game_area::update_message(const std::string& contents)
{
    message_.set_contents(contents);
    message_.align_window();
}

void game_area::new_deal()
{
    this->player_->new_deal(this->deck_area_);
    this->ai_->new_deal(this->deck_area_);
    while(!this->draw()){}
    this->player_->sort_hand();
    this->ai_->sort_hand();
    while(!this->draw()){}
}

void game_area::adjust_exchange()
{
    this->player_->adjust_exchange();
    this->ai_->adjust_exchange();
}

void game_area::report(const lead no_fold_actor)
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

std::shared_ptr<player_area> game_area::player_input()
{
    return player_;
}

std::shared_ptr<card_window> game_area::deck_area()const
{
    return deck_area_;
}
