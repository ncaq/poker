#pragma once

#include "display.hpp"
#include <cmath>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace nctk
{
    /*!
      window兼widget
      tuiだとtextしか載せられないので,これ1つで十分
    */

    std::vector<std::string> default_contents();

    class window
    {
    public:
        window();
        window(const size_t y, const size_t x, const std::function<std::vector<std::string>()> init = default_contents);
        virtual ~window();

        template<typename ShowAble>
        void set_contents(const ShowAble& input);

        virtual bool draw();

        template<typename WindowDerived>
        std::shared_ptr<WindowDerived> add(const std::shared_ptr<WindowDerived> w);

        virtual void erase(const std::shared_ptr<window> w);
        virtual void clear();

        void move_while_drawing(const size_t to_y, const size_t to_x);
        void place_to_right(window& take)const;
        void resize(const size_t h, const size_t w);

        void yx(const size_t y, const size_t x);
        void y(const size_t y);
        void x(const size_t x);

        std::vector<std::string> show_contents()const;
        size_t colu()const;
        size_t line()const;
        size_t y()const;
        size_t to_y()const;
        size_t x()const;
        size_t to_x()const;
        size_t under()const;
        size_t to_under()const;
        size_t right()const;
        size_t to_right()const;

        virtual window& operator=(const window& take);
        virtual bool operator<(const window& w)const; //!< インターフェイス用途なのでデフォルト実装に実用性はないです

        template<typename ShowAble>
        window& operator+=(const ShowAble& input);

    private:
        bool increase_moving();

        size_t y_ = 0;
        size_t x_ = 0;
        size_t to_y_ = 0;
        size_t to_x_ = 0;

        std::function<std::vector<std::string>()> contents_;
        std::set<std::shared_ptr<window> > children_;
    };

    template<typename ShowAble>
    struct show_contents_function
    {
        static std::function<std::vector<std::string>()> value(ShowAble s)
        {
            return [s](){return std::vector<std::string>({nctk::to_string(s)});};
        }
    };

    template<typename ShowAble>
    struct show_contents_function<std::shared_ptr<ShowAble> >
    {
        static std::function<std::vector<std::string>()> value(std::shared_ptr<ShowAble> s)
        {
            return [s](){return std::vector<std::string>({nctk::to_string(*s)});};
        }
    };

    template<>
    struct show_contents_function<std::function<std::vector<std::string>()> >
    {
        static std::function<std::vector<std::string>()> value(std::function<std::vector<std::string>()> s)
        {
            return s;
        }
    };

    template<>
    struct show_contents_function<std::function<std::string()> >
    {
        static std::function<std::vector<std::string>()> value(std::function<std::string()> s)
        {
            return [s](){return std::vector<std::string>({s()});};
        }
    };

    template<>
    struct show_contents_function<std::vector<std::string> >
    {
        static std::function<std::vector<std::string>()> value(std::vector<std::string> s)
        {
            return [s](){return s;};
        }
    };

    template<>
    struct show_contents_function<std::string>
    {
        static std::function<std::vector<std::string>()> value(std::string s)
        {
            return [s](){return std::vector<std::string>({s});};
        }
    };

    template<typename ShowAble>
    void window::set_contents(const ShowAble& input)
    {
        this->contents_ = show_contents_function<ShowAble>::value(input);
    }

    template<typename WindowDerived>
    std::shared_ptr<WindowDerived> window::add(const std::shared_ptr<WindowDerived> w)
    {
        return std::dynamic_pointer_cast<WindowDerived>(*this->children_.insert(w).first);
    }

    // template<typename ShowAble>
    // window& window::operator+=(const ShowAble& input)
    // {
    //     this->set_contents(this->show_contents() + show_contents_function<ShowAble>::value(input)());
    //     return *this;
    // }
    template<typename ShowAble>
    window& window::operator+=(const ShowAble&)
    {
        return *this;
    }
}
