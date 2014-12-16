#include "event_manager.hpp"

void event_manager::play()
{
    poker.init_deal();
    field.deal(poker.hand());

    field.draw();
    usleep(10000000);
    // auto selected = field.get_selected_index_IO();
    // poker.exchange(selected);
    
}
