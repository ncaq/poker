#include "window.hpp"

namespace nctk
{
    window::window(const size_t lines, const size_t cols, const size_t y, const size_t x, const std::function<std::string()> init)
        : window_ptr_(newwin(lines, cols, y, x), delwin)
        , distination_y_(getbegy(window_ptr_)) // コンストラクタに入らないとインスタンス関数は使えない
        , distination_x_(getbegx(window_ptr_))
        , contents_(init)
    {}

    window::~window(){};

    void window::clear()
    {
        wclear(*this);
        wrefresh(*this);
    }

    bool window::draw()
    {
        wclear(*this);
        bool done = this->increase_moving();
        waddstr(*this, this->show_contents().data());
        for(auto& child : this->children_)
        {
            done = child.second->draw() & done;
        }
        wrefresh(*this);
        return done;
    }

    void window::add(const std::string& name, const std::shared_ptr<window> child)
    {
        this->children_.insert({name, child});
    }

    std::shared_ptr<window> window::lookup(const std::string& name)
    {
        return this->children_.at(name);
    }

    std::string window::get_string()
    {
        char buffer[256] = {};
        wgetnstr(*this, buffer, 255);
        return std::string(buffer);
    }

    char window::get_char()
    {
        return wgetch(*this);
    }

    int window::get_int()
    {
        return std::stoi(this->get_string());
    }

    void window::move_while_drawing(const size_t to_y, const size_t to_x)
    {
        this->distination_y_ = to_y;
        this->distination_x_ = to_x;
    }

    void window::place_to_right(window& take)const
    {
        take.move_while_drawing(this->distination_y_, this->right());
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
        wresize(window_ptr_.get(), h, w);
    }

    std::string window::show_contents()const
    {
        return this->contents_();
    }

    size_t window::under()const
    {
        return this->distination_y_ + this->height();
    }

    size_t window::right()const
    {
        return this->distination_x_ + this->width();
    }

    void window::yx(const size_t y, const size_t x)
    {
        mvwin(*this, y, x);
    }

    void window::y(const size_t y)
    {
        this->yx(y, this->x());
    }

    void window::x(const size_t x)
    {
        this->yx(this->y(), x);
    }

    size_t window::y()const
    {
        return getbegy(window_ptr_.get()); // Preprocessor Macroなのが原因なのか,型変換が効かない
    }

    size_t window::x()const
    {
        return getbegx(window_ptr_.get());
    }

    size_t window::height()const
    {
        return getmaxy(window_ptr_.get());
    }

    size_t window::width()const
    {
        return getmaxx(window_ptr_.get());
    }

    window::operator WINDOW*()
    {
        return this->window_ptr_.get();
    }

    window::operator const WINDOW*()const
    {
        return this->window_ptr_.get();
    }

    bool window::increase_moving()
    {
        const int sy = (static_cast<int>(distination_y_) - static_cast<int>(this->y())) / 5;
        const int sx = (static_cast<int>(distination_x_) - static_cast<int>(this->x())) / 5;
        if(std::signbit(sy))
        {
            if(distination_y_ < this->y() + sy)
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
            if(this->y() + sy < distination_y_)
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
            if(distination_x_ < this->x() + sx)
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
            if(this->x() + sx < distination_x_)
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
