#pragma once

#include "ai.hpp"
#include "player.hpp"
#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <random>

enum class lead
{nothing, player_lead, ai_lead};

class card;
class player_window;

class poker_mediator
{
public:
    poker_mediator();
    void set_controller(std::shared_ptr<player_window> controller);

    void new_deal();
    void bet_ante();
    void exchange();
    void raise();
    lead call();
    void payoff(const lead no_fold_actor);

    lead comp_hand()const;
    size_t sum_pool()const;
    bool done()const;
    lead current_lead()const;

    player& player_ref();
    ai& ai_ref();

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    player player_;
    ai     ai_;
};

constexpr size_t ante = 15;
