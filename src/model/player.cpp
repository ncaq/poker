#include "../view/player_area.hpp"
#include "player.hpp"

void player::set_controller(std::shared_ptr<player_area> controller)
{
    this->player_input_ = controller;
}

std::deque<bool> player::select_changing_cards()
{
    return player_input_->select_changing_cards();
}

void player::raise()
{
    this->pay(player_input_->raise());
}

bool player::call(const size_t enemy_pool)
{
    return player_input_->call(enemy_pool);
}
