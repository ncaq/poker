#include "../nctk/form.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "game_area.hpp"
#include "player_area.hpp"

player_area::player_area(game_area& whole_area, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_area)
    : actor_window(whole_area, m, chip_area, "player chip: ")
{};

std::deque<bool> player_area::select_changing_cards()
{
    nctk::window_selecter_horizontally<card_window> cursors(this->hand_);
    int key = 0;
    nctk::form input("");
    do
    {
        this->whole().draw();
        cursors.draw();

        key = input.get_char();

        if(key == 5)             // right
        {
            cursors.shift_to_right();
        }
        else if(key == 4)       // left
        {
            cursors.shift_to_left();
        }
        else if(key == 3)        // up
        {
            cursors.toggle();
        }
    }while(key != '\n' && key != 2);
    return cursors.selected_array();
}

size_t player_area::raise()
{
    auto prompt = nctk::form("please input raise chip size. [0 <= x <= 20]:");
    prompt.draw();
    int chip_size;
    try
    {
        chip_size = prompt.get_int();
    }catch(...)
    {
        prompt.clear();
        return this->raise();
    }
    if(0 <= chip_size && chip_size <= 20)
    {
        return chip_size;
    }
    else
    {
        prompt.clear();
        return this->raise();
    }
}

bool player_area::call(const size_t ai_pool)
{
    auto prompt = nctk::form("ai bet is " + std::to_string(ai_pool) + "." + "Do you call? [y/n]:");
    prompt.draw();
    char answer;
    try
    {
        answer = prompt.get_char();
    }catch(...)
    {
        prompt.clear();
        return this->call(ai_pool);
    }
    if(answer == 'y')
    {
        return true;
    }
    if(answer == 'n')
    {
        return false;
    }
    prompt.clear();
    return this->call(ai_pool);
}

void player_area::set_hide_cards(bool)
{
    for(auto& h : this->hand_)
    {
        h->set_hide(false);
    }
}

bool player_area::default_hide_setting()const
{
    return false;
}

size_t player_area::hand_y_top()const
{
    return 18;
}
