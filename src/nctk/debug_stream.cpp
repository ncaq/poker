#include "debug_stream.hpp"

namespace nctk
{
    debug_streambuf::debug_streambuf()
        : std::streambuf()
        , file_output_("error.log", std::ios::app)
    {
        try
        {
            curses_output_.reset(new new_window<std::string>(0, 0, getmaxy(stdscr) - 10, getmaxx(stdscr) - 20));
            scrollok(*curses_output_, true);
        }catch(...){}
    }

    int debug_streambuf::overflow(const int c)
    {
        time_stamp_when_first();
        if(c != EOF)
        {
            try                 // endwinしてるような状況だと書き込めない.そこは諦める.
            {
                *curses_output_ += std::string(1, static_cast<char>(c)); // std::string(繰り返し回数, 文字)
            }catch(...){}
            file_output_ << static_cast<char>(c);
        }
        return c;
    }

    std::streamsize debug_streambuf::xsputn(const char* s, std::streamsize n)
    {
        time_stamp_when_first();
        const std::string message(s, n);
        try
        {
            *curses_output_ += message;
        }catch(...){}
        file_output_ << message;
        return n;
    }

    int debug_streambuf::sync()
    {
        try
        {            
            curses_output_->draw();
        }catch(...){}

        file_output_.flush();
        return 0;
    }

    void debug_streambuf::time_stamp_when_first()
    {
        if(!started_)
        {
            auto lvalue_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); // std::ctimeはC言語の関数なので右辺値参照が出来ないのでポインタ渡しを求められる
            std::ofstream("error.log", std::ios::app)
                << "----------\n"
                << std::ctime(&lvalue_time);

            started_ = true;
        }
    }

    bool debug_streambuf::started_ = false;

    debug_stream::debug_stream()
        : std::ostream(&buffer_)
    {}
}
