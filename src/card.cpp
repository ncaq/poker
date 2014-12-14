#include "card.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>

card::image_cell card::sprite_ = card::image_cell("cards.txt");

card::card(const suit s, const size_t r)
{
    // todo
    this->suit_   = s;
    this->rank_   = r;
    this->height_ = 9;
    this->width_  = 11;
    const size_t x =
        (s == suit::club)    ?  0 :
        (s == suit::diamond) ? 11 :
        (s == suit::heart)   ? 22 :
        33 ;
    this->view_   = sprite_.split(height_, width_, 0, x);
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
    for(size_t i = y; i <= y + l; ++i)
    {
        result += lines_.at(i).substr(x, c);
    }
    return result;
}
