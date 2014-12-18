#include "event_manager.hpp"
#include "nctk/form.hpp"

void event_manager::play()
{
    poker.init_deal();

    field.reset(poker.hand());

    auto selected = field.selected_array_IO();
    poker.exchange(selected);
    field.reset(poker.hand());

    field.draw();

    const std::string message_to_wait = "press any key to exit:";
    auto message_win = nctk::new_window(1, message_to_wait.size(), getmaxy(stdscr) - 1, 0);
    message_win.set_contents(message_to_wait).draw();

    nctk::form form(getmaxy(stdscr) - 1, message_win.right());
    form.get_char();
}
