#include "basic_window.hpp"
#include <cmath>
#include <unistd.h>

namespace nctk
{
    basic_window::basic_window(WINDOW* win)
        : window_ptr_(win)
        , distination_y_(this->y())
        , distination_x_(this->x())
    {
    }

    basic_window::~basic_window()
    {
        delwin(window_ptr_);
    }

    basic_window& basic_window::set_contents(const std::string& input)
    {
        this->contents_ = input;
        return *this;
    }
    
    bool basic_window::draw()
    {
        wclear(*this);
        wrefresh(*this);
        waddstr(*this, this->contents_.data());
        wrefresh(*this);
        return this->increase_moving();
    }

    void basic_window::clear()
    {
        wclear(*this);
        wrefresh(*this);
    }

    void basic_window::move_while_drawing(const size_t to_y, const size_t to_x) // todo: 同時に移動できるように書き換えます
    {
        while(to_y != this->y() || to_x != this->x())
        {
            wclear(*this);
            wrefresh(*this);
            const int sy = std::ceil((to_y - this->y()) / 5);
            const int sx = std::ceil((to_x - this->x()) / 5);
            if(std::signbit(sy))
            {
                if(to_y < this->y() + sy - 1)
                {
                    this->y(this->y() + sy - 1);
                }
                else
                {
                    this->y(to_y);
                }
            }
            else
            {
                if(this->y() + sy + 1 < to_y)
                {
                    this->y(this->y() + sy + 1);
                }
                else
                {
                    this->y(to_y);
                }
            }
            if(std::signbit(sx))
            {
                if(to_x < this->x() + sx - 1)
                {
                    this->x(this->x() + sx - 1);
                }
                else
                {
                    this->x(to_x);
                }
            }
            else
            {
                if(this->x() + sx + 1 < to_x)
                {
                    this->x(this->x() + sx + 1);
                }
                else
                {
                    this->x(to_x);
                }
            }
            this->draw();
            usleep(20000);
        }
    }

    void basic_window::place_other_window_to_right_while_drawing(basic_window& take)const
    {
        take.move_while_drawing(this->y(), this->right());
    }
    
    char basic_window::get_char()
    {
        return wgetch(*this);
    }

    std::shared_ptr<basic_window> basic_window::make_under(std::function<std::shared_ptr<basic_window>(const size_t, const size_t)> maker)
    {
        return maker(this->under(), this->x());
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

    size_t basic_window::height()const
    {
        return getmaxy(window_ptr_);
    }

    size_t basic_window::width()const
    {
        return getmaxx(window_ptr_);
    }

    size_t basic_window::under()const
    {
        return y() + getmaxy(window_ptr_);
    }

    size_t basic_window::right()const
    {
        return x() + getmaxx(window_ptr_);
    }

    bool basic_window::increase_moving() // wip
    {
        return (this->y() == this->distination_y_ && this->x() == this->distination_x_);
    }
}
