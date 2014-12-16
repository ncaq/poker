#include "curses_field.hpp"

curses_field::curses_field()
    :deck_area_(undefined_card(), 0, 0), cursors_()
{
}

void curses_field::draw()
{
    deck_area_.draw();
    for(const auto& h : hand_area_)
    {
        h.draw();
    }
    cursors_.draw();
}

void curses_field::deal(const std::vector<card>& cs)
{
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

std::vector<size_t> curses_field::get_selected_index_IO ()
{
    int key;
    do
    {
        key = getch();
        if(key == KEY_RIGHT)
        {
            cursors_.shift_to_right();
        }
        else if(key == KEY_LEFT)
        {
            cursors_.shift_to_left();
        }
        this->draw();
    }while(key == KEY_ENTER);
    return cursors_.selected();
}
