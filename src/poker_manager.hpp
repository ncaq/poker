#include "card.hpp"
#include <deque>

class poker_manager
{
public:
    poker_manager();

    void deal(const size_t limit);

private:
    std::deque<card> deck_;     // 山札
    std::deque<card> hand_;     // 手札(一人用)
};
