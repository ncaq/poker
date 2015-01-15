#pragma once

#include "ai.hpp"
#include "player.hpp"
#include <algorithm>
#include <deque>
#include <functional>
#include <memory>
#include <random>

/*!
  有利な方を表す
*/
enum class lead
{nothing, player_lead, ai_lead};

class card;
class player_window;

/*!
  pokerのゲームロジックを制御する
*/

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

    lead comp_hand()const;      //!< どちらの手札が強いか
    size_t sum_pool()const;
    bool done()const;           //!< ゲーム終了判定
    lead current_lead()const;   //!< 規定ゲーム数した場合の,判定勝ち判定

    player& player_ref();
    ai& ai_ref();

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    player player_;
    ai     ai_;
};

constexpr size_t ante = 15;
