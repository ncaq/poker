#pragma once

#include <algorithm>
#include <deque>
#include <memory>

class card;

enum poker_hands_type
{
    no_pair,
    one_pair,
    two_pair,
    three_cards,
    straight,
    flush,
    full_house,
    four_cards,
    straight_flush,
};

class poker_hands
{
public:
    poker_hands(const std::deque<std::shared_ptr<card> >& cards);

    bool operator==(const poker_hands& take);
    bool operator< (const poker_hands& take);

    std::string readable()const;

    static poker_hands_type from_cards(const std::deque<std::shared_ptr <card> >& sorted_cards);

private:
    std::deque<std::shared_ptr<card> > sorted_cards_;
    poker_hands_type type_;
};
