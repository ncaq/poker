#pragma once

#include "../model/poker_mediator.hpp"
#include <memory>

/*!
  eventを進めていくclass
  単純に関数転移する
*/

class main_window;

class event_manager
{
public:
    event_manager();

    void play();                //!< initみたいなもの

private:
    void new_deal();            //!< 手札配布,ゲームの最初
    void bet_ante();            //!< ante(強制徴収金)を賭ける
    void exchange();            //!< 手札交換,2回まで
    void raise();               //!< 賭け金追加選択
    void call();                //!< 相手の賭け金の方が高い場合に選択
    void payoff(const lead no_fold_actor); //!< 配当
    void player_win();                     //!< 表示を分けてるだけ
    void ai_win();
    void half();                //!< obsolete
    void end();                 //!< キー入力待って終了

    std::shared_ptr<main_window> tui_;
    std::shared_ptr<poker_mediator> poker_;

    size_t game_count_ = 0;
    size_t exchange_count_ = 0;
};
