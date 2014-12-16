#pragma once

#include <string>

class undefined_card
{
public:
    undefined_card();

    std::string to_string()const;

    size_t height()const
    {
        return height_;

    }
    size_t width()const
    {
        return width_;
    }

private:
    size_t height_, width_;

    std::string view_;
};
