#pragma once

#include "actor.hpp"
#include <functional>


class player : public actor
{
public:
    player();
    virtual ~player();

    virtual std::deque<bool> select_changing_cards();
    virtual size_t raise();
    virtual bool call();
};
