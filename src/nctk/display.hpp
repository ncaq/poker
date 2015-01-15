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
      ncursesに変わるバックエンド.
      ダブルバッファリンクしている.
      TUIでマルチディスプレイは考える必要ないためstatic class.
    */

    class display final
    {
    public:
        static int echo_mode(bool p);       //!< false: "stty -echo" get_char()が改行を待たなくなる
        static void write(const window& w); //!< バッファに書き込み
        static void flush();                //!< clearして描画
        static int clear();                 //!< clear
        static char get_key();              //!< ncursesのgetch()を再現 sttyでechoしなくする
        static void set_dialog(const std::string& description); //!< dialogは1つしか用意出来ないので上書きされます
        static std::string get_dialog();                        //!< dialogのテキストを取得
        static void wait_input();                               //!< flushする時にstd::getlineします

    private:
        static size_t line_;    //!< 描画可能領域.dialog分があるので実際に描画する領域はもう一つ上です
        static size_t colu_;
        static std::vector<std::string> buffer_;

        static std::string form_description_;
        static std::string user_input_;
    };
}
