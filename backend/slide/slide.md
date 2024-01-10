---
marp: true
size: 16:9
style: |
    section {
        font-family: "BIZ UDPGothic", sans-serif;
        justify-content: start;
    }
    h1, h2, h3, h4, h5, h6 {
        color: #691f80;
        font-weight: bold;
    }
    section.lead {
        justify-content: center;
    }
    section.lead h1 {
        text-align: center;
    }
    td, th {
        padding: 0.5rem !important;
    }
math: mathjax
---

<!-- headingDivider: 2 -->

<!-- _class: lead -->

# 効率厨のための旅行計画アルゴリズム

<p class="text-right">経済学部3年 小川歩夢</p>

## 問題設定1

<div>

行きたいスポットを列挙し、その中で最も満足度が高い旅行計画を作りたい！！！

### スポット

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

- 制約
  - 到着時刻
  - 上限（任意）
  - 下限（任意）
  - 営業時間（任意）
  - 滞在時間

</div>
<div>

- スコア
  - 満足度 ： 1〜3の3段階
  - 満足度の合計が同じなら所要時間が短い方が良い

</div>
</div>
</div>

## 問題設定2

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

### スポット間

- 移動時間

</div>
<div>

### 旅行計画

- スポットの訪問順序
- 最後は出発地に戻ってくる

</div>
</div>

## 単純化してみたら

<div>

### スポット

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

- ~~制約~~
  - ~~(略)~~

</div>
<div>

- スコア
  - 満足度 ： ~~1〜3の3段階~~ **1とする**
  - **満足度の合計が同じなら所要時間が短い方が良い**

</div>
</div>

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

### スポット間

- **移動時間**

</div>
<div>

### 旅行計画

- **スポットの訪問順序**
- **最後は出発地に戻ってくる**

</div>
</div>
</div>

## 巡回セールスマン問題とは

> 都市の集合と各2都市間の移動コスト（たとえば距離）が与えられたとき、全ての都市をちょうど一度ずつ巡り出発地に戻る巡回路のうちで総移動コストが最小のものを求める（セールスマンが所定の複数の都市を1回だけ巡回する場合の最短経路を求める）組合せ最適化問題である。

<div class="text-lg flex justify-end">

- [巡回セールスマン問題 - Wikipedia](https://ja.wikipedia.org/wiki/%E5%B7%A1%E5%9B%9E%E3%82%BB%E3%83%BC%E3%83%AB%E3%82%B9%E3%83%9E%E3%83%B3%E5%95%8F%E9%A1%8C)

</div>

<br/>

さっきの単純化した問題は巡回セールスマン問題に帰着できる！

- 全スポットを最も短い時間で訪問する順序を求めるから

## 巡回セールスマン問題を解く

**bitDP**と（競プロ界隈で）呼ばれる手法で解くことができる。

- bit: 2進数のビットが立っているかどうかで集合を表現

    |集合|bitでの表現|
    |--|--|
    |$\{1, 3\}$|`0101` $\rightarrow$ `5`|
    |$\{2\}$|`0010` $\rightarrow$ `2`|
    |$\emptyset$|`0000` $\rightarrow$ `0`|

- DP: 動的計画法（部分問題に分割して解く）

## 巡回セールスマン問題を解く

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

頂点数を$n$とする。
訪問の仕方を全探索しようとすると、$n!$通りある。
bitDPを使うと、$O(2^n n^2)$で解くことができる。

</div>

<div>

<image src="./bitDP-graph.png" class="h-2/3"/>

- <span class="text-green-800">**緑**</span> : $\log_2{(x!)}$
- <span class="text-blue-800">**青**</span> : $\log_2{(2^x x^2)}$

</div>
</div>

## 巡回セールスマン問題を解く

次の更新式をすべての集合、すべての頂点について計算する。
$$
dp[S \cup \{v\}][v] = \min_{u \in S} \{ dp[S][u] + c_{u, v} \}
$$

- $S$ : 訪問済みのスポットの集合
- $v$ : 次に訪問するスポット($v \notin S$)
- $c_{u, v}$ : スポット$u$からスポット$v$への移動時間

</br>

$dp[S][v]$は訪問済みスポット$S$、最後に訪問したスポットが$v$であるときの最小の移動時間であることが保証される。

求めたい解は、$dp[V][0]$である。（$V$は頂点全体の集合で、スポット$0$に戻ってくるから）

<script src="https://cdn.tailwindcss.com/3.0.0"></script>
<script src="./tailwind.config.js"></script>
