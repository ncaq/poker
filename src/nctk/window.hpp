#pragma once

#include "display.hpp"
#include <cmath>
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
        window(const size_t line, const size_t colu, const size_t y, const size_t x, const std::function<std::string()> init = nullptr);
        virtual ~window();

        template<typename ShowAble>
        void set_contents(const ShowAble& input);

        virtual bool draw();

        using child_iterator = typename std::map<std::string, std::shared_ptr<window> >::iterator;

        template<typename WindowChild = window>
        std::shared_ptr<WindowChild> at(const std::string& name)const;

        template<typename WindowChild>
        std::pair<child_iterator, bool> insert(const std::string& name, std::shared_ptr<WindowChild> w);

        virtual void erase(const std::string& name);
        virtual void clear();

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
        size_t to_under()const;
        size_t right()const;
        size_t to_right()const;

        void yx(const size_t y, const size_t x);
        void y(const size_t y);
        void x(const size_t x);
        size_t line()const;
        size_t colu()const;
        size_t y()const;
        size_t x()const;

        window& operator=(const window& take);
        template<typename ShowAble>
        window& operator+=(const ShowAble& input);

    private:
        bool increase_moving();

        size_t line_, colu_, y_, x_;
        size_t to_y_, to_x_;

        std::function<std::string()> contents_;
        std::map<std::string, std::shared_ptr<window> > children_;
    };

    void swap_and_move(window& a, window& b, std::function<bool()> draw_callback);

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

    template<typename WindowChild>
    std::shared_ptr<WindowChild> window::at(const std::string& name)const
    {
        return std::dynamic_pointer_cast<WindowChild>(this->children_.at(name));
    }

    template<typename WindowChild>
    std::pair<window::child_iterator, bool> window::insert(const std::string& name, std::shared_ptr<WindowChild> w)
    {
        return this->children_.insert(std::make_pair(name, w));
    }

    template<typename Window>
    Window window::make_under(std::function<Window(const size_t, const size_t)> maker)const
    {
        return maker(this->to_under(), this->to_x_);
    }

    template<typename Window>
    Window window::make_right(std::function<Window(const size_t, const size_t)> maker)const
    {
        return maker(this->to_y_, this->to_right());
    }

    template<typename ShowAble>
    window& window::operator+=(const ShowAble& input)
    {
        this->set_contents(this->show_contents() + show_contents_function<ShowAble>::value(input)());
        return *this;
    }
}
