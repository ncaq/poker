#include "actor.hpp"

actor::actor()
{};

actor::~actor()
{};

void actor::init_deal(std::deque<std::shared_ptr<card> > hand)
{
    hand_ = hand;
}

void actor::exchange(std::deque<std::shared_ptr<card> > deck)
{
    auto selected = this->select_changing_cards();
    std::deque<std::shared_ptr<card> > stash;
    const size_t changed_size = std::count(selected.begin(), selected.end(), true);
    std::move(deck.begin(), deck.begin() + changed_size, std::back_inserter(stash));
    deck.erase(deck.begin(), deck.begin() + changed_size);

    auto stock_top = stash.begin();           // 山札のトップ
    for(size_t hand_index = 0; hand_index < selected.size(); ++hand_index)
    {
        if(selected.at(hand_index))
        {
            hand_.at(hand_index).swap(*stock_top);
            ++stock_top;
        }
    }
    std::copy(stash.begin(), stash.end(), std::back_inserter(deck));
}

bool actor::pay(const size_t size)
{
    if(chip_ < size)
    {
        return true;
    }
    else
    {
        chip_ -= size;
        pool_chip_ += size;
        return false;
    }
}

poker_hands actor::show_down()
{
    return poker_hands(hand_);
}

size_t actor::chip()const
{
    return chip_;
}

size_t actor::pool_chip()const
{
    return pool_chip_;
}

std::deque<std::shared_ptr<card> > actor::hand()const
{
    return hand_;
}
