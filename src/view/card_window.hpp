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

    void set_hide(bool hide);

    bool operator<(const card_window& take)const;
    bool operator==(const card_window& take)const;
    bool operator!=(const card_window& take)const;

private:
    const card& model_;
    bool hide_;
    std::string card_cache_;

    class image_cell
    {
    public:
        image_cell(const std::string& path);

        std::string split(const size_t index);

    private:
        std::vector<std::string> lines_;
    };
    static card_window::image_cell sprite_;
    static const std::string hide_card_cache_;
};
