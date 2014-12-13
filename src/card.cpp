#include "card.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>

std::unique_ptr<card::image_cell> card::sprite_;

card::card(const suit s, const size_t r)
{
    if(!sprite_)
    {
        sprite_.reset(new image_cell("cards.txt"));
    }

    // todo
    this->suit_   = s;
    this->rank_   = r;
    this->height_ = 10;
    this->width_  = 10;
    this->view_   = sprite_->split(height_, width_, 0, 0);
}

std::string card::to_string()const
{
    return view_;
}

card::image_cell::image_cell(const std::string& path)
{
    std::ifstream ifs(path);

    std::string buffer;
    while(std::getline(ifs, buffer))
    {
        lines_.push_back(buffer);
    }
}

std::string card::image_cell::split(const size_t l, const size_t c, const size_t y, const size_t x)
{
    std::string result;
    for(size_t i = y; i < y + l; ++i)
    {
        result += lines_.at(i).substr(x, c) + "\n";
    }
    return result;
}
