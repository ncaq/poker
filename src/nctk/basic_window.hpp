#pragma once

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <cmath>
#include <curses.h>
#include <functional>
#include <string>
#include <unistd.h>
#include <vector>

namespace nctk
{
    template<typename ShowAble>
    class basic_window
    {
    public:
        basic_window(WINDOW* win, const std::shared_ptr<ShowAble> init = std::make_shared<ShowAble>())
            : window_ptr_(win)
            , distination_y_(getbegy(win)) // コンストラクタに入らないとインスタンス関数は使えない
            , distination_x_(getbegx(win))
            , contents_(init)
        {}

        virtual ~basic_window()
        {
            delwin(window_ptr_);
        }

        void set_contents(const ShowAble input)
        {
            this->contents_ = std::make_shared<ShowAble>(input);
        }

        void set_reference(const std::shared_ptr<ShowAble> input)
        {
            this->contents_.reset(input);
        }

        virtual bool draw()
        {
            bool done = this->increase_moving();
            waddstr(*this, this->show_contents().data());
            wrefresh(*this);
            return done;
        }

        void clear()
        {
            wclear(*this);
            wrefresh(*this);
        }

        char get_char()
        {
            return wgetch(*this);
        }

        std::string get_string()
        {
            char buffer[256] = {};
            wgetnstr(*this, buffer, 255);
            return std::string(buffer);
        }

        void move_while_drawing(const size_t to_y, const size_t to_x)
        {
            this->distination_y_ = to_y;
            this->distination_x_ = to_x;
        }

        void place_to_right(basic_window& take)const
        {
            take.move_while_drawing(this->distination_y_, this->right());
        }

        template <typename Window>
        Window make_under(std::function<Window(const size_t, const size_t)> maker)const
        {
            return maker(this->under(), this->distination_x_);
        }

        template <typename Window>
        Window make_right(std::function<Window(const size_t, const size_t)> maker)const
        {
            return maker(this->distination_y_, this->right());
        }

        void yx(const size_t y, const size_t x)
        {
            mvwin(*this, y, x);
        }

        void y(const size_t y)
        {
            this->yx(y, this->x());
        }

        void x(const size_t x)
        {
            this->yx(this->y(), x);
        }

        void resize(const size_t h, const size_t w)
        {
            wresize(window_ptr_, h, w);
        }

        void align_window()
        {
            std::vector<std::string> lines;
            auto text = this->show_contents();
            boost::algorithm::split(lines, text, boost::is_any_of("\n"));
            this->resize(
                lines.size(),
                std::max_element(lines.begin(), lines.end(),
                                 [](const std::string a, std::string b)
                                 {
                                     return a.size() < b.size();
                                 })->size());
        }

        size_t y()const
        {
            return getbegy(window_ptr_); // Preprocessor Macroなのが原因なのか,型変換が効かない
        }

        size_t x()const
        {
            return getbegx(window_ptr_);
        }

        size_t height()const
        {
            return getmaxy(window_ptr_);
        }

        size_t width()const
        {
            return getmaxx(window_ptr_);
        }

        size_t under()const
        {
            return this->distination_y_ + this->height();
        }

        size_t right()const
        {
            return this->distination_x_ + this->width();
        }

        std::string show_contents()const
        {
            return boost::lexical_cast<std::string>(*this->contents_);
        }

        basic_window<ShowAble>& operator+=(const ShowAble& input)
        {
            *(this->contents_) += input;
            return *this;
        }

        operator WINDOW*()
        {
            return window_ptr_;
        }

        operator const WINDOW*()const
        {
            return window_ptr_;
        }

    private:
        bool increase_moving()
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

        WINDOW* window_ptr_;
        size_t distination_y_, distination_x_;
        std::shared_ptr<ShowAble> contents_;
    };
}
