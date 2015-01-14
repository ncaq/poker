#include "card_window.hpp"

card_window::card_window(const card& m, const size_t y, const size_t x, const bool hide)
    : nctk::window(9, 11, y, x)
    , model_(m)
    , hide_(hide)
{
    // 2次元配列みたいに切り出す
    const size_t split_begin = this->line() * 4 * (13 - this->model_.rank());
    const size_t suit_distance =
        (this->model_.suit() == suit_t::club)    ? 0 * this->line():
        (this->model_.suit() == suit_t::diamond) ? 1 * this->line():
        (this->model_.suit() == suit_t::heart)   ? 2 * this->line():
        (this->model_.suit() == suit_t::spade)   ? 3 * this->line():
        throw std::range_error("suit_t is range out");

    this->card_cache_ = sprite_.split(split_begin + suit_distance);
    if(this->hide_)
    {
        this->set_contents(hide_card_cache_);
    }
    else
    {
        this->set_contents(this->card_cache_);
    }
}

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
const std::string card_window::hide_card_cache_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
