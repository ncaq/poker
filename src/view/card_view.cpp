#include "card_view.hpp"
#include <codecvt>
#include <curses.h>
#include <fstream>
#include <iostream>

card_view::card_view(const std::shared_ptr<card> base, const size_t y, const size_t x)
    : nctk::new_window<std::string>(9, 11, y, x)
    , model_(base)
{
    const size_t split_begin_y = this->height() * (13 - base->rank());
    const size_t split_begin_x =
        (base->suit() == suit_t::club)    ?  0 :
        (base->suit() == suit_t::diamond) ? 11 :
        (base->suit() == suit_t::heart)   ? 22 :
        (base->suit() == suit_t::spade)   ? 33 :
        throw std::range_error("suit_t is range out");
    this->set_contents(this->contents_cache_ = sprite_.split(this->height(), this->width(), split_begin_y, split_begin_x));
}

void card_view::set_hide(bool hide)
{
    if(hide)
    {
        this->set_contents(hide_card_view_);
    }
    else
    {
        this->set_contents(this->contents_cache_);
    }
}

bool card_view::operator<(const card_view& take)const
{
    return *this->model_ < *take.model_;
}

bool card_view::operator==(const card_view& take)const
{
    return *this->model_ == *take.model_;
}

card_view::image_cell card_view::sprite_ = card_view::image_cell("cards.txt");

card_view::image_cell::image_cell(const std::string& path)
{
    std::ifstream ifs(path);

    std::string buffer;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    while(std::getline(ifs, buffer))
    {
        lines_.push_back(cv.from_bytes(buffer));
    }
}

std::string card_view::image_cell::split(const size_t l, const size_t c, const size_t y, const size_t x)
{
    std::string result;
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cv;
    for(size_t i = y; i < y + l; ++i)
    {
        result += cv.to_bytes(lines_.at(i).substr(x, c));
    }
    return result;
}

std::ifstream ifs("hide_card.txt");
const std::string card_view::hide_card_view_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

void swap(card_view& a, card_view& b, std::function<bool()> draw_callback)
{
    a.move_while_drawing(b.y(), b.x());
    b.move_while_drawing(a.y(), a.x());
    while(!draw_callback()){}
}
