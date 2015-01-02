#include "game_area.hpp"
#include "player_area.hpp"
#include <numeric>
#include <unistd.h>

game_area::game_area()
    : deck_area_(9, 0)
    , player_(std::make_shared<player_area>(*this))
    , ai_(std::make_shared<actor_area>(*this))
    , message_(0, 0, 15, 13)
{
    update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void game_area::new_game(const std::deque<std::shared_ptr<card> >& new_player_hand, const std::deque<std::shared_ptr<card> >& new_ai_hand)
{
    player_->clear();
    ai_->clear();

    for(const auto& h : new_player_hand)
    {
        player_->push(std::make_shared<card_view>(h, deck_area_.y(), deck_area_.x()));
    }
    for(const auto& h : new_ai_hand)
    {
        ai_->push(std::make_shared<card_view>(h, deck_area_.y(), deck_area_.x()));
    }
}

void game_area::draw()
{
    usleep(50000);
    clear();
    refresh();
    bool moving_is_done = true;
    moving_is_done &= deck_area_.draw() & message_.draw() & player_->draw() & ai_->draw();
    if(!moving_is_done)
    {
        this->draw();
    }
}

void game_area::update_message(const std::string& contents)
{
    message_.set_contents(contents);
    message_.align_window();
}

std::shared_ptr<player_area> game_area::player_input()
{
    return player_;
}
