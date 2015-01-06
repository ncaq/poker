#include "../model/ai.hpp"
#include "../model/player.hpp"
#include "ai_area.hpp"
#include "game_area.hpp"
#include "player_area.hpp"
#include <numeric>
#include <unistd.h>

game_area::game_area()
    : deck_area_(std::make_shared<card_view>(std::make_shared<card>(suit_t::spade, 1), 9, 0))
    , pool_chip_(0, 0, 10, 13)
    , message_(0, 0, 15, 13)
{
    deck_area_->set_hide(true);
    this->update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void game_area::init_game(std::shared_ptr<player> player_model, std::shared_ptr<ai> ai_model)
{
    this->player_ = std::make_shared<player_area>(*this, player_model, std::make_shared<nctk::new_window<std::string> >(0, 0, 11, 13));
    this->ai_ = std::make_shared<ai_area>(*this, ai_model, std::make_shared<nctk::new_window<std::string> >(0, 0, 12, 13));
}

bool game_area::draw()
{
    usleep(100000);
    clear();
    refresh();
    bool done = true;
    done = deck_area_->draw() && done;
    done = message_.draw() && done;
    done = player_->draw() && done;
    done = ai_->draw() && done;
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

std::shared_ptr<player_area> game_area::player_input()
{
    return player_;
}

std::shared_ptr<card_view> game_area::deck_area()const
{
    return deck_area_;
}
