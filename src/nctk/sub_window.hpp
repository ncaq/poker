#include "basic_window.hpp"

namespace nctk
{
    class sub_window : public basic_window
    {
    public:
        sub_window(WINDOW* origin, const size_t lines, const size_t cols, const size_t y, const size_t x);

        virtual ~sub_window();

    private:
        WINDOW* parent_window_ptr;
    };
}
