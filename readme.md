# 遊び方

## Windows

poker.exeを**mintty(cygwinのターミナルエミュレータ)**で実行してください.
**cmd.exe(コマンドプロンプト)では動きません!**

## GNU/Linux

poker.elfを実行

# ゲームの流れ

#. 双方の初期チップが**100**配られる
#. 双方にカードが5枚配られる
#. 双方は配られた時点でチップを**15**ベットする
#. 双方は任意のカードを交換することが出来る
#. 双方は交換した後,チップを追加出来る(0 <= 追加チップ <= **20**)
#. (プレイヤーの賭け金 < AIの賭け金)なら,プレイヤーは降りるか受けるかを選択する
#. 降りる場合,プレイヤーはAIに自分が賭けた金額を払う
#. 受ける場合,プレイヤーはAIの賭け金と同額,足りない場合は所持金の残額全てを賭ける
#. (プレイヤーの賭け金 > AIの賭け金)なら,AIは勝手に判断する
#. 勝ったほうがチップを全て取得する
#. 3ゲームするか,どちらかのチップがなくなったら終了
#. 終了時にAIよりチップ数が多ければ,ゲームに勝利する

# ビルド

## 必要なもの

* >=gcc-4.8.3
* boost
* ncurses
* GNUツール(make, find, xargs, sed ..)

## 手順

make runで動きます
make staticでstaticビルド,staticビルドにはlibncursesw.aが必要

# クレジット

## boost

[Boost Software License](http://www.boost.org/users/license.html)

## ncurses

``` {include="ncurses_README"}
```
