#include "../model/ai.hpp"
#include "../model/player.hpp"
#include "game_area.hpp"
#include "player_area.hpp"
#include <numeric>
#include <unistd.h>

game_area::game_area()
    : deck_area_(std::make_shared<card>(suit_t::spade, 1), 9, 0)
    , message_(0, 0, 15, 13)
{
    deck_area_.set_hide(true);
    update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void game_area::init_game(std::shared_ptr<const player> player_model, std::shared_ptr<const ai> ai_model)
{
    this->player_ = std::make_shared<player_area>(*this, player_model);
    this->ai_ = std::make_shared<actor_area>(*this, ai_model);
}

bool game_area::draw()
{
    usleep(50000);
    clear();
    refresh();
    return (deck_area_.draw() & message_.draw() & player_->draw() & ai_->draw()) ?
        true :
        this->draw();
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

void game_area::exchange()
{
    
}

std::shared_ptr<player_area> game_area::player_input()
{
    return player_;
}
