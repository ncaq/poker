#pragma once

#include "card_view.hpp"
#include <deque>
#include <memory>

class game_area;

class actor_area
{
public:
    actor_area(game_area& whole_area);
    virtual ~actor_area();

    bool draw();
    void push(std::shared_ptr<card_view> card);
    void swap(const std::shared_ptr<card>& c, const size_t index); // todo:
    void clear();

    virtual size_t hand_y_top()const;

    std::deque<std::shared_ptr<card_view> > hand()const;

protected:
    game_area& whole()const;

private:
    std::deque<std::shared_ptr<card_view> > hand_;

    game_area& whole_area_;
};
