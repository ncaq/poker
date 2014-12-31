#pragma once

#include "ai.hpp"
#include "card.hpp"
#include "player.hpp"
#include <deque>
#include <functional>
#include <memory>

enum class game_state
{playing, player_win, ai_win};

class player_area;

class poker_mediator
{
public:
    poker_mediator(player_area& player_input);

    game_state bet_ante();
    void init_deal();
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
    size_t pool = 0;
};

constexpr size_t ante = 5;
