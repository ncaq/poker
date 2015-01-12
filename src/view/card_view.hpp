#pragma once

#include "../model/card.hpp"
#include "../nctk/window.hpp"
#include <functional>
#include <string>
#include <vector>

class card_view : public nctk::window
{
public:
    card_view(const std::shared_ptr<card> base, const size_t y, const size_t x, const bool hide = false);

    void set_hide(bool hide);

    bool operator<(const card_view& take)const;
    bool operator==(const card_view& take)const;
    bool operator!=(const card_view& take)const;

private:
    std::shared_ptr<card> model_;
    std::string card_contents_cache_;
    bool hide_;

    class image_cell
    {
    public:
        image_cell(const std::string& path);

        std::string split(const size_t l, const size_t c, const size_t y, const size_t x);

    private:
        std::vector<std::u32string> lines_;
    };
    static card_view::image_cell sprite_;
    static const std::string hide_card_view_;
};

void swap(card_view& a, card_view& b, std::function<bool()> draw_callback);
