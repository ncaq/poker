#include "game_area.hpp"
#include <numeric>
#include <unistd.h>

game_area::game_area()
    : deck_area_(0, 0)
    , player_(*this)
    , ai_(*this)
    , message_(0, 0, 15, 13)
{
    update_message(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)"); // 初期メッセージは操作説明
}

void game_area::draw()
{
    bool moving_is_done = true;
    moving_is_done &= deck_area_.draw() & message_.draw() & player_.draw() & ai_.draw();
    if(moving_is_done)
    {
        usleep(100000);
        this->draw();
    }
}

void game_area::new_game(const std::deque<std::shared_ptr<card> >& new_player_hand, const std::deque<std::shared_ptr<card> >& new_ai_hand)
{
    player_.clear();
    ai_.clear();

    for(const auto& h : new_player_hand)
    {
        player_.push(std::make_shared<card_view>(h, deck_area_.y(), deck_area_.x()));
        player_.draw();
    }
    for(const auto& h : new_ai_hand)
    {
        ai_.push(std::make_shared<card_view>(h, deck_area_.y(), deck_area_.x()));
        ai_.draw();
    }
}

void game_area::update_message(const std::string& contents)
{
    message_.set_contents(contents);
    message_.align_window();
    message_.draw();
}

player_area& game_area::player_input()
{
    return player_;
}
