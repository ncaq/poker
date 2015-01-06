#pragma once

#include "../nctk/new_window.hpp"
#include "card_view.hpp"
#include <deque>
#include <memory>

class ai;
class ai_area;
class player;
class player_area;

class game_area
{
public:
    game_area();
    void init_game(std::shared_ptr<player> player_model, std::shared_ptr<ai> ai_model);

    bool draw();
    void update_message(const std::string& contents);
    void new_deal();
    void adjust_exchange();

    std::shared_ptr<player_area> player_input();
    std::shared_ptr<card_view> deck_area()const;

private:
    std::shared_ptr<card_view> deck_area_; // ハリボテ
    std::shared_ptr<player_area> player_;
    std::shared_ptr<ai_area> ai_;
    nctk::new_window<std::string> pool_chip_;
    nctk::new_window<std::string> message_;  // その時々の説明を表示するウインドウ
};
