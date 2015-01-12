#pragma once

#include <cmath>
#include <curses.h>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace nctk
{
    /*!
      window兼widget
      tuiだとtextしか載せられないので,これ1つで十分
    */

    class window
    {
    public:
        window();
        window(const size_t lines, const size_t cols, const size_t y, const size_t x, const std::function<std::string()> init = [](){return "";});
        virtual ~window();

        template<typename ShowAble>
        void set_contents(const ShowAble& input);
        void clear();

        virtual bool draw();

        void insert(const std::shared_ptr<window> child, const std::string name = "");
        std::shared_ptr<window> at(const std::string& name);
        void erase(const std::string& name);

        std::string get_string();
        char get_char();
        int get_int();

        template <typename Window>
        Window make_under(std::function<Window(const size_t, const size_t)> maker)const;
        template <typename Window>
        Window make_right(std::function<Window(const size_t, const size_t)> maker)const;

        void move_while_drawing(const size_t to_y, const size_t to_x);
        void place_to_right(window& take)const;
        void align_window(); //!< 改行に合わせてwindowのサイズを再設定する.utf-8だと大きすぎになることはあるが,小さすぎになることはない
        void resize(const size_t h, const size_t w);

        std::string show_contents()const;
        size_t under()const;
        size_t right()const;

        void yx(const size_t y, const size_t x);
        void y(const size_t y);
        void x(const size_t x);
        size_t y()const;
        size_t x()const;
        size_t height()const;
        size_t width()const;

        template<typename ShowAble>
        window& operator+=(const ShowAble& input);
        operator WINDOW*();
        operator const WINDOW*()const;

    private:
        bool increase_moving();

        std::shared_ptr<WINDOW> window_ptr_;
        size_t distination_y_, distination_x_;
        std::function<std::string()> contents_;

        std::map<std::string, std::shared_ptr<window> > children_;
    };

    template<typename ShowAble>
    struct show_contents_function
    {
        static std::function<std::string()> value(ShowAble s)
        {
            return [s](){return std::to_string(s);};
        }
    };

    template<typename ShowAble>
    struct show_contents_function<std::shared_ptr<ShowAble> >
    {
        static std::function<std::string()> value(std::shared_ptr<ShowAble> s)
        {
            return [s](){return std::to_string(*s);};
        }
    };

    template<>
    struct show_contents_function<std::function<std::string()> >
    {
        static std::function<std::string()> value(std::function<std::string()> s)
        {
            return s;
        }
    };

    template<>
    struct show_contents_function<std::string>
    {
        static std::function<std::string()> value(std::string s)
        {
            return [s](){return s;};
        }
    };

    template<typename ShowAble>
    void window::set_contents(const ShowAble& input)
    {
        this->contents_ = show_contents_function<ShowAble>::value(input);
    }

    template<typename Window>
    Window window::make_under(std::function<Window(const size_t, const size_t)> maker)const
    {
        return maker(this->under(), this->distination_x_);
    }

    template<typename Window>
    Window window::make_right(std::function<Window(const size_t, const size_t)> maker)const
    {
        return maker(this->distination_y_, this->right());
    }

    template<typename ShowAble>
    window& window::operator+=(const ShowAble& input)
    {
        this->set_contents(this->show_contents() + show_contents_function<ShowAble>::value(input)());
        return *this;
    }
}
