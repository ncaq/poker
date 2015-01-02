#include "../nctk/form.hpp"
#include "../nctk/window_selecter_horizontally.hpp"
#include "game_area.hpp"
#include "player_area.hpp"

player_area::player_area(game_area& whole_area_)
    : actor_area::actor_area(whole_area_)
{};

std::deque<bool> player_area::select_changing_cards()
{
    nctk::window_selecter_horizontally<card_view> cursors(this->hand());
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
    return std::stoi(nctk::form("please input raise chip size. [0 <= x <= 20]:").get_string());
}

bool player_area::call()
{
    return (nctk::form("Do you call? [y/n]:").get_string().at(0) == 'y');
}

size_t player_area::hand_y_top()const
{
    return 18;
}
