#pragma once

#include "actor.hpp"
#include <algorithm>
#include <map>
#include <random>

/*!
  明らかに有利なときは大幅に賭ける.
  他は優位性で平均と標準偏差を調整した正規分布.
*/

class ai : public actor
{
public:
    ai();

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call(const size_t enemy_pool);

private:
    static std::random_device init_seed;
    std::mt19937 random;
};
