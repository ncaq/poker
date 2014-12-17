#pragma once

#include "new_window.hpp"

namespace nctk
{
    class form : public new_window
    {
    public:
        form(const size_t y, const size_t x);

        virtual ~form();
    };
}
