#pragma once

#include "../model/poker_mediator.hpp"
#include "../nctk/window.hpp"
#include "card_window.hpp"
#include <deque>
#include <memory>

class ai_area;
class player_area;

class game_area
{
public:
    game_area();
    void init_game(std::shared_ptr<poker_mediator> model);

    bool draw();
    void update_message(const std::string& contents);
    void new_deal();
    void adjust_exchange();
    void report(const lead no_fold_actor);

    std::shared_ptr<player_area> player_input();
    std::shared_ptr<card_window> deck_area()const;

private:
    std::shared_ptr<card_window> deck_area_; //!< ハリボテ
    std::shared_ptr<player_area> player_;
    std::shared_ptr<ai_area> ai_;
    nctk::window pool_chip_;
    nctk::window message_;     //!< その時々の説明を表示するウインドウ

    std::shared_ptr<poker_mediator> model_;
};
