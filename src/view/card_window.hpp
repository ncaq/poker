#pragma once

#include "../model/card.hpp"
#include "../nctk/window.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

/*
  cardの見た目を制御
*/
class card_window : public nctk::window
{
public:
    card_window(const card& m, const size_t y, const size_t x, const bool hide = false);
    virtual ~card_window();

    void set_hide(bool hide);   //!< 数字を見えなくする

    virtual bool operator<(const card_window& take)const;
    virtual bool operator==(const card_window& take)const;
    virtual bool operator!=(const card_window& take)const;

private:
    std::vector<std::string> split(const size_t index)const;

    const card& model_;
    bool hide_;

    std::vector<std::string> card_cache_;
    static const std::vector<std::string> card_texture_;
    static const std::vector<std::string> hide_card_cache_;
    static constexpr size_t card_line_ = 9;
};
