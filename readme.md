# readme

# 遊び方

## 起動方法

### Windows

**poker.batを実行してください.**

**cygwinが必要です.**

もしくは,poker.exeをmintty(cygwinのターミナルエミュレータ)で実行してください.

おそらくcmd.exe(コマンドプロンプト)では動きません.

cygwinのバージョンによっては動かない可能性があります.
その場合はお手数ですがビルドをお願いします.

### GNU/Linux

poker.elfを実行.

## 操作方法

* 左右キーでカーソル移動
* 上キーでカード選択
* 下キーで選択決定

# ゲームの流れ

* 双方の初期チップが **100** 配られる
* 双方にカードが5枚配られる
* 双方は配られた時点でチップを **15** ベットする
* 双方は任意のカードを交換することが出来る
* 双方は交換した後,チップを追加出来る(0 <= 追加チップ <= **20**)
* (プレイヤーの賭け金 < AIの賭け金)なら,プレイヤーは降りるか受けるかを選択する
* 降りる場合,プレイヤーはAIに自分が賭けた金額を払う
* 受ける場合,プレイヤーはAIの賭け金と同額,足りない場合は所持金の残額全てを賭ける
* (プレイヤーの賭け金 > AIの賭け金)なら,AIは勝手に判断する
* 勝ったほうがチップを全て取得する
* 3ゲームするか,どちらかのチップがなくなったら終了
* 終了時にAIよりチップ数が多ければ,ゲームに勝利する

# ビルド

## 必要なもの

* >=gcc-4.8.3
* boost
* ncurses
* GNUツール(cygwinで揃う)(make, find, xargs, sed ..)

## 手順

普通にmakeでコンパイルできます.

# license

copyright null 2015

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

## library

[AUTHORS.md](AUTHORS.md)
