#include "undefined_card_view.hpp"
#include <fstream>

undefined_card_view::undefined_card_view(const size_t y, const size_t x)
    : new_window(9, 12, y, x)
{
    this->set_contents(immutable_contents_);
}

std::ifstream ifs("undefined_card.txt");
const std::string undefined_card_view::immutable_contents_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
