#include "window.hpp"

namespace nctk
{
    window::window()
        : contents_(default_contents)
    {};

    window::window(const size_t y, const size_t x, const std::function<std::vector<std::string>()> init)
        : y_(y)
        , x_(x)
        , to_y_(y)
        , to_x_(x)
        , contents_(init)
    {}

    window::~window(){};

    bool window::draw()
    {
        bool done = true;
        done = this->increase_moving() && done;
        display::write(*this);
        for(auto& child : this->children_)
        {
            done = child->draw() && done;
        }
        return done;
    }

    void window::erase(const std::shared_ptr<window> w)
    {
        this->children_.erase(w);
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
        take.move_while_drawing(this->to_y_, this->to_right());
    }

    std::vector<std::string> window::show_contents()const
    {
        return (this->contents_) ?
            this->contents_() :
            std::vector<std::string>({""});
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

    size_t window::colu()const
    {
        const auto& cs = this->show_contents();
        const auto& max_it = std::max_element(cs.begin(), cs.end(), [](const std::string& a, const std::string& b){return size_utf8(a) < size_utf8(b);});
        return size_utf8(*max_it);
    }

    size_t window::line()const
    {
        return this->show_contents().size();
    }

    size_t window::y()const
    {
        return this->y_;
    }

    size_t window::to_y()const
    {
        return this->to_y_;
    }

    size_t window::x()const
    {
        return this->x_;
    }

    size_t window::to_x()const
    {
        return this->to_x_;
    }

    size_t window::under()const
    {
        return this->y_ + this->show_contents().size();
    }

    size_t window::to_under()const
    {
        return this->to_y_ + this->show_contents().size();
    }

    size_t window::right()const
    {
        return this->x_ + this->colu();
    }

    size_t window::to_right()const
    {
        return this->to_x_ + this->colu();
    }

    window& window::operator=(const window& take)
    {
        window(take.y(), take.x(), take.contents_);
        return *this;
    }

    bool window::operator<(const window& take)const
    {
        return this->x() < take.x();
    }

    bool window::increase_moving()
    {
        if(this->y() == this->to_y_ && this->x() == this->to_x_)
        {
            return true;
        }
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

    std::vector<std::string> window::default_contents()
    {
        return std::vector<std::string>({""});
    }
}
