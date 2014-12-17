#include "card.hpp"
#include <codecvt>
#include <curses.h>
#include <fstream>
#include <iostream>

card::image_cell card::sprite_ = card::image_cell("cards.txt");

card::card(const suit s, const size_t r)
{
    this->suit_   = s;
    this->rank_   = r;
    this->height_ = 9;
    this->width_  = 11;
    const size_t y = this->height_ * (13 - this->rank_);
    const size_t x =
        (this->suit_ == suit::club)    ?  0 :
        (this->suit_ == suit::diamond) ? 11 :
        (this->suit_ == suit::heart)   ? 22 :
        33 ;
    this->view_   = sprite_.split(height_, width_, y, x);
}

bool card::operator<(const card& take)const
{
    if(this->rank_ == take.rank_)
    {
        return this->suit_ < take.suit_;
    }
    else
    {
        const size_t this_rotated_rank = (this->rank_ == 1) ? 14 : this->rank_; // 1を14として計算する
        const size_t take_rotated_rank = (take. rank_ == 1) ? 14 : take. rank_;
        return this_rotated_rank < take_rotated_rank;
    }
}

card::card(const card& take)
    :suit_(take.suit_), rank_(take.rank_), height_(take.height_), width_(take.width_), view_(take.view_)
{
}

bool card::operator==(const card& take)const
{
    return this->suit_ == take.suit_ && this->rank_ == take.rank_;
}

std::string card::to_string()const
{
    return view_;
}

card::image_cell::image_cell(const std::string& path)
{
    std::ifstream ifs(path);

    std::string buffer;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    while(std::getline(ifs, buffer))
    {
        lines_.push_back(cv.from_bytes(buffer));
    }
}

std::string card::image_cell::split(const size_t l, const size_t c, const size_t y, const size_t x)
{
    std::string result;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    for(size_t i = y; i < y + l; ++i)
    {
        result += cv.to_bytes(lines_.at(i).substr(x, c));
    }
    return result;
}
