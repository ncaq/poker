#pragma once

#include "card.hpp"
#include <deque>
#include <vector>
#include <cassert>

class poker_manager
{
public:
    poker_manager();

    void deal(const size_t limit);
    void init_deal();
    void exchange(const std::vector<bool>& selected);

    std::vector<card> hand()const;

private:
    std::deque<card> deck_;     // 山札
    std::vector<card> hand_;     // 手札(一人用)
};

void test_exchange();
