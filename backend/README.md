# 3 年後期 ゼミ

## 目標

プログラムにより最適な旅行プランを立てることができるようになる。

### 条件・制約

-   利用者が入力
    -   訪問する観光スポット
    -   日付
    -   開始時刻
    -   終了時刻
    -   滞在時間
    -   到着したい時間帯 ⋯「昼食は 12 時から 13 時のあいだに食べたい」、「夜のライトアップが見たい」など
-   Google Maps API
    -   移動時間
        -   [Distance Matrix API](https://developers.google.com/maps/documentation/distance-matrix/overview?hl=ja)を用いる
        -   ~~バス・電車のダイヤによっては移動時間が出発時刻に依存する可能性がある点は注意~~
            -   日本において Google Maps API は公共交通機関を利用した距離行列に対応していない
    -   営業時間
        -   [Place Details API](https://developers.google.com/maps/documentation/places/web-service/details?hl=ja)を用いる

### 最適な旅行プランとは

尺度はさまざま

-   できるだけ多くのスポットを訪問する
-   行きたい度が高いスポットを優先してできるだけ多く訪問する
-   歩く距離を少なくしたい
-   API へのリクエスト回数を少なくしたい

## 実装

### 概要

-   [`./python/*.py`](./python/)：主に API との通信を行う
-   [`./src/*.cpp`](./src/)：主に最適化を行う
