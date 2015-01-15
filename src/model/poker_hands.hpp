#pragma once

#include "card.hpp"
#include <algorithm>
#include <deque>
#include <memory>

namespace poker                 //<! std::flushと名前が被ったので退避
{
    enum hands_type
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
}

/*!
  手札の役,強い方,よさ気な表示を出してくれます
 */

class poker_hands
{
public:
    poker_hands(const std::deque<std::shared_ptr<card> >& cards);

    std::string readable()const; //!< human readable
    const std::deque<std::shared_ptr<card> >& sorted_cards()const;
    poker::hands_type type()const;

    bool operator==(const poker_hands& take);
    bool operator< (const poker_hands& take); //!< 役が同じなら,一番高いカードの価値で判定する

    static poker::hands_type from_cards(const std::deque<std::shared_ptr <card> >& sorted_cards);

private:
    std::deque<std::shared_ptr<card> > sorted_cards_;
    poker::hands_type type_;
};
