#include "card.hpp"
#include "poker_hands.hpp"
#include <numeric>

poker_hands::poker_hands(const std::deque<std::shared_ptr<card> >& cards)
{
    std::deque<std::shared_ptr<card> > stash_cards = cards;
    std::sort(stash_cards.begin(), stash_cards.end());
    this->sorted_cards_ = stash_cards;
    this->type_ = poker_hands::from_cards(sorted_cards_);
}

bool poker_hands::operator==(const poker_hands& take)
{
    return this->card_ranking_compare(take);
}

bool poker_hands::operator<(const poker_hands& take)
{
    if(this->type_ == take.type_)
    {
        return this->card_ranking_compare(take);
    }
    else
    {
        return this->type_ < take.type_;
    }
}

bool poker_hands::card_ranking_compare(const poker_hands& take)const
{
    return std::lexicographical_compare(this->sorted_cards_.rbegin(), this->sorted_cards_.rend(),
                                        take. sorted_cards_.rbegin(), take. sorted_cards_.rend());
}

poker_hands_type poker_hands::from_cards(const std::deque<std::shared_ptr <card> >& sorted_cards)
{
    bool is_flush = std::find_if_not(sorted_cards.begin() + 1, sorted_cards.end(),
                                     [&sorted_cards](const std::shared_ptr<card>& x)
                                     {
                                         return sorted_cards[0]->suit() == x->suit();
                                     }) == sorted_cards.end();
    bool is_straight = std::accumulate(sorted_cards.begin() + 1, sorted_cards.end(), std::make_pair(true, sorted_cards[0]),
                                       [](const std::pair<bool, std::shared_ptr<card> > a, const std::shared_ptr<card>& b)
                                       {
                                           return std::make_pair(a.first && (a.second->rank() == b->rank() - 1), b);
                                       }).first;
    if(is_flush && is_straight)
    {
        return poker_hands_type::straight_flush;
    }
    bool is_three_cards = false;
    for(auto i = sorted_cards.begin() + 2; i != sorted_cards.end(); ++i)
    {
        is_three_cards |= (*(i - 2))->rank() == (*(i - 1))->rank() == (*i)->rank();
    }
    size_t pairs = 0;
    for(auto found = sorted_cards.begin(); found != sorted_cards.end(); ++found)
    {
        for(auto i = found + 1; i != sorted_cards.end(); ++i)
        {
            if((*found)->rank() == (*i)->rank())
            {
                ++pairs;
            }
        }
    }
    if(is_three_cards && (pairs == 1))
    {
        return poker_hands_type::full_house;
    }
    if(is_flush)
    {
        return poker_hands_type::flush;
    }
    if(is_straight)
    {
        return poker_hands_type::straight;
    }
    if(is_three_cards)
    {
        return poker_hands_type::three_cards;
    }
    if(pairs == 2)
    {
        return poker_hands_type::two_pair;
    }
    if(pairs == 1)
    {
        return poker_hands_type::one_pair;
    }
    return poker_hands_type::no_pair;
}
