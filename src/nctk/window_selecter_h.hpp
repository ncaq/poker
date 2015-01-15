#pragma once

#include "window_list.hpp"
#include <deque>
#include <fstream>

namespace nctk
{
    class arrow_window : public window
    {
    public:
        arrow_window(const size_t y, const size_t x);

    private:
        static const std::vector<std::string> immutable_contents_;
    };

    template<typename WindowDerived>
    class window_selecter_h : public window
    {
    public:
        window_selecter_h(const window_list<WindowDerived>& hs)
            : list_(hs)
            , selected_(list_.size(), false)
            , hover_cursor_(0)
        {}

        virtual ~window_selecter_h(){}

        virtual bool draw()
        {
            this->clear();
            for(size_t i = 0; i < this->list_.size(); ++i)
            {
                if(this->selected_.at(i))
                {
                    this->add(std::make_shared<arrow_window>(list_.at(i)->under(), list_.at(i)->x()));
                }
            }
            if(this->hover_cursor_ < this->list_.size())
            {
                this->add(std::make_shared<arrow_window>(this->list_.at(this->hover_cursor_)->under(), this->list_.at(this->hover_cursor_)->x()));
            }
            return window::draw();
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
        const window_list<WindowDerived>& list_;
        std::deque<bool> selected_;
        size_t hover_cursor_;
    };
}
