#pragma once

#include <deque>
#include <functional>
#include <memory>

enum class game_state
{playing, player_win, ai_win};

class ai;
class card;
class player;
class player_area;

class poker_mediator
{
public:
    poker_mediator();
    void set_player_input(std::shared_ptr<player_area> player_input);
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
    std::shared_ptr<player> player_;
    std::shared_ptr<ai> ai_;
};

constexpr size_t ante = 5;
