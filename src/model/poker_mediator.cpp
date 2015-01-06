#include "ai.hpp"
#include "card.hpp"
#include "player.hpp"
#include "poker_mediator.hpp"

poker_mediator::poker_mediator()
    : player_(std::make_shared<player>())
    , ai_(std::make_shared<ai>())
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

void poker_mediator::set_controller(std::shared_ptr<player_area> controller)
{
    this->player_->set_controller(controller);
}

void poker_mediator::new_deal()
{
    {
        std::deque<std::shared_ptr<card> > player_stash;
        for(size_t i = 0; i < 5 && !deck_.empty(); ++i, deck_.pop_front())
        {
            player_stash.push_back(deck_.front());
        }
        player_->new_deal(player_stash);
    }
    {
        std::deque<std::shared_ptr<card> > ai_stash;
        for(size_t i = 0; i < 5 && !deck_.empty(); ++i, deck_.pop_front())
        {
            ai_stash.push_back(deck_.front());
        }
        ai_->new_deal(ai_stash);
    }
}

game_state poker_mediator::bet_ante()
{
    if(player_->pay(ante))
    {
        return game_state::ai_win;
    }
    if(ai_->pay(ante))
    {
        return game_state::player_win;
    }
    return game_state::playing;
}

void poker_mediator::exchange()
{
    player_->exchange(deck_);
    ai_->exchange(deck_);
}

void poker_mediator::raise()
{
    if(player_->pool_chip() == ai_->pool_chip())
    {
        return;
    }
    else if(player_->pool_chip() < ai_->pool_chip())
    {
        player_->raise();
    }
    else
    {
        ai_->raise();
    }
}

void poker_mediator::call()
{
    if(player_->pool_chip() == ai_->pool_chip())
    {
        return;
    }
    else if(player_->pool_chip() < ai_->pool_chip())
    {
        player_->call();
    }
    else
    {
        ai_->call();
    }
}

void poker_mediator::payoff()
{
    auto player_hands = player_->show_down()
        ,ai_hands     = ai_->show_down();
    if(player_hands == ai_hands)
    {
        player_->payoff(*player_->pool_chip());
        ai_->payoff(*ai_->pool_chip());
    }
    else
    {
        auto pool = *player_->pool_chip() + *ai_->pool_chip();
        if(player_hands < ai_hands)
        {
            player_->payoff(0);
            ai_->payoff(pool);
        }
        else
        {
            player_->payoff(pool);
            ai_->payoff(0);
        }
    }
}

std::shared_ptr<player> poker_mediator::player_ptr()const
{
    return this->player_;
}

std::shared_ptr<ai> poker_mediator::ai_ptr()const
{
    return this->ai_;
}
