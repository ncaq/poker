#pragma once

#include <memory>
#include <string>
#include <vector>

enum class suit
{spade, heart, diamond, club};

class card
{
public:
    card(const suit s, const size_t r);

    std::string to_string()const;

    size_t width()const
    {
        return width_;
    }

    size_t height()const
    {
        return height_;
    }

private:
    class image_cell
    {
    public:
        image_cell(const std::string& path);

        std::string split(const size_t l, const size_t c, const size_t y, const size_t x);

    private:
        std::vector<std::u32string> lines_;
    };
    static card::image_cell sprite_;
    
    suit suit_;
    size_t rank_;

    size_t height_, width_;
    std::string view_;
};
