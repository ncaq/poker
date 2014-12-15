#include "undefined_card.hpp"
#include <fstream>

undefined_card::undefined_card()
{
    std::ifstream ifs("undefined_card.txt");
    this->view_ = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

    this->height_ = 9;
    this->width_  = 11;
}

std::string undefined_card::to_string()const
{
    return view_;
}
