#pragma once

#include "window.hpp"
#include <deque>

namespace nctk
{
    template<typename WindowDerived>
    class window_list : public window
    {
    public:
        window_list(const size_t y, const size_t x)
            : window(y, x)
        {}

        virtual ~window_list(){}

        virtual void clear()
        {
            this->list_.clear();
            window::clear();
        }

        void push(const std::shared_ptr<WindowDerived> w)
        {
            this->add(w);
            this->list_.push_back(w);
            if(this->list_.size() == 1)
            {
                this->list_.front()->move_while_drawing(this->y(), this->x());
            }
            else
            {
                (*(this->list_.end() - 2))->place_to_right(*this->list_.back());
            }
        }

        void sort()
        {
            for(auto left_it = this->list_.begin(); left_it != this->list_.end(); ++left_it)
            {
                auto right_it = std::min_element(
                    left_it, this->list_.end(),
                    [](const std::shared_ptr<WindowDerived> a, const std::shared_ptr<WindowDerived> b)
                    {return *a < *b;}
                    );
                this->position_swap(*left_it, *right_it);
                std::swap(*left_it, *right_it);
            }
        }

        void replace(const size_t index, std::shared_ptr<WindowDerived> new_window)
        {
            this->add(new_window);
            auto old_window = this->at(index);
            this->position_swap(old_window, new_window);
            this->erase(old_window);
            this->list_.at(index) = new_window;
        }

        typename std::deque<std::shared_ptr<WindowDerived> >::iterator begin()
        {
            return this->list_.begin();
        }

        typename std::deque<std::shared_ptr<WindowDerived> >::iterator end()
        {
            return this->list_.end();
        }

        virtual size_t size()const
        {
            return this->list_.size();
        }

        std::shared_ptr<WindowDerived> at(const size_t index)const
        {
            return list_.at(index);
        }

        void position_swap(std::shared_ptr<WindowDerived> a, std::shared_ptr<WindowDerived> b)
        {
            size_t a__to_y = a->to_y();
            size_t a__to_x = a->to_x();
            a->move_while_drawing(b->to_y(), b->to_x());
            b->move_while_drawing(a__to_y  , a__to_x  );
        }

    private:
        std::deque<std::shared_ptr<WindowDerived> > list_;
    };
}
