#pragma once

#include "card.hpp"
#include "nctk/box.hpp"
#include "nctk/box_cursors.hpp"
#include "undefined_card.hpp"
#include <vector>

class game_field
{
public:
    game_field();

    void draw();

    void deal(const std::vector<card>& cs); // todo: 引数をstd::vector<box<card>>&に変更
    std::vector<bool> selected_array_IO();

private:
    void push(const card& c);
    void swap(const card& c, const size_t index); // todo:
    
    nctk::box<undefined_card> deck_area_; // ハリボテ
    std::vector<nctk::box<card>> hand_area_; // 手札
};

void test_selected_array_IO();
