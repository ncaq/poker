#pragma once

#include "nctk/new_window.hpp"
#include <string>

class undefined_card_view : public nctk::new_window
{
public:
    undefined_card_view(const size_t y, const size_t x);

private:
    static const std::string immutable_contents_;
};
