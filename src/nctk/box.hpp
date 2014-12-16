#pragma once

#include "new_window.hpp"
#include <cmath>
#include <curses.h>
#include <memory>
#include <unistd.h>

namespace nctk
{
    template <typename T>
    class box
    {
    public:
        box(const T& c, const size_t y, const size_t x)
            :contents_(c), draw_area_(new new_window(contents_.height(), contents_.width(), y, x))
        {
        }

        void draw()const
        {
            draw_area_->add_string(contents_.to_string());
            wrefresh(*draw_area_);
        }

        void moving_draw(const size_t y, const size_t x)
        {
            while(y != draw_area_->y() || x != draw_area_->x())
            {
                wclear(*draw_area_);
                wrefresh(*draw_area_);
                const int sy = y - draw_area_->y();
                const int sx = x - draw_area_->x();
                if(std::signbit(sy))
                {
                    if(y < draw_area_->y() - 1)
                    {
                        draw_area_->y(draw_area_->y() - 1);
                    }
                    else
                    {
                        draw_area_->y(y);
                    }
                }
                else
                {
                    if(draw_area_->y() + 1 < y)
                    {
                        draw_area_->y(draw_area_->y() + 1);
                    }
                    else
                    {
                        draw_area_->y(y);
                    }
                }
                if(std::signbit(sx))
                {
                    if(x < draw_area_->x() - 1)
                    {
                        draw_area_->x(draw_area_->x() - 1);
                    }
                    else
                    {
                        draw_area_->x(x);
                    }
                }
                else
                {
                    if(draw_area_->x() + 1 < x)
                    {
                        draw_area_->x(draw_area_->x() + 1);
                    }
                    else
                    {
                        draw_area_->x(x);
                    }
                }
                this->draw();
                usleep(100000);
            }
            this->draw();
            usleep(100000);
        }

        template <typename Another>
        box<Another> make_under(const Another& c)const
        {
            return box<Another>(c, draw_area_->under(), draw_area_->x());
        }

        template <typename Another>
        void move_to_right(box<Another>& take)const
        {
            take.moving_draw(draw_area_->y(), draw_area_->x());
        }

    private:
        const T contents_;

        std::unique_ptr<basic_window> draw_area_;
    };
}
