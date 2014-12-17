#include "event_manager.hpp"

void event_manager::play()
{
    poker.init_deal();

    field.deal(poker.hand());

    {
        auto selected = field.selected_array_IO();
        poker.exchange(selected);
        field.deal(poker.hand());
    }

    {
        auto selected = field.selected_array_IO();
        poker.exchange(selected);
        field.deal(poker.hand());
    }

    field.draw();

    auto message_win = nctk::new_window(1, getmaxx(stdscr) - 1, getmaxy(stdscr) - 1, 0);
    message_win.echo("please push any key to exit");

    nctk::new_window form(0, 0, -1, -1);
    keypad(form, true);
    form.get_char();
}
