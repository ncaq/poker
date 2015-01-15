#include "card_window.hpp"

card_window::card_window(const card& m, const size_t y, const size_t x, const bool hide)
    : nctk::window(y, x)
    , model_(m)
    , hide_(hide)
{
    // 2次元配列みたいに切り出す
    const size_t split_begin = card_line_ * 4 * (13 - this->model_.rank());
    const size_t suit_distance =
        (this->model_.suit() == suit_t::club)    ? 0 * card_line_:
        (this->model_.suit() == suit_t::diamond) ? 1 * card_line_:
        (this->model_.suit() == suit_t::heart)   ? 2 * card_line_:
        (this->model_.suit() == suit_t::spade)   ? 3 * card_line_:
        throw std::range_error("suit_t is range out");

    this->card_cache_ = this->split(split_begin + suit_distance);
    if(this->hide_)
    {
        this->set_contents(hide_card_cache_);
    }
    else
    {
        this->set_contents(this->card_cache_);
    }
}

card_window::~card_window(){}

void card_window::set_hide(bool hide)
{
    this->hide_ = hide;
    if(this->hide_)
    {
        this->set_contents(hide_card_cache_);
    }
    else
    {
        this->set_contents(this->card_cache_);
    }
}

bool card_window::operator<(const card_window& take)const
{
    return this->model_ < take.model_;
}

bool card_window::operator==(const card_window& take)const
{
    return this->model_ == take.model_;
}

bool card_window::operator!=(const card_window& take)const
{
    return this->model_ != take.model_;
}

std::vector<std::string> card_window::split(const size_t index)const
{
    return std::vector<std::string>(card_texture_.begin() + index, card_texture_.begin() + index + card_line_);
}

const std::vector<std::string> card_window::card_texture_ = nctk::read_texture("resource/cards.txt");

const std::vector<std::string> card_window::hide_card_cache_ = nctk::read_texture("resource/hide_card.txt");
