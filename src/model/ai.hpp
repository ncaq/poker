#pragma once

#include "actor.hpp"
#include <algorithm>
#include <map>
#include <random>

class ai : public actor         // とりあえず乱数でごまかしている
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
