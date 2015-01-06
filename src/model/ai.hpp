#pragma once

#include "actor.hpp"

class ai : public actor
{
public:
    virtual std::deque<bool> select_changing_cards();
    virtual void raise();
    virtual bool call(const size_t );

private:
};
