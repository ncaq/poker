#include "../model/poker_mediator.hpp"
#include "../nctk/form.hpp"
#include "../view/game_area.hpp"
#include "event.hpp"
#include "event_manager.hpp"

event_manager::event_manager()
{}

void event_manager::play()
{
    poker_.init_deal();
    game_area_.new_game(poker_.player_hand(), poker_.ai_hand());
    game_area_.draw();

    poker_.bet_ante();
    game_area_.draw();

    poker_.exchange();
    game_area_.draw();

    poker_.raise();
    game_area_.draw();

    poker_.call();
    game_area_.draw();

    poker_.payoff();
    game_area_.draw();

    nctk::form to_wait("press any key to exit:");
    to_wait.get_char();
}
