#include "display.hpp"
#include "window.hpp"

namespace nctk
{
    display::display()
        : lines_(40)            // 標準ライブラリ制限があって端末の大きさが取得できないため,決め打ちをしておく
        , colus_(80)
        , buffer_(40, std::string(this->colus_, ' '))
    {}

    void display::flush()
    {
        for(const auto& l : this->buffer_)
        {            
            std::cout << l << std::endl;
        }
        std::fill_n(this->buffer_.begin(), this->lines_, std::string(this->colus_, ' '));
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
                    this->buffer_.at(cursor_y).at(cursor_x) = *content_it;
                }
                else
                {
                    ++content_it;
                    break;
                }
            }
        }
    }
}
