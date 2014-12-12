#include "card.hpp"
#include <curses.h>
#include <fstream>

card::card(const suit s, const std::size_t r)
    :suit_(s), rank_(r)
{
    std::ifstream ifs("cards/" + std::to_string(static_cast<int>(suit_)) + "_" + std::to_string(rank_) + ".txt");

    std::string buffer;
    while(std::getline(ifs, buffer))
    {
        width_ = std::max(width_, buffer.size());
        contents_ += "\n" + buffer;
    }
    height_ = contents_.size();
}

std::string card::to_string()const
{
    return contents_;
}
