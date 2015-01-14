#include "../nctk/window_selecter_h.hpp"
#include "ai_window.hpp"
#include "main_window.hpp"

ai_window::ai_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window)
    : actor_window(m, whole_window, chip_notation_window, "ai     chip: ")
{};

bool ai_window::default_hide_setting()const
{
    return true;
}

size_t ai_window::hand_y_top()const
{
    return 0;
}
