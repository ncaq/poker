#pragma once

#include "../model/poker_mediator.hpp"
#include "../nctk/window.hpp"
#include <deque>
#include <memory>

class ai_window;
class card_window;
class player_window;

class main_window : public nctk::window
{
public:
    main_window();
    void init_game(std::shared_ptr<poker_mediator> model);

    virtual bool draw();
    void update_message(const std::string& contents);

    void new_deal();
    void adjust_exchange();
    void report(const lead no_fold_actor);

    std::shared_ptr<card_window> deck_window()const;
    std::shared_ptr<player_window> player_();

private:
    std::shared_ptr<ai_window> ai_();
    std::shared_ptr<poker_mediator> model_;
};
