#pragma once

#include "box.hpp"
#include <fstream>
#include <vector>

namespace nctk
{
    class arrow
    {
    public:
        std::string to_string()const
        {
            return view_;
        }
        size_t height()const
        {
            return 6;
        }
        size_t width()const
        {
            return 12;          // + '\n'
        }

    private:
        static std::ifstream ifs;
        static std::string view_;
    };
    
    template <typename T>
    class box_cursors
    {
    public:
        box_cursors(const std::vector<box<T>>& hs)
            :hover_cursor_(0)
        {
            for(const auto& h : hs)
            {
                hand_.push_back(std::make_pair(&h, false));
            }
        }

        void draw()const
        {
            for(const auto& h : hand_)
            {
                if(h.second)
                {
                    h.first->make_under(arrow()).draw();
                }
                else
                {
                    h.first->make_under(arrow()).clear();
                }
            }
            if(hover_cursor_ < hand_.size())
            {
                hand_.at(hover_cursor_).first->make_under(arrow()).draw();
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

        std::vector<bool> selected_array()const
        {
            std::vector<bool> result;
            std::transform(hand_.begin(), hand_.end(), std::back_inserter(result),
                           [](const may_select_box m)
                           {
                               return m.second;
                           });
            return result;
        }

    private:
        using selected = bool;
        using may_select_box = std::pair<const box<T>*, selected>;
        std::vector<may_select_box> hand_;
        size_t hover_cursor_;
    };
}
