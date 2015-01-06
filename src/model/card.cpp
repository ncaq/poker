#include "card.hpp"
#include <boost/lexical_cast.hpp>

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
        return this->rotated_rank() < take.rotated_rank();
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

std::string card::readable()const
{
    std::string suit_view =
        (this->suit() == suit_t::spade  ) ? "spade  " :
        (this->suit() == suit_t::heart  ) ? "heart  " :
        (this->suit() == suit_t::club   ) ? "club   " :
        (this->suit() == suit_t::diamond) ? "diamond" :
        throw std::range_error("undefined suit");
    std::string rank_view = boost::lexical_cast<std::string>(this->rank());
    return "suit: " + suit_view + ", rank: " + rank_view;
}

size_t card::rotated_rank()const
{
    return (this->rank() == 1) ? 14 : this->rank();
}

suit_t card::suit()const
{
    return this->suit_;
}

size_t card::rank()const
{
    return this->rank_;
}
