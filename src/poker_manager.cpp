#include "poker_manager.hpp"
#include <algorithm>
#include <random>

poker_manager::poker_manager()
{
    auto push_card = [this](const suit s)
        {
            for(size_t r = 0; r <= 13; ++r)
            {
                this->stocks_.push_back(card(s, r));
            }
        };
    push_card(suit::spade);
    push_card(suit::heart);
    push_card(suit::diamond);
    push_card(suit::club);

    std::random_device init_seed;
    std::shuffle(this->stocks_.begin(), this->stocks_.end(), std::mt19937(init_seed()));
    // std::random_shuffleはstd::rand()使ってるのでC++14から非推奨になる
}
