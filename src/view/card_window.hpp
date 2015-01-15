#pragma once

#include "../model/card.hpp"
#include "../nctk/window.hpp"
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class card_window : public nctk::window
{
public:
    card_window(const card& m, const size_t y, const size_t x, const bool hide = false);
    virtual ~card_window();

    void set_hide(bool hide);

    bool operator<(const card_window& take)const;
    bool operator==(const card_window& take)const;
    bool operator!=(const card_window& take)const;

private:
    std::vector<std::string> split(const size_t index)const;

    const card& model_;
    bool hide_;

    std::vector<std::string> card_cache_;
    static const std::vector<std::string> card_texture_;
    static const std::vector<std::string> hide_card_cache_;
    static constexpr size_t card_line_ = 9;
};
