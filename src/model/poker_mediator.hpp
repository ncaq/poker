#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <random>

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
    void set_controller(std::shared_ptr<player_area> controller);

    void new_deal();
    game_state bet_ante();
    void exchange();
    void raise();
    void call();
    void payoff();

    std::shared_ptr<const player> player_ptr()const;
    std::shared_ptr<const ai> ai_ptr()const;

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    std::shared_ptr<player> player_;
    std::shared_ptr<ai> ai_;
};

constexpr size_t ante = 5;
