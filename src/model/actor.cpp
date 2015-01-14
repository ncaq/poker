#include "actor.hpp"
#include "card.hpp"

actor::~actor()
{};

void actor::new_deal(std::deque<std::shared_ptr<card> >& deck)
{
    if(hand_.empty())
    {
        for(size_t i = 0; i < 5; ++i)
        {
            hand_.push_back(deck.front());
            deck.pop_front();
        }
    }
    else
    {
        this->exchange_select_cards(deck, {true, true, true, true, true});
    }
}

void actor::exchange(std::deque<std::shared_ptr<card> >& deck)
{
    this->exchange_select_cards(deck, this->select_changing_cards());
}

void actor::exchange_select_cards(std::deque<std::shared_ptr<card> >& deck, const std::deque<bool>& selected)
{
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

void actor::pay(const size_t size)
{
    if(*this->chip_ < size)
    {
        *this->pool_ += *this->chip_;
        *this->chip_ = 0;
    }
    else
    {
        *this->chip_ -= size;
        *this->pool_ += size;
    }
}

void actor::payoff(const size_t paid_chip)
{
    *chip_ += paid_chip;
    *pool_ = 0;
}

poker_hands actor::show_down()const
{
    return poker_hands(hand_);
}

void actor::sort()
{
    std::sort(this->hand_.begin(), this->hand_.end(),[](const std::shared_ptr<card> a, const std::shared_ptr<card>b){return *a < *b;});
}

std::deque<std::shared_ptr<card> >& actor::hand_reffernce()
{
    return this->hand_;
}

std::shared_ptr<size_t> actor::chip()const
{
    return chip_;
}

std::shared_ptr<size_t> actor::pool()const
{
    return pool_;
}
