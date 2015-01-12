#include "../nctk/form.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "main_window.hpp"
#include "player_window.hpp"

player_window::player_window(main_window& whole_window, std::shared_ptr<actor> m, std::shared_ptr<nctk::window> chip_window)
    : actor_window(whole_window, m, chip_window, "player chip: ")
{};

std::deque<bool> player_window::select_changing_cards()
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

size_t player_window::raise()
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

bool player_window::call(const size_t ai_pool)
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

void player_window::set_hide_cards(bool)
{
    for(auto& h : this->hand_)
    {
        h->set_hide(false);
    }
}

bool player_window::default_hide_setting()const
{
    return false;
}

size_t player_window::hand_y_top()const
{
    return 18;
}
