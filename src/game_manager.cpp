#include "game_manager.hpp"
#include <algorithm>
#include <random>

game_manager::game_manager()
{
    auto push_card = [this](const suit_t s)
        {
            for(size_t r = 1; r <= 13; ++r)
            {
                this->deck_.push_back(std::make_shared<card>(s, r));
            }
        };
    push_card(suit_t::spade);
    push_card(suit_t::heart);
    push_card(suit_t::club);
    push_card(suit_t::diamond);

    std::random_device init_seed;
    std::shuffle(this->deck_.begin(), this->deck_.end(), std::mt19937(init_seed()));
    // std::random_shuffleはstd::rand()使ってるのでC++14から非推奨になる
}

void game_manager::deal(const size_t limit)
{
    for(size_t i = 0; i < limit && !deck_.empty(); ++i)
    {
        hand_.push_back(deck_.back());
        deck_.pop_back();
    }
    std::sort(hand_.begin(), hand_.end());
}

void game_manager::init_deal()
{
    deal(5);
}

void game_manager::exchange(const std::deque<bool>& selected)
{
    std::deque<std::shared_ptr<card> > stash;
    const size_t changed_size = std::count(selected.begin(), selected.end(), true);
    std::move(deck_.begin(), deck_.begin() + changed_size, std::back_inserter(stash));
    deck_.erase(deck_.begin(), deck_.begin() + changed_size);

    auto stock_top = stash.begin();           // 山札のトップ
    for(size_t hand_index = 0; hand_index < selected.size(); ++hand_index)
    {
        if(selected.at(hand_index))
        {
            hand_.at(hand_index).swap(*stock_top);
            ++stock_top;
        }
    }
    std::copy(stash.begin(), stash.end(), std::back_inserter(deck_));
    std::sort(hand_.begin(), hand_.end());
}

std::deque<std::shared_ptr<card> > game_manager::hand()const
{
    return hand_;
}

#include <cassert>

void test_exchange()
{
    game_manager p;
    p.init_deal();
    for(size_t i = 0; i < 5; ++i)
    {        
        std::deque<bool> s = {false, false, false, false, false};
        s.at(i) = true;
        auto old_hand = p.hand();
        p.exchange(s);
        auto new_hand = p.hand();
        assert(!(old_hand.at(i) == new_hand.at(i)));
    }
}
