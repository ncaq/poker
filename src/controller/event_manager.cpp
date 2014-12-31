#include "event_manager.hpp"
#include "../nctk/form.hpp"

event_manager::event_manager()
    : game_area_()
    , poker_(game_area_.player_input())
{}

void event_manager::play()
{
    game_area_.new_game(poker_.player_hand(), poker_.ai_hand());
    game_area_.draw();

    // poker_
    
    // const std::string message_to_wait = "press any key to exit:";
    // auto message_win = nctk::new_window(1, message_to_wait.size(), getmaxy(stdscr) - 1, 0);
    // message_win.set_contents(message_to_wait).draw();

    // nctk::form form(getmaxy(stdscr) - 1, message_win.right());
    // form.get_char();
}
