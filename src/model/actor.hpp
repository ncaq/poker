#pragma once

#include "poker_hands.hpp"
#include <deque>
#include <memory>

class card;

/*!
  pokerをやる人
  基底クラス
*/

class actor
{
public:
    virtual ~actor() = 0;

    void new_deal(std::deque<std::shared_ptr<card> >& deck);
    void exchange(std::deque<std::shared_ptr<card> >& deck);
    void exchange_select_cards(std::deque<std::shared_ptr<card> >& deck, const std::deque<bool>& selected);
    void pay(const size_t size); // true: 金額不足
    void payoff(const size_t paid_chip);
    poker_hands show_down()const;
    void sort();

    virtual std::deque<bool> select_changing_cards() = 0; //!< playerとaiにはこれらを実装してもらいます
    virtual size_t raise() = 0;
    virtual bool call(const size_t enemy_pool) = 0;

    std::deque<std::shared_ptr<card> >& hand_reffernce();

    std::shared_ptr<size_t> chip()const; //!< windowに参照させたいのでshared_ptrです
    std::shared_ptr<size_t> pool()const;

private:
    std::deque<std::shared_ptr<card> > hand_;
    std::shared_ptr<size_t> chip_ = std::make_shared<size_t>(100);
    std::shared_ptr<size_t> pool_ = std::make_shared<size_t>(0);
};
