#include "window_selecter_h.hpp"

namespace nctk
{
    arrow_window::arrow_window(const size_t y, const size_t x)
        : window(y, x, [](){return immutable_contents_;})
    {}
    const std::vector<std::string> arrow_window::immutable_contents_ = read_texture("resource/arrow.txt");
}
