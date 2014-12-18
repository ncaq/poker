#include "game_field.hpp"
#include "nctk/form.hpp"

game_field::game_field()
    : deck_area_(0, 0)
    , description_(4, 40, 0, 13)
{
    description_.set_contents(
        R"(up: select card to change
right and left: move cursor
down or enter: done selecting)");
}

void game_field::draw()
{
    // clear();
    // refresh();
    deck_area_.draw();
    for(auto&& h : hand_area_)
    {
        h->draw();
    }
    description_.draw();
}

void game_field::reset(const std::deque<std::shared_ptr<card> >& cs)
{
    hand_area_.clear();

    for(const auto& c : cs)
    {
        this->push(c);
        this->draw();
    }
}

void game_field::push(const std::shared_ptr<card>& c)
{
    hand_area_.push_back(std::make_shared<card_view>(c, 0, 0));
    if(hand_area_.size() <= 1)
    {
        hand_area_.at(0)->move_while_drawing(11, 0);
    }
    else
    {
        (*(hand_area_.end() - 2))->move_to_right_while_drawing(*hand_area_.back());
    }
}

std::deque<bool> game_field::selected_array_IO()
{
    nctk::window_selecter_horizontally<card_view> cursors(hand_area_);
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

#include <unistd.h>

void test_selected_array_IO()
{
    game_field field;
    field.reset({std::make_shared<card>(suit_t::spade, 1)});

    std::string buffer;
    for(auto c : field.selected_array_IO())
    {
        buffer += std::to_string(c);
    }
    nctk::new_window(1, 20, 40, 0).set_contents(buffer).draw();
    usleep(1000000);
}
