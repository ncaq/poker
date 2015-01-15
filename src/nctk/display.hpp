#pragma once

#include "alter.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace nctk
{
    class window;

    /*!
      ncursesに変わるバックエンド
      static class.TUIでマルチディスプレイは考える必要ない.
    */

    class display final
    {
    public:
        static int echo_mode(bool p);
        static void write(const window& w);
        static void flush();
        static int clear();
        static char get_key();
        static void set_dialog(const std::string& description); //!< dialogは1つしか用意出来ないので上書きされます
        static std::string get_dialog();
        static void wait_input();

    private:
        static size_t line_;    //!< 描画可能領域.dialog分があるので実際に描画する領域はもう一つ上です
        static size_t colu_;
        static std::vector<std::string> buffer_;

        static std::string form_description_;
        static std::string user_input_;
    };
}
