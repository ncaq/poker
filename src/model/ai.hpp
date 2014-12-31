#pragma once

#include "actor.hpp"

class ai : public actor
{
public:
    virtual std::deque<bool> select_changing_cards()
    {
        return {0, 1};          // todo
    };

    virtual size_t raise()
    {
        return 5;               // todo
    }

    virtual bool call()
    {
        return true;            // todo
    }

private:
};
