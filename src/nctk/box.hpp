#pragma once

#include "new_window.hpp"
#include "sub_window.hpp"
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
            :contents_(c), draw_area_(new sub_window(stdscr, contents_.height(), contents_.width(), y, x))
        {
        }

        void draw()const
        {
            draw_area_->add_string(contents_.to_string());
            wrefresh(*draw_area_);
        }

        void moving_draw(const size_t y, const size_t x)
        {
            while(y != draw_area_->y() && x != draw_area_->x())
            {
                wclear(*draw_area_);
                wrefresh(*draw_area_);
                const size_t sy = y - draw_area_->y();
                const size_t sx = x - draw_area_->x();
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
                    if(draw_area_->y() + 1)
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
                    if(draw_area_->x() + 1)
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

    private:
        const T contents_;

        std::unique_ptr<basic_window> draw_area_;
    };
}
