#include "basic_window.hpp"

namespace nctk
{
    basic_window::basic_window(WINDOW* win, const size_t lines, const size_t cols, const size_t y, const size_t x)
        :window_ptr_(win), height_(lines), width_(cols), y_(y), x_(x)
    {
    }

    basic_window::~basic_window()
    {
        delwin(window_ptr_);
    }

    void basic_window::add_string(const std::string& str)
    {
        wclear(*this);
        wrefresh(*this);
        waddstr(*this, str.data());
    }

    basic_window::operator WINDOW*()
    {
        return window_ptr_;
    }

    void basic_window::yx(const size_t y, const size_t x)
    {
        y_ = y;
        x_ = x;
        mvwin(*this, y_, x_);
    }
        
    size_t basic_window::y(const size_t n)
    {
        yx(n, x_);
        return y_;
    }

    size_t basic_window::x(const size_t n)
    {
        yx(y_, n);
        return x_;
    }
    
    size_t basic_window::y()const
    {
        return y_;
    }

    size_t basic_window::x()const
    {
        return x_;
    }

    size_t basic_window::under()const
    {
        return y_ + height_;
    }

    size_t basic_window::right()const
    {
        return x_ + width_;
    }
}
