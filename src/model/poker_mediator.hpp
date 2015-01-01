#pragma once

#include "ai.hpp"
#include "player.hpp"
#include <deque>
#include <functional>
#include <memory>

enum class game_state
{playing, player_win, ai_win};

class card;

class poker_mediator
{
public:
    poker_mediator();
    void init_deal();

    game_state bet_ante();
    void exchange();
    void raise();
    void call();
    void payoff();

    std::deque<std::shared_ptr<card> > player_hand()const;
    std::deque<std::shared_ptr<card> > ai_hand()const;

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    player player_;
    ai ai_;
};

constexpr size_t ante = 5;
