#include "game_field.hpp"
#include "nctk/form.hpp"

game_field::game_field()
    : deck_area_(undefined_card(), 0, 0)
    , description_(4, 40, 0, 13)
{
}

void game_field::draw()
{
    clear();
    refresh();
    deck_area_.draw();
    for(const auto& h : hand_area_)
    {
        h.draw();
    }

    description_.echo(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)");
}

void game_field::deal(const std::vector<card>& cs)
{
    hand_area_.clear();

    for(const auto& c : cs)
    {
        this->push(c);
        this->draw();
    }
}

void game_field::push(const card& c)
{
    hand_area_.push_back(nctk::box<card>(c, 0, 0));
    if(hand_area_.size() <= 1)
    {
        hand_area_.at(0).moving_draw(11, 0);
    }
    else
    {
        (hand_area_.end() - 2)->move_to_right(hand_area_.back());
    }
}

std::vector<bool> game_field::selected_array_IO()
{
    nctk::box_cursors<card> cursors(hand_area_);
    int key;
    nctk::form input(0, getmaxx(stdscr) - 1);
    do
    {
        this->draw();
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

void test_selected_array_IO()
{
    game_field field;
    field.deal({card(suit::spade, 1)});

    std::string buffer;
    for(auto c : field.selected_array_IO())
    {
        buffer += std::to_string(c);
    }
    nctk::new_window(1, 20, 40, 0).echo(buffer);
    usleep(1000000);
}
