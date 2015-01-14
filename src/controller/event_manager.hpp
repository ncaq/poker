#pragma once

#include "../model/poker_mediator.hpp"
#include <memory>

/*!
  eventを進めていくclass
  単純に関数転移する
 */

class main_window;

class event_manager
{
public:
    event_manager();

    void play();

private:
    void new_deal();
    void bet_ante();
    void exchange();
    void raise();
    void call();
    void payoff(const lead no_fold_actor);
    void player_win();
    void ai_win();
    void half();
    void end();

    std::shared_ptr<main_window> tui_;
    std::shared_ptr<poker_mediator> poker_;

    size_t game_count_ = 0;
    size_t exchange_count_ = 0;
};
