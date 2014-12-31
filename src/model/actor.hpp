#pragma once

#include "card.hpp"
#include "poker_hands.hpp"
#include <deque>
#include <memory>

class actor
{
public:
    actor();
    virtual ~actor() = 0;

    void init_deal(std::deque<std::shared_ptr<card> > hand);
    void exchange(std::deque<std::shared_ptr<card> > deck);
    bool pay(const size_t size); // true: 金額不足
    poker_hands show_down();

    virtual std::deque<bool> select_changing_cards() = 0;
    virtual size_t raise() = 0; // 0: raiseしない
    virtual bool call() = 0;

    size_t chip()const;
    size_t pool_chip()const;

    std::deque<std::shared_ptr<card> > hand()const;

private:
    std::deque<std::shared_ptr<card> > hand_;

    size_t chip_ = 100;
    size_t pool_chip_ = 0;
};
