#pragma once

#include "window.hpp"
#include <deque>
#include <fstream>

namespace nctk
{
    class arrow_view : public window
    {
    public:
        arrow_view(const size_t y, const size_t x)
            : window(6, 12, y, x, [](){return immutable_contents_;})
        {}

    private:
        static std::ifstream ifs;
        static const std::string immutable_contents_;
    };

    template <typename T>
    class window_selecter_horizontally
    {
    public:
        window_selecter_horizontally(const std::deque<std::shared_ptr<T> >& hs)
            : list_(hs)
            , selected_(list_.size(), false)
            , hover_cursor_(0)
        {
        }

        void draw()const
        {
            std::function<arrow_view(const size_t, const size_t)> make_arrow_view =
                [this](const size_t y, const size_t x)
                {
                    return arrow_view(y, x);
                };
            for(size_t i = 0; i < list_.size(); ++i)
            {
                if(selected_.at(i))
                {
                    list_.at(i)->make_under(make_arrow_view).draw();
                }
            }
            if(hover_cursor_ < list_.size())
            {
                list_.at(hover_cursor_)->make_under(make_arrow_view).draw();
            }
        }

        void toggle()
        {
            if(selected_.at(hover_cursor_)) // 登録済み
            {
                selected_.at(hover_cursor_) = false;
            }
            else
            {
                selected_.at(hover_cursor_) = true;
            }
        }

        void shift_to_right()
        {
            if(hover_cursor_ < list_.size() - 1)
            {
                ++hover_cursor_;
            }
            else
            {
                hover_cursor_ = 0;
            }
        }

        void shift_to_left()
        {
            if(0 < hover_cursor_)
            {
                --hover_cursor_;
            }
            else
            {
                hover_cursor_ = list_.size() - 1;
            }
        }

        bool is_selected(const size_t index)const
        {
            return this->selected_.at(index);
        }

        std::deque<bool> selected_array()const
        {
            return selected_;
        }

    private:
        const std::deque<std::shared_ptr<T> >& list_;
        std::deque<bool> selected_;
        size_t hover_cursor_;
    };
}
