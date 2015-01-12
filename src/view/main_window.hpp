#pragma once

#include "../model/poker_mediator.hpp"
#include "../nctk/window.hpp"
#include "card_window.hpp"
#include <deque>
#include <memory>

class ai_window;
class player_window;

class main_window
{
public:
    main_window();
    void init_game(std::shared_ptr<poker_mediator> model);

    bool draw();
    void update_message(const std::string& contents);
    void new_deal();
    void adjust_exchange();
    void report(const lead no_fold_actor);

    std::shared_ptr<player_window> player_input();
    std::shared_ptr<card_window> deck_window()const;

private:
    std::shared_ptr<card_window> deck_window_; //!< ハリボテ
    std::shared_ptr<player_window> player_;
    std::shared_ptr<ai_window> ai_;
    nctk::window pool_chip_;
    nctk::window message_;     //!< その時々の説明を表示するウインドウ

    std::shared_ptr<poker_mediator> model_;
};
