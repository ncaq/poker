#pragma once

#include <string>

enum class suit_t
{spade, heart, club, diamond};

class card
{
public:
    card(const suit_t s, const size_t r);

    bool operator<(const card& take)const;
    bool operator==(const card& take)const;

    suit_t suit()const;
    size_t rank()const;

private:
    suit_t suit_;
    size_t rank_;
};
