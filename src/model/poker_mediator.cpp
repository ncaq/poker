#include "card.hpp"
#include "poker_mediator.hpp"

poker_mediator::poker_mediator()
{
    // 山札にカードを振り分ける
    auto push_card = [this](const suit_t s)
        {
            for(size_t r = 1; r <= 13; ++r)
            {
                this->deck_.push_back(std::make_shared<card>(s, r));
            }
        };
    push_card(suit_t::spade);
    push_card(suit_t::heart);
    push_card(suit_t::club);
    push_card(suit_t::diamond);

    std::random_device init_seed;
    std::shuffle(this->deck_.begin(), this->deck_.end(), std::mt19937(init_seed()));
    // std::random_shuffleはstd::rand()使ってるのでC++14から非推奨になる
}

void poker_mediator::set_controller(std::shared_ptr<player_window> controller)
{
    this->player_.set_controller(controller);
}

void poker_mediator::new_deal()
{
    this->player_.new_deal(this->deck_);
    this->ai_    .new_deal(this->deck_);
}

void poker_mediator::bet_ante()
{
    this->player_.pay(ante);
    this->ai_    .pay(ante);
}

void poker_mediator::exchange()
{
    this->player_.exchange(deck_);
    this->ai_    .exchange(deck_);
}

void poker_mediator::raise()
{
    player_.pay(std::min<size_t>(std::max<size_t>(0, player_.raise()), 20));
    ai_    .pay(std::min<size_t>(std::max<size_t>(0, ai_    .raise()), 20));
}

lead poker_mediator::call()
{
    if(*player_.pool() == *ai_.pool())
    {
        return lead::nothing;
    }
    else if(*player_.pool() < *ai_.pool())
    {
        if(player_.call(*ai_.pool()))
        {
            player_.pay(*ai_.pool() - *player_.pool());
            return lead::nothing;
        }
        else
        {
            return lead::ai_lead;
        }
    }
    else
    {
        if(ai_.call(*player_.pool()))
        {
            ai_.pay(*player_.pool() - *ai_.pool());
            return lead::nothing;
        }
        else
        {
            return lead::player_lead;
        }
    }
}
// #include "../nctk/debug_stream.hpp"
void poker_mediator::payoff(const lead no_fold_actor)
{
    // static nctk::debug_stream dout;
    auto pay_to_player = [this](){player_.payoff(this->sum_pool());ai_    .payoff(0);};
    auto pay_to_ai     = [this](){ai_    .payoff(this->sum_pool());player_.payoff(0);};
    if(no_fold_actor == lead::nothing)
    {
        auto high_actor = this->comp_hand();
        if(high_actor == lead::nothing)
        {
            player_.payoff(*player_.pool());
            ai_.payoff(*ai_.pool());
        }
        else
        {
            if(high_actor == lead::player_lead)
            {
                // dout <<
                //     "player" << std::endl <<
                //     "player:" << *player_.pool() << std::endl <<
                //     "ai: " << *ai_.pool() << std::endl;
                pay_to_player();
            }
            else
            {
                // dout <<
                //     "ai" << std::endl <<
                //     "player:" << *player_.pool() << std::endl <<
                //     "ai: " << *ai_.pool() << std::endl;
                pay_to_ai();
            }
        }
    }
    else if(no_fold_actor == lead::player_lead)
    {
        pay_to_player();
    }
    else
    {
        pay_to_ai();
    }
}

lead poker_mediator::comp_hand()const
{
    auto player_hands = this->player_.show_down()
        ,ai_hands     = this->ai_.show_down();
    if(player_hands == ai_hands)
    {
        return lead::nothing;
    }
    else
    {
        if(ai_hands < player_hands)
        {
            return lead::player_lead;
        }
        else
        {
            return lead::ai_lead;
        }
    }
}

size_t poker_mediator::sum_pool()const
{
    return
        *this->player_.pool() +
        *this->ai_.pool();
}

bool poker_mediator::done()const
{
    return
        *this->player_.chip() == 0 ||
        *this->ai_.chip() == 0;
}

lead poker_mediator::current_lead()const
{
    if(*this->player_.chip() == *this->ai_.chip())
    {
        return lead::nothing;
    }
    else if(*this->ai_.chip() < *this->player_.chip())
    {
        return lead::player_lead;
    }
    else
    {
        return lead::ai_lead;
    }
}

player& poker_mediator::player_ref()
{
    return this->player_;
}

ai& poker_mediator::ai_ref()
{
    return this->ai_;
}
