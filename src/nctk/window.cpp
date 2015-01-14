#include "window.hpp"

namespace nctk
{
    window::window(){}

    window::window(const size_t line, const size_t colu, const size_t y, const size_t x, const std::function<std::string()> init)
        : line_(line)
        , colu_(colu)
        , y_(y)
        , x_(x)
        , to_y_(y_) // コンストラクタに入らないとインスタンス関数は使えない
        , to_x_(x_)
        , contents_(init)
    {}

    window::~window(){};

    bool window::draw()
    {
        bool done = true;
        if(this->contents_)
        {
            done = this->increase_moving() && done;
            display::write(*this);
        }
        for(auto& child : this->children_)
        {
            done = child.second->draw() && done;
        }
        return done;
    }

    void window::erase(const std::string& name)
    {
        this->children_.erase(name);
    }

    void window::clear()
    {
        this->children_.clear();
    }

    void window::move_while_drawing(const size_t to_y, const size_t to_x)
    {
        this->to_y_ = to_y;
        this->to_x_ = to_x;
    }

    void window::place_to_right(window& take)const
    {
        take.move_while_drawing(this->to_y_, this->right());
    }

    void window::align_window()
    {
        size_t line_size = 1, max_col_size = 0, current_col_size = 0;
        for(char c : this->show_contents())
        {
            ++current_col_size;
            if(c == '\n')
            {
                max_col_size = std::max(max_col_size, current_col_size);
                current_col_size = 0;
                ++line_size;
            }
        }
        max_col_size = std::max(max_col_size, current_col_size);
        this->resize(line_size, max_col_size);
    }

    void window::resize(const size_t h, const size_t w)
    {
        this->line_ = h;
        this->colu_ = w;
    }

    std::string window::show_contents()const
    {
        return (this->contents_) ?
            this->contents_() :
            "";
    }

    size_t window::under()const
    {
        return this->y_ + this->line();
    }

    size_t window::to_under()const
    {
        return this->to_y_ + this->line();
    }

    size_t window::right()const
    {
        return this->x_ + this->colu();
    }

    size_t window::to_right()const
    {
        return this->to_x_ + this->colu();
    }

    void window::yx(const size_t y, const size_t x)
    {
        this->y_ = y;
        this->x_ = x;
    }

    void window::y(const size_t y)
    {
        this->yx(y, this->x());
    }

    void window::x(const size_t x)
    {
        this->yx(this->y(), x);
    }

    size_t window::line()const
    {
        return this->line_;
    }

    size_t window::colu()const
    {
        return this->colu_;
    }

    size_t window::y()const
    {
        return this->y_;
    }

    size_t window::x()const
    {
        return this->x_;
    }

    window& window::operator=(const window& take)
    {
        window(take.line(), take.colu(), take.y(), take.x(), take.contents_);
        return *this;
    }

    bool window::increase_moving()
    {
        const int sy = (static_cast<int>(to_y_) - static_cast<int>(this->y())) / 5;
        const int sx = (static_cast<int>(to_x_) - static_cast<int>(this->x())) / 5;
        if(std::signbit(sy))
        {
            if(to_y_ < this->y() + sy)
            {
                this->y(this->y() + sy - 1);
            }
            else
            {
                this->y(to_y_);
            }
        }
        else
        {
            if(this->y() + sy < to_y_)
            {
                this->y(this->y() + sy + 1);
            }
            else
            {
                this->y(to_y_);
            }
        }
        if(std::signbit(sx))
        {
            if(to_x_ < this->x() + sx)
            {
                this->x(this->x() + sx - 1);
            }
            else
            {
                this->x(to_x_);
            }
        }
        else
        {
            if(this->x() + sx < to_x_)
            {
                this->x(this->x() + sx + 1);
            }
            else
            {
                this->x(to_x_);
            }
        }
        return (this->y() == this->to_y_ && this->x() == this->to_x_);
    }

    void swap_and_move(window& a, window& b, std::function<bool()> draw_callback)
    {
        {
            auto t = a;
            a = b;
            b = t;
        }
        a.move_while_drawing(b.y(), b.x());
        b.move_while_drawing(a.y(), a.x());
        while(!draw_callback()){}
    }
}
