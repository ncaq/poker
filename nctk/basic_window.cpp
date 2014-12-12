#include "basic_window.hpp"

namespace nctk
{
    basic_window::basic_window(WINDOW* win, const size_t lines, const size_t cols, const size_t y, const size_t x)
        :window_ptr_(win), width_(lines), height_(cols), y_(y), x_(x)
    {
    }

    basic_window::~basic_window()
    {
        delwin(window_ptr_);
    }

    void basic_window::add_string(const std::string& str)
    {
        waddstr(*this, str.data());
    }

    basic_window::operator WINDOW*()
    {
        return window_ptr_;
    }
}
