#pragma once

#include <stdexcept>
#include <string>

/*!
  カードの色
*/
enum suit_t
{spade, heart, club, diamond};

/*!
  cardです.これ自体は概念上のものなのでグラフィック(テキストだけど)は含みません.
 */
class card
{
public:
    card(const suit_t s, const size_t r);

    bool operator<(const card& take)const; //!< 数値優先,数値が同じなら色で判断{spade, heart, club, diamond}
    bool operator==(const card& take)const;
    bool operator!=(const card& take)const;

    std::string readable()const; //!< human_readableな表示 
    size_t rotated_rank()const; //!< 1を14として計算する

    suit_t suit()const;
    size_t rank()const;

private:
    suit_t suit_;
    size_t rank_;
};
