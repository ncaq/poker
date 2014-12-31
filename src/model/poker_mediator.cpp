#include "../view/player_area.hpp"
#include "poker_mediator.hpp"
#include <algorithm>
#include <random>

poker_mediator::poker_mediator(player_area& player_input)
    : player_(player_input)
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

game_state poker_mediator::bet_ante()
{
    if(player_.pay(ante))
    {
        return game_state::ai_win;
    }
    pool += ante;
    if(ai_.pay(ante))
    {
        return game_state::player_win;
    }
    pool += ante;
    return game_state::playing;
}

void poker_mediator::init_deal()
{
    {
        std::deque<std::shared_ptr<card> > player_stash;
        for(size_t i = 0; i < 5 && !deck_.empty(); ++i, deck_.pop_front())
        {
            player_stash.push_back(deck_.front());
        }
        player_.init_deal(player_stash);
    }
    {
        std::deque<std::shared_ptr<card> > ai_stash;
        for(size_t i = 0; i < 5 && !deck_.empty(); ++i, deck_.pop_front())
        {
            ai_stash.push_back(deck_.front());
        }
        ai_.init_deal(ai_stash);
    }
}

void poker_mediator::exchange()
{
    player_.exchange(deck_);
    ai_.exchange(deck_);
}

void poker_mediator::raise()
{
    if(player_.pool_chip() == ai_.pool_chip())
    {
        return;
    }
    else if(player_.pool_chip() < ai_.pool_chip())
    {
        player_.raise();
    }
    else
    {
        ai_.raise();
    }
}

void poker_mediator::call()
{
    if(player_.pool_chip() == ai_.pool_chip())
    {
        return;
    }
    else if(player_.pool_chip() < ai_.pool_chip())
    {
        player_.call();
    }
    else
    {
        ai_.call();
    }
}

void poker_mediator::payoff()
{
    
}

std::deque<std::shared_ptr<card> > poker_mediator::player_hand()const
{
    return player_.hand();
}

std::deque<std::shared_ptr<card> > poker_mediator::ai_hand()const
{
    return ai_.hand();
}
