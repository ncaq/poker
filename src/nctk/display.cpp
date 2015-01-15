#include "display.hpp"
#include "window.hpp"
#include <iostream>
#include <thread>

namespace nctk
{
    size_t display::line_(50);            //!< terminfoとか使えないので端末の大きさが取得できないため,決め打ちになる
    size_t display::colu_(80);
    std::vector<std::string> display::buffer_(display::line_, std::string(display::colu_, ' '));
    std::string display::form_description_;
    std::string display::user_input_;

    int display::echo_mode(bool p)
    {
        if(p)
        {
            return std::system("/bin/stty echo icanon"); //! std::systemはcstdlibに定義されているらしい
        }
        else
        {
            return std::system("/bin/stty -echo -icanon");
        }
    }

    void display::write(const window& w)
    {
        const auto& split_text = w.show_contents();
        size_t y = w.y();
        for(const auto& t : split_text)
        {
            buffer_.at(y).replace(w.x(), w.colu(), t);
            ++y;
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

        if(!form_description_.empty())
        {
            wait_input();
        }

        std::fill_n(buffer_.begin(), line_, std::string(colu_, ' '));
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    int display::clear()
    {
        return std::system("clear");
    }

    char display::get_key()
    {
        echo_mode(false);
        char c = std::getchar();
        echo_mode(true);
        return c;
    }

    void display::set_dialog(const std::string& description)
    {
        form_description_ = description;
    }

    std::string display::get_dialog()
    {
        std::string backup = user_input_;
        return user_input_;
    }

    void display::wait_input()
    {
        std::cout << form_description_;

        form_description_ = "";
        user_input_ = "";
        std::getline(std::cin, user_input_);
    }
}
