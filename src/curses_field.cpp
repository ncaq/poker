#include "curses_field.hpp"

curses_field::curses_field()
    :deck_area_(undefined_card(), 0, 0)
{
}

void curses_field::draw()
{
    deck_area_.draw();
    for(const auto& h : hand_area_)
    {
        h.draw();
    }
}

void curses_field::deal(const std::vector<card>& cs)
{
    hand_area_.clear();

    for(const auto& c : cs)
    {
        this->push(c);
        this->draw();
    }
}

void curses_field::push(const card& c)
{
    hand_area_.push_back(nctk::box<card>(c, 0, 0));
    if(hand_area_.size() <= 1)
    {
        hand_area_.at(0).moving_draw(14, 0);
    }
    else
    {
        (hand_area_.end() - 2)->move_to_right(hand_area_.back());
    }
}

std::vector<bool> curses_field::selected_array_IO()
{
    nctk::box_cursors<card> cursors(hand_area_);
    int key;
    nctk::new_window form(1, 1, getmaxy(stdscr), 0);
    keypad(form, true);
    do
    {
        this->draw();
        cursors.draw();

        key = form.get_char();

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
    }while(key != '\n');
    return cursors.selected_array();
}

void test_selected_array_IO()
{
    curses_field field;
    field.deal({card(suit::spade, 1)});

    std::string buffer;
    for(auto c : field.selected_array_IO())
    {
        buffer += std::to_string(c);
    }
    nctk::new_window(1, 20, 40, 0).echo(buffer);
    usleep(1000000);
}
