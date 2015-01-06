#pragma once

#include "actor.hpp"

class ai : public actor
{
public:
    virtual std::deque<bool> select_changing_cards()
    {
        return {0, 1};          // todo
    };

    virtual void raise()
    {
        this->pay(5);               // todo
    }

    virtual bool call(const size_t )
    {
        return true;            // todo
    }

private:
};
