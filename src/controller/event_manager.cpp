#include "../nctk/form.hpp"
#include "event_manager.hpp"

event_manager::event_manager()
    : game_area_(std::make_shared<game_area>())
    , poker_(std::make_shared<poker_mediator>())
    , event_scene_(new init_chip())
{
    poker_->set_player_input(game_area_->player_input());
}

void event_manager::play()
{

    nctk::form to_wait("press any key to exit:");
    to_wait.get_char();
}

std::shared_ptr<game_area> event_manager::gui()
{
    return game_area_;
}

std::shared_ptr<poker_mediator> event_manager::poker()
{
    return poker_;
}
