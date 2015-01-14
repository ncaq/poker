#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace nctk
{
    class window;
    
    class debug_streambuf : public std::streambuf
    {
    public:
        debug_streambuf();

    protected:
        virtual int overflow(const int c = EOF);
        virtual std::streamsize xsputn(const char* s, std::streamsize n);
        virtual int sync();

    private:
        void time_stamp_when_first();

        std::unique_ptr<window> curses_output_;
        std::ofstream file_output_;

        static bool started_;
    };

    class debug_stream : public std::ostream
    {
    public:
        debug_stream();

    private:
        debug_streambuf buffer_;
    };
}
