#include "ai.hpp"
#include "poker_hands.hpp"

ai::ai()
    : init_seed()
    , random(init_seed())
{}

std::deque<bool> ai::select_changing_cards()
{
    const poker_hands current_hands = this->show_down();
    if(straight <= current_hands.type()) // 入れ替える余地がないならそのまま
    {
        return std::deque<bool>(5, false);
    }
    else                        // ペアを保持する
    {
        std::deque<bool> selected(5, true);
        for(size_t found = 0; found < current_hands.sorted_cards().size(); ++found)
        {
            for(size_t i = found + 1; i < current_hands.sorted_cards().size(); ++i)
            {
                if(current_hands.sorted_cards().at(found)->rank() == current_hands.sorted_cards().at(i)->rank())
                {
                    selected.at(found) = false;
                    selected.at(i) = false;
                }
            }
        }
        if(std::find(selected.begin(), selected.end(), false) != selected.end()) // ペアがあればそれ以外を交換
        {
            return selected;
        }
        else                    // ペアがないならflush狙いで最大マークを保持
        {
            std::map<suit_t, size_t> suits_size = 
                {
                    {spade, 0},
                    {heart, 0},
                    {club, 0},
                    {diamond, 0},
                };
            for(const auto& c : current_hands.sorted_cards())
            {
                ++suits_size.at(c->suit());
            }
            suit_t max_suit = std::max_element(suits_size.begin(), suits_size.end(),
                                               [](const std::pair<suit_t, size_t> a, const std::pair<suit_t, size_t> b)
                                               {return a.second < b.second;})->first;
            for(size_t i = 0;i < current_hands.sorted_cards().size(); ++i)
            {
                if(current_hands.sorted_cards().at(i)->suit() == max_suit)
                {
                    selected.at(i) = false;
                }
            }
            return selected;
        }
    }
}

size_t ai::raise()
{
    const poker_hands_type current_hands_type = this->show_down().type();
    if(full_house <= current_hands_type)
    {
        return std::binomial_distribution<>(20, 0.95)(random);
    }
    else if(three_cards <= current_hands_type)
    {
        return std::binomial_distribution<>(20, 0.8)(random);
    }
    else
    {
        if(two_pair <= current_hands_type)
        {
            return std::normal_distribution<>(10, 0.5)(random);
        }
        else if(one_pair <= current_hands_type)
        {
            return std::normal_distribution<>(5, 0.5)(random);
        }
        else
        {
            return std::normal_distribution<>(0, 0.5)(random);
        }
    }
}

bool ai::call(const size_t enemy_pool)
{
    const poker_hands_type current_hands_type = this->show_down().type();
    if(three_cards <= current_hands_type)
    {
        return true;
    }
    else
    {
        if(current_hands_type == two_pair && enemy_pool <= std::normal_distribution<>(10, 0.5)(random))
        {
            return true;
        }
        else if(current_hands_type == one_pair && enemy_pool <= std::normal_distribution<>(5, 0.5)(random))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
