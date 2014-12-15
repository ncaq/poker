#include "event_manager.hpp"

event_manager::event_manager()
{
    poker.init_deal();
    for(auto card : poker.hand())
    {        
        field.deal(card);
    }
}
