#include "../view/player_area.hpp"
#include "player.hpp"

player::player(std::shared_ptr<player_area> player_input)
    : player_input_(player_input)
{}

player::~player(){}

std::deque<bool> player::select_changing_cards()
{
    return player_input_->select_changing_cards();
}

size_t player::raise()
{
    return player_input_->raise();
}

bool player::call()
{
    return player_input_->call();
}
