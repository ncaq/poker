#pragma once

#include "../nctk/new_window.hpp"
#include "card_view.hpp"
#include <deque>
#include <memory>

class actor_area;
class ai;
class player;
class player_area;

class game_area
{
public:
    game_area();
    void init_game(std::shared_ptr<const player> player_model, std::shared_ptr<const ai> ai_model);

    bool draw();
    void update_message(const std::string& contents);
    void new_deal();
    void exchange();

    std::shared_ptr<player_area> player_input();

private:
    card_view deck_area_; // ハリボテ
    std::shared_ptr<player_area> player_;
    std::shared_ptr<actor_area> ai_;
    nctk::new_window<std::string> message_;  // その時々の説明を表示するウインドウ
};
