#include "../nctk/form.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "ai_area.hpp"
#include "game_area.hpp"

ai_area::ai_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_area)
    : actor_window(whole_area, m, chip_area, "ai     chip: ")
{};

bool ai_area::default_hide_setting()const
{
    return true;
}

size_t ai_area::hand_y_top()const
{
    return 0;
}
