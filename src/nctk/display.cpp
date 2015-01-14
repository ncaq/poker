#include "display.hpp"
#include "window.hpp"
#include <iostream>
#include <thread>

namespace nctk
{
    size_t display::line_(80);            //!< terminfoとか使えないので端末の大きさが取得できないため,決め打ちをしておく
    size_t display::colu_(80);
    std::vector<std::string> display::buffer_(display::line_, std::string(display::colu_, ' '));
    std::string display::form_description_;
    std::string display::user_input_;

    void display::init()
    {
        echo_mode(false);
    }

    void display::echo_mode(bool p)
    {
        if(p)
        {
            system("/bin/stty echo icanon");
        }
        else
        {
            system("/bin/stty -echo -icanon"); //!< get_char()が改行を待たないようになる
        }
    }

    void display::write(const window& w)
    {
        auto content_it = w.show_contents().begin();
        for(size_t cursor_y = w.y();
            cursor_y < w.under() && content_it != w.show_contents().end();
            ++cursor_y)
        {
            for(size_t cursor_x = w.x();
                cursor_x < w.right() && content_it != w.show_contents().end();
                ++cursor_x, ++content_it)
            {
                if(*content_it != '\n')
                {
                    buffer_.at(cursor_y).at(cursor_x) = *content_it;
                }
                else
                {
                    ++content_it;
                    break;
                }
            }
        }
    }

    void display::flush()
    {
        display::clear();

        for(const auto& l : buffer_)
        {
            std::cout << l << '\n';
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if(!form_description_.empty())
        {
            wait_input();
        }

        std::fill_n(buffer_.begin(), line_, std::string(colu_, ' '));
    }

    void display::clear()
    {
#ifdef unix
        std::system("clear");
#elif _WIN32
        std::system("cls");
#endif
    }

    char display::get_key()
    {
        return std::getchar();
    }

    void display::set_dialog(const std::string& description)
    {
        form_description_ = description;
    }

    std::string display::get_dialog()
    {
        std::string backup = user_input_;
        form_description_ = "";
        return user_input_;
    }

    void display::wait_input()
    {
        std::cout << form_description_;

        echo_mode(true);
        user_input_ = "";
        std::getline(std::cin, user_input_);
        echo_mode(false);
    }

    // std::string display::get_string(const window& w)
    // {
    //     echo_mode(true);

    //     std::string input;
    //     std::getline(std::cin, input);

    //     echo_mode(false);
    //     return input;
    // }

    // void set_cursor_to_under()
    // {
    //     std::cout.seekp
    // }
}
