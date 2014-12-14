#include "card.hpp"
#include <deque>

class poker_manager
{
public:
    poker_manager();

private:
    std::deque<card> stocks_;     // 山札
};
