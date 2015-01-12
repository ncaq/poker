#include "card_window.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>

card_window::card_window(const std::shared_ptr<card> base, const size_t y, const size_t x, const bool hide)
    : nctk::window(9, 11, y, x)
    , model_(base)
    , hide_(hide)
{
    // 2次元配列みたいに切り出す
    const size_t split_begin = this->height() * 4 * (13 - base->rank());
    const size_t suit_distance =
        (base->suit() == suit_t::club)    ? 0 * this->height():
        (base->suit() == suit_t::diamond) ? 1 * this->height():
        (base->suit() == suit_t::heart)   ? 2 * this->height():
        (base->suit() == suit_t::spade)   ? 3 * this->height():
        throw std::range_error("suit_t is range out");

    this->card_contents_cache_ = sprite_.split(split_begin + suit_distance);
    if(this->hide_)
    {
        this->set_contents(hide_card_window_);
    }
    else
    {
        this->set_contents(this->card_contents_cache_);
    }
}

void card_window::set_hide(bool hide)
{
    this->hide_ = hide;
    if(this->hide_)
    {
        this->set_contents(hide_card_window_);
    }
    else
    {
        this->set_contents(this->card_contents_cache_);
    }
}

bool card_window::operator<(const card_window& take)const
{
    return *this->model_ < *take.model_;
}

bool card_window::operator==(const card_window& take)const
{
    return *this->model_ == *take.model_;
}

bool card_window::operator!=(const card_window& take)const
{
    return *this->model_ != *take.model_;
}

card_window::image_cell card_window::sprite_ = card_window::image_cell("resource/cards.txt");

card_window::image_cell::image_cell(const std::string& path)
{
    std::ifstream ifs(path);

    std::string buffer;
    while(std::getline(ifs, buffer))
    {
        lines_.push_back(buffer);
    }
}

std::string card_window::image_cell::split(const size_t index)
{
    std::string result;
    for(size_t i = index; i < index + 9; ++i)
    {
        result += lines_.at(i);
    }
    return result;
}

std::ifstream ifs("resource/hide_card.txt");
const std::string card_window::hide_card_window_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

void swap(card_window& a, card_window& b, std::function<bool()> draw_callback)
{
    {
        card_window t = a;
        a = b;
        b = t;
    }
    a.move_while_drawing(b.y(), b.x());
    b.move_while_drawing(a.y(), a.x());
    while(!draw_callback()){}
}
