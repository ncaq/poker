#pragma once

#include "new_window.hpp"
#include <string>

namespace nctk
{
    class form : public new_window
    {
    public:
        form(const std::string& prompt_message);

        virtual ~form();
    };
}
