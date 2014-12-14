#include "card.hpp"
#include <deque>

class poker_manager
{
public:
    poker_manager();

private:
    std::deque<card> deck_;     // 山札
    std::deque<card> deal_;     // 手札(一人用)
};
