#pragma once

#include "card.hpp"
#include "nctk/new_window.hpp"
#include <string>
#include <vector>

class card_view : public nctk::new_window
{
public:
    card_view(const std::shared_ptr<const card> base, const size_t y, const size_t x);

    bool operator<(const card_view& take)const;
    bool operator==(const card_view& take)const;

private:
    std::shared_ptr<const card> model_;

    class image_cell
    {
    public:
        image_cell(const std::string& path);

        std::string split(const size_t l, const size_t c, const size_t y, const size_t x);

    private:
        std::vector<std::u32string> lines_;
    };
    static card_view::image_cell sprite_;
};
