#include "event_manager.hpp"

event_manager::event_manager()
    : gui_(std::make_shared<game_area>())
    , poker_(std::make_shared<poker_mediator>())
{}

void event_manager::play()
{
    this->init();
}

void event_manager::init()
{
    this->gui_->init_game(this->poker_);
    this->poker_->set_controller(this->gui_->player_input());

    this->new_deal(); // c++11ではstd::make_uniqueは使えない
}

void event_manager::new_deal()
{
    this->gui_->draw();
    if(this->game_count_ < 3 && !this->poker_->done())
    {
        this->poker_->new_deal();
        this->gui_->new_deal();

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
    this->gui_->draw();

    this->poker_->bet_ante();
    this->exchange();
}

void event_manager::exchange()
{
    this->gui_->draw();

    this->poker_->exchange();
    this->gui_->adjust_exchange();
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
    this->gui_->draw();

    this->poker_->raise();

    this->call();
}

void event_manager::call()
{
    this->gui_->draw();

    lead no_fold_actor = this->poker_->call();

    this->payoff(no_fold_actor);
}

void event_manager::payoff(const lead no_fold_actor)
{
    this->gui_->draw();

    this->gui_->report(no_fold_actor);

    this->gui_->draw();
    nctk::form to_wait("press any key to next game:");
    to_wait.draw();
    to_wait.get_char();

    this->poker_->payoff(no_fold_actor);

    ++this->game_count_;

    this->gui_->update_message("new game");

    this->new_deal();
}

void event_manager::player_win()
{
    this->gui_->draw();

    this->gui_->update_message("player win.");

    this->end();
}

void event_manager::ai_win()
{
    this->gui_->draw();

    this->gui_->update_message("ai win.");

    this->end();
}

void event_manager::half()
{
    this->gui_->draw();

    this->gui_->update_message("half.");

    this->end();
}

void event_manager::end()
{
    this->gui_->draw();
    
    nctk::form to_wait("press any key to exit:");
    to_wait.draw();
    to_wait.get_char();
}
