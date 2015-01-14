#include "window_selecter_h.hpp"

namespace nctk
{
    std::ifstream arrow_window::ifs("resource/arrow.txt");
    const std::string arrow_window::immutable_contents_ = std::string(std::istreambuf_iterator<char>(arrow_window::ifs), std::istreambuf_iterator<char>());
}
