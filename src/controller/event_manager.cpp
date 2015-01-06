#include "../model/poker_mediator.hpp"
#include "../nctk/form.hpp"
#include "../view/game_area.hpp"
#include "event.hpp"
#include "event_manager.hpp"

event_manager::event_manager()
    : game_area_(std::make_shared<game_area>())
    , poker_(std::make_shared<poker_mediator>())
{
}

void event_manager::play()
{
    for(std::unique_ptr<event::event> scene(new event::start()); typeid(scene) != typeid(event::end); scene = scene->next_event(*this))
    {}
    
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
