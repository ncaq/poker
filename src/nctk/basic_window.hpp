#pragma once

#include <curses.h>
#include <functional>
#include <string>

namespace nctk
{
    class basic_window
    {
    public:
        basic_window(WINDOW* win);
        virtual ~basic_window() = 0;

        operator WINDOW*();
        operator const WINDOW*()const;

        basic_window& set_contents(const std::string& input);
        bool draw();
        void clear();
        void move_while_drawing(const size_t to_y, const size_t to_x);
        void place_other_window_to_right_while_drawing(basic_window& take)const;

        char get_char();

        std::shared_ptr<basic_window> make_under(std::function<std::shared_ptr<basic_window>(const size_t, const size_t)> maker);

        void yx(const size_t y, const size_t x);
        void y(const size_t y);
        void x(const size_t x);
        size_t y()const;
        size_t x()const;
        size_t height()const;
        size_t width()const;
        size_t under()const;
        size_t right()const;

    private:
        WINDOW* window_ptr_;

        bool increase_moving();
        size_t distination_y_, distination_x_;

        std::string contents_;
    };
}
