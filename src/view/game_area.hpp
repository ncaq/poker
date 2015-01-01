#pragma once

#include "../nctk/new_window.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "card_view.hpp"
#include "player_area.hpp"
#include "undefined_card_view.hpp"
#include <deque>
#include <memory>

class game_area
{
public:
    game_area();

    void draw();
    void new_game(const std::deque<std::shared_ptr<card> >& new_player_hand, const std::deque<std::shared_ptr<card> >& new_ai_hand);
    void update_message(const std::string& contents);

    player_area& player_input();

private:
    undefined_card_view deck_area_; // ハリボテ
    player_area player_;
    actor_area ai_;
    nctk::new_window message_;  // その時々の説明を表示するウインドウ
};
