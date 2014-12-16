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
            return 11;
        }

    private:
        static std::ifstream ifs;
        static std::string view_;
    };
    
    template <typename T>
    class box_cursors
    {
    public:
        box_cursors()
            :hover_cursor_(0)
        {};
        
        void bind(const std::vector<box<T>>& h)
        {
            std::copy(h.begin(), h.end(), this->hand_.end());
        }

        void draw()
        {
            for(size_t i = 0; i < hand_.size(); ++i)
            {
                if(std::find(selected_.begin(), selected_.end(), i) != selected_.end())
                {
                    hand_.at(i).make_under(arrow()).draw();
                }
            }
            if(!hand_.empty())
            {                
                hand_.at(hover_cursor_).make_under(arrow()).draw();
            }
        }

        void toggle()
        {
            auto may_found = std::find(selected_.begin(), selected_.end(), this->hover_cursor_);
            if(may_found == selected_.end()) // 未登録
            {
                selected_.push_back(this->hover_cursor_);
            }
            else
            {
                selected_.erase(may_found);
            }
        }

        void shift_to_right()
        {
            if(hover_cursor_ <= hand_.size())
            {
                hover_cursor_ = 0;
            }
            else
            {
                ++hover_cursor_;
            }
        }

        void shift_to_left()
        {
            if(0 <= hover_cursor_)
            {
                hover_cursor_ = hand_.size() - 1;
            }
            else
            {
                --hover_cursor_;
            }
        }

        std::vector<size_t> selected()
        {
            return this->selected_;
        }

    private:
        const std::vector<box<T>> hand_;
        std::vector<size_t> selected_;
        size_t hover_cursor_;
    };
}
