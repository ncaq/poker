#pragma once

#include "../nctk/new_window.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "card_view.hpp"
#include "undefined_card_view.hpp"
#include <deque>
#include <memory>

class player_area;
class actor_area;

class game_area
{
public:
    game_area();
    void new_game(const std::deque<std::shared_ptr<card> >& new_player_hand, const std::deque<std::shared_ptr<card> >& new_ai_hand);

    void draw();
    void update_message(const std::string& contents);

    std::shared_ptr<player_area> player_input();

private:
    undefined_card_view deck_area_; // ハリボテ
    std::shared_ptr<player_area> player_;
    std::shared_ptr<actor_area> ai_;
    nctk::new_window message_;  // その時々の説明を表示するウインドウ
};
