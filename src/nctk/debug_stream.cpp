#include "debug_stream.hpp"

namespace nctk
{
    debug_streambuf::debug_streambuf()
        : curses_output_(new_window(0, 0, getmaxy(stdscr) - 10, getmaxx(stdscr) - 20))
        , file_output_("error.log", std::ios::app)
    {
        scrollok(curses_output_, true);
    }

    int debug_streambuf::overflow(const int c)
    {
        time_stamp_when_first();
        if(c != EOF)
        {
            curses_output_.add_contents(std::string(1, static_cast<char>(c))); // std::string(繰り返し回数, 文字)
            file_output_ << static_cast<char>(c);
        }
        return c;
    }

    std::streamsize debug_streambuf::xsputn(const char* s, std::streamsize n)
    {
        time_stamp_when_first();
        const std::string message(s, n);
        curses_output_.add_contents(message);
        file_output_ << message;
        return n;
    }

    int debug_streambuf::sync()
    {
        curses_output_.draw();
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
