#include "../view/main_window.hpp"
#include "event_manager.hpp"

event_manager::event_manager()
    : tui_(std::make_shared<main_window>())
    , poker_(std::make_shared<poker_mediator>())
{}

void event_manager::play()
{
    this->tui_->init_game(this->poker_);
    this->poker_->set_controller(this->tui_->player_);

    this->new_deal();
}

void event_manager::new_deal()
{
    this->tui_->draw();
    if(this->game_count_ < 3 && !this->poker_->done())
    {
        this->poker_->new_deal();
        this->tui_->new_deal();

        this->bet_ante();
    }
    else
    {
        lead winner = this->poker_->current_lead();
        if(winner == lead::nothing)
        {
            this->half();
        }
        else if(winner == lead::player_lead)
        {
            this->player_win();
        }
        else if(winner == lead::ai_lead)
        {
            this->ai_win();
        }
        else
        {
            throw std::range_error("lead is not nothing or player_lead or ai_lead.");
        }
    }
}

void event_manager::bet_ante()
{
    this->tui_->draw();

    this->poker_->bet_ante();
    this->exchange();
}

void event_manager::exchange()
{
    this->tui_->draw();

    this->poker_->exchange();
    this->tui_->adjust_exchange();
    if(this->exchange_count_ < 1)
    {
        ++this->exchange_count_;
        this->exchange();
    }
    else
    {
        this->exchange_count_ = 0;
        this->raise();
    }
}

void event_manager::raise()
{
    this->tui_->draw();

    this->poker_->raise();

    this->call();
}

void event_manager::call()
{
    this->tui_->draw();

    lead no_fold_actor = this->poker_->call();

    this->payoff(no_fold_actor);
}

void event_manager::payoff(const lead no_fold_actor)
{
    this->tui_->draw();

    this->tui_->report(no_fold_actor);

    this->tui_->draw();
    nctk::display::set_dialog("press any key to next game:");
    this->tui_->draw();

    this->poker_->payoff(no_fold_actor);

    ++this->game_count_;

    this->tui_->update_message({"new game"});

    this->new_deal();
}

void event_manager::player_win()
{
    this->tui_->draw();

    this->tui_->update_message({"player win."});

    this->end();
}

void event_manager::ai_win()
{
    this->tui_->draw();

    this->tui_->update_message({"ai win."});

    this->end();
}

void event_manager::half()
{
    this->tui_->draw();

    this->tui_->update_message({"half."});

    this->end();
}

void event_manager::end()
{
    this->tui_->draw();

    nctk::display::set_dialog("press any key to exit:");
    this->tui_->draw();
}
