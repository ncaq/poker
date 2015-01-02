#pragma once

#include "new_window.hpp"
#include <curses.h>
#include <fstream>
#include <iostream>
#include <string>

namespace nctk
{
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

        new_window<std::string> curses_output_;
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
