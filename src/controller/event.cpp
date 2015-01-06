#include "../model/poker_mediator.hpp"
#include "../view/game_area.hpp"
#include "event.hpp"
#include "event_manager.hpp"

namespace event
{
    event::~event(){}

    std::unique_ptr<event> event::next_event(event_manager& context)
    {
        auto&& stash = this->update(context);
        context.gui()->draw();
        return std::move(stash);
    }

    std::unique_ptr<event> start::update(event_manager& context)
    {
        context.gui()->init_game(context.poker()->player_ptr(), context.poker()->ai_ptr());
        context.poker()->set_controller(context.gui()->player_input());
        return std::unique_ptr<event>(new new_deal()); // c++11ではstd::make_uniqueは使えない
    }

    std::unique_ptr<event> new_deal::update(event_manager& context)
    {
        context.poker()->new_deal();
        context.gui()->new_deal();
        return std::unique_ptr<event>(new bet_ante());
    }

    std::unique_ptr<event> bet_ante::update(event_manager& context)
    {
        game_state winner = context.poker()->bet_ante();
        if(winner == game_state::playing)
        {        
            return std::unique_ptr<event>(new exchange());
        }
        else
        {
            if(winner == game_state::player_win)
            {
                return std::unique_ptr<event>(new player_win);
            }
            if(winner == game_state::ai_win)
            {
                return std::unique_ptr<event>(new ai_win);
            }
        }
        throw std::range_error("game_state is not playing or player_win or ai_win.");
    }

    std::unique_ptr<event> exchange::update(event_manager& context)
    {
        context.poker()->exchange();
        context.gui()->exchange();
        return std::unique_ptr<event>(new raise());
    }

    std::unique_ptr<event> raise::update(event_manager& context)
    {
        context.poker()->raise();
        // todo: gui
        return std::unique_ptr<event>(new call());
    }

    std::unique_ptr<event> call::update(event_manager& context)
    {
        context.poker()->call();
        return std::unique_ptr<event>(new payoff());
    }

    std::unique_ptr<event> payoff::update(event_manager& context)
    {
        context.poker()->payoff();
        return std::unique_ptr<event>(new bet_ante());
    }

    std::unique_ptr<event> player_win::update(event_manager& context)
    {
        context.gui()->update_message("player win.");
        return std::unique_ptr<event>(new end());
    }

    std::unique_ptr<event> ai_win::update(event_manager& context)
    {
        context.gui()->update_message("ai win.");
        return std::unique_ptr<event>(new end());
    }

    std::unique_ptr<event> end::update(event_manager&)
    {
        return std::unique_ptr<event>(this);
    }
}
