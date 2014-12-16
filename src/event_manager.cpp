#include "event_manager.hpp"

void event_manager::play()
{
    poker.init_deal();
    field.deal(poker.hand());
    
}
