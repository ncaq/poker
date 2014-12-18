#include "basic_window.hpp"

namespace nctk
{
    basic_window::basic_window(WINDOW* win)
        :window_ptr_(win)
    {
    }

    basic_window::~basic_window()
    {
        delwin(window_ptr_);
    }

    void basic_window::echo(const std::string& str)
    {
        wclear(*this);
        wrefresh(*this);
        waddstr(*this, str.data());
        wrefresh(*this);
    }

    void basic_window::clear()
    {
        wclear(*this);
        wrefresh(*this);
    }

    char basic_window::get_char()
    {
        return wgetch(*this);
    }

    basic_window::operator WINDOW*()
    {
        return window_ptr_;
    }

    basic_window::operator const WINDOW*()const
    {
        return window_ptr_;
    }

    void basic_window::yx(const size_t y, const size_t x)
    {
        mvwin(*this, y, x);
    }

    void basic_window::y(const size_t y)
    {
        this->yx(y, this->x());
    }

    void basic_window::x(const size_t x)
    {
        this->yx(this->y(), x);
    }

    size_t basic_window::y()const
    {
        return getbegy(window_ptr_); // Preprocessor Macroなのが原因なのか,型変換効かない
    }

    size_t basic_window::x()const
    {
        return getbegx(window_ptr_);
    }

    size_t basic_window::under()const
    {
        return y() + getmaxy(window_ptr_);
    }

    size_t basic_window::right()const
    {
        return x() + getmaxx(window_ptr_);
    }
}
