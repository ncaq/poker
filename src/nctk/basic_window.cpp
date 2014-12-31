#include "basic_window.hpp"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <cmath>
#include <unistd.h>
#include <vector>

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

    void basic_window::align_window()
    {
        size_t lines, max_column;
        std::vector<std::string> stash;
        boost::algorithm::split(stash, contents_, boost::is_any_of("\n"));
        lines = stash.size();
        max_column = std::max_element(stash.begin(), stash.end(),
                                      [](const std::string a, std::string b)
                                      {
                                          return a.size() < b.size();
                                      })->size();
        resize(lines, max_column);
    }
    
    bool basic_window::draw()
    {
        this->clear();
        bool done = this->increase_moving();
        waddstr(*this, this->contents_.data());
        wrefresh(*this);
        return done;
    }

    void basic_window::clear()
    {
        wclear(*this);
        wrefresh(*this);
    }

    void basic_window::move_while_drawing(const size_t distination_y_, const size_t distination_x_)
    {
        this->distination_y_ = distination_y_;
        this->distination_x_ = distination_x_;
    }

    void basic_window::place_other_window_to_right_while_drawing(basic_window& take)const
    {
        take.move_while_drawing(this->y(), this->right());
    }
    
    char basic_window::get_char()
    {
        return wgetch(*this);
    }

    std::string basic_window::get_string()
    {
        char buffer[256] = {};
        wgetnstr(*this, buffer, 255);
        return std::string(buffer);
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

    void basic_window::resize(const size_t h, const size_t w)
    {
        wresize(window_ptr_, h, w);
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
        const int sy = std::ceil((distination_y_ - this->y()) / 5);
        const int sx = std::ceil((distination_x_ - this->x()) / 5);
        if(std::signbit(sy))
        {
            if(distination_y_ < this->y() + sy - 1)
            {
                this->y(this->y() + sy - 1);
            }
            else
            {
                this->y(distination_y_);
            }
        }
        else
        {
            if(this->y() + sy + 1 < distination_y_)
            {
                this->y(this->y() + sy + 1);
            }
            else
            {
                this->y(distination_y_);
            }
        }
        if(std::signbit(sx))
        {
            if(distination_x_ < this->x() + sx - 1)
            {
                this->x(this->x() + sx - 1);
            }
            else
            {
                this->x(distination_x_);
            }
        }
        else
        {
            if(this->x() + sx + 1 < distination_x_)
            {
                this->x(this->x() + sx + 1);
            }
            else
            {
                this->x(distination_x_);
            }
        }
        return (this->y() == this->distination_y_ && this->x() == this->distination_x_);
    }
}
