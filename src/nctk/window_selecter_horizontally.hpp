#pragma once

#include "new_window.hpp"
#include <deque>
#include <fstream>

namespace nctk
{
    class arrow_view : public new_window<std::string>
    {
    public:
        arrow_view(const size_t y, const size_t x)
            : new_window(6, 12, y, x)
        {
            this->set_contents(immutable_contents_);
        }
        
    private:
        static std::ifstream ifs;
        static const std::string immutable_contents_;
    };
    
    template <typename T>
    class window_selecter_horizontally
    {
    public:
        window_selecter_horizontally(const std::deque<std::shared_ptr<T> >& hs)
            :hover_cursor_(0)
        {
            for(const auto& h : hs)
            {
                hand_.push_back(std::make_pair(h, false));
            }
        }

        void draw()const
        {
            std::function<arrow_view(const size_t, const size_t)> make_arrow_view =
                [this](const size_t y, const size_t x)
                {
                    return arrow_view(y, x);
                };
            for(const auto& h : hand_)
            {
                auto under_area = h.first->make_under(make_arrow_view);
                if(h.second)
                {
                    under_area.draw();
                }
            }
            if(hover_cursor_ < hand_.size())
            {
                hand_.at(hover_cursor_).first->make_under(make_arrow_view).draw();
            }
        }

        void toggle()
        {
            if(hand_.at(hover_cursor_).second) // 登録済み
            {
                hand_.at(hover_cursor_).second = false;
            }
            else
            {
                hand_.at(hover_cursor_).second = true;
            }
        }

        void shift_to_right()
        {
            if(hover_cursor_ < hand_.size() - 1)
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
                hover_cursor_ = hand_.size() - 1;
            }
        }

        bool is_selected(const size_t index)const
        {
            return this->selected_.at(index);
        }

        std::deque<bool> selected_array()const
        {
            std::deque<bool> result;
            std::transform(hand_.begin(), hand_.end(), std::back_inserter(result),
                           [](const may_select_box m)
                           {
                               return m.second;
                           });
            return result;
        }

    private:
        using selected = bool;
        using may_select_box = std::pair<const std::shared_ptr<T>, selected>;
        std::deque<may_select_box> hand_;
        size_t hover_cursor_;
    };
}
