#include "../nctk/form.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "ai_window.hpp"
#include "main_window.hpp"

ai_window::ai_window(main_window& whole_window, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_window)
    : actor_window(whole_window, m, chip_window, "ai     chip: ")
{};

bool ai_window::default_hide_setting()const
{
    return true;
}

size_t ai_window::hand_y_top()const
{
    return 0;
}
