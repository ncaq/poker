#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace nctk
{
    class window;

    /*!
      ncursesに変わるバックエンド
    */

    class display
    {
    public:
        display();

        void flush();
        void write(const window& w);

    private:
        size_t lines_;
        size_t colus_;
        std::vector<std::string> buffer_;
    };
}
