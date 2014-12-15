#include "poker_manager.hpp"
#include <algorithm>
#include <random>

poker_manager::poker_manager()
{
    auto push_card = [this](const suit s)
        {
            for(size_t r = 0; r <= 13; ++r)
            {
                this->deck_.push_back(card(s, r));
            }
        };
    push_card(suit::spade);
    push_card(suit::heart);
    push_card(suit::club);
    push_card(suit::diamond);

    std::random_device init_seed;
    std::shuffle(this->deck_.begin(), this->deck_.end(), std::mt19937(init_seed()));
    // std::random_shuffleはstd::rand()使ってるのでC++14から非推奨になる
}

void poker_manager::deal(const size_t limit)
{
    for(size_t i = 0; i < limit && !hand_.empty(); ++i)
    {
        hand_.push_back(deck_.back());
        deck_.pop_back();
    }
}

void poker_manager::init_deal()
{
    deal(5);
}

void poker_manager::exchange(const std::vector<size_t>& selected)
{
    std::vector<card> stash;
    for(size_t i = 0; i < selected.size(); ++i)
    {
        stash.push_back(deck_.front());
        deck_.pop_front();
    }
    for(auto exchange_iterator = selected.begin(); exchange_iterator != selected.end(); ++exchange_iterator)
    {
        std::swap(hand_.at(*exchange_iterator), stash.at(std::distance(selected.begin(), exchange_iterator)));
    }
    for(auto s : stash)
    {
        deck_.push_back(s);
    }
}
