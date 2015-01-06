#include "card.hpp"

card::card(const suit_t s, const size_t r)
    : suit_(s)
    , rank_(r)
{
}

bool card::operator<(const card& take)const
{
    if(this->rank() == take.rank())
    {
        return this->suit() < take.suit();
    }
    else
    {
        const size_t this_rotated_rank = (this->rank() == 1) ? 14 : this->rank(); // 1を14として計算する
        const size_t take_rotated_rank = (take. rank() == 1) ? 14 : take. rank();
        return this_rotated_rank < take_rotated_rank;
    }
}

bool card::operator==(const card& take)const
{
    return this->suit() == take.suit() && this->rank() == take.rank();
}

bool card::operator!=(const card& take)const
{
    return this->suit() != take.suit() || this->rank() != take.rank();
}

suit_t card::suit()const
{
    return this->suit_;
}

size_t card::rank()const
{
    return this->rank_;
}
