#include "window_selecter_horizontally.hpp"

namespace nctk
{
    std::ifstream arrow_view::ifs("arrow.txt");
    const std::string arrow_view::immutable_contents_ = std::string(std::istreambuf_iterator<char>(arrow_view::ifs), std::istreambuf_iterator<char>());
}
