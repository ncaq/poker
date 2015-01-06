#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <random>

enum class lead
{nothing, player_lead, ai_lead};

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
    lead bet_ante();
    void exchange();
    void raise();
    lead call();
    void payoff(const lead no_fold_actor);

    lead current_lead();

    std::shared_ptr<player> player_ptr()const;
    std::shared_ptr<ai> ai_ptr()const;

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    std::shared_ptr<player> player_;
    std::shared_ptr<ai> ai_;
};

constexpr size_t ante = 5;
