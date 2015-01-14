#include "../nctk/window_selecter_horizontally.hpp"
#include "main_window.hpp"
#include "player_window.hpp"

player_window::player_window(actor& m, main_window& whole_window, const std::shared_ptr<nctk::window> chip_notation_window)
    : actor_window(m, whole_window, chip_notation_window, "player chip: ")
{};

std::deque<bool> player_window::select_changing_cards()
{
    this->insert("cursors", std::make_shared<nctk::window_selecter_horizontally<card_window> >(this->hand_));
    int key = 0;
    do
    {
        this->whole_.draw();

        key = nctk::display::get_key();

        if(key == 67)           // right
        {
            this->at<nctk::window_selecter_horizontally<card_window> >("cursors")->shift_to_right();
        }
        else if(key == 68)      // left
        {
            this->at<nctk::window_selecter_horizontally<card_window> >("cursors")->shift_to_left();
        }
        else if(key == 65)       // up
        {
            this->at<nctk::window_selecter_horizontally<card_window> >("cursors")->toggle();
        }
    }while(key != '\n' && key != 66);
    return this->at<nctk::window_selecter_horizontally<card_window> >("cursors")->selected_array();
}

size_t player_window::raise()
{
    int chip_size;
    try
    {
        nctk::display::set_dialog("please input raise chip size. [0 <= x <= 20]:");
        this->whole_.draw();
        chip_size = std::stoi(nctk::display::get_dialog());
    }catch(...)
    {
        this->clear();
        return this->raise();
    }
    if(0 <= chip_size && chip_size <= 20)
    {
        return chip_size;
    }
    else
    {
        this->clear();
        return this->raise();
    }
}

bool player_window::call(const size_t ai_pool)
{
    std::string answer;
    try
    {
        nctk::display::set_dialog("ai bet is " + std::to_string(ai_pool) + "." + "Do you call? [y/n]:");
        this->whole_.draw();
        answer = nctk::display::get_dialog();
    }catch(...)
    {
        this->clear();
        return this->call(ai_pool);
    }
    if(answer.at(0) == 'y')
    {
        return true;
    }
    if(answer.at(0) == 'n')
    {
        return false;
    }
    this->clear();
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
