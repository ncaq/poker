#pragma once

#include "card.hpp"
#include <deque>
#include <memory>

class game_manager
{
public:
    game_manager();

    void deal(const size_t limit);
    void init_deal();
    void exchange(const std::deque<bool>& selected);

    std::deque<std::shared_ptr<card> > hand()const;

private:
    std::deque<std::shared_ptr<card> > deck_;     // 山札
    std::deque<std::shared_ptr<card> > hand_;     // 手札(一人用)
};

void test_exchange();
