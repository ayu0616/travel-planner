---
marp: true
size: 16:9
lang: ja
style: |
    section {
        font-family: "BIZ UDPGothic", sans-serif;
        justify-content: start;
        color: #333;
    }
    div.mermaid { all: unset; }
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
    section.narrow {
       padding: 0;
    }
    code {
      font-family: monaco, monospace;
    }
math: mathjax
---

<!-- $width: 1920 -->
<!-- $height: 1080 -->

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

制約とかややこしいので全部取っ払ってみた

<div>

### スポット

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

- ~~制約~~
  - ~~(略)~~

</div>
<div>

- スコア
  - **全部訪問して、所要時間が短いほど良い**

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

全地点を最短時間（距離）で訪問する経路を求める問題

> 都市の集合と各2都市間の移動コスト（たとえば距離）が与えられたとき、全ての都市をちょうど一度ずつ巡り出発地に戻る巡回路のうちで総移動コストが最小のものを求める（セールスマンが所定の複数の都市を1回だけ巡回する場合の最短経路を求める）組合せ最適化問題である。

<div class="text-lg flex justify-end">

- [巡回セールスマン問題 - Wikipedia](https://ja.wikipedia.org/wiki/%E5%B7%A1%E5%9B%9E%E3%82%BB%E3%83%BC%E3%83%AB%E3%82%B9%E3%83%9E%E3%83%B3%E5%95%8F%E9%A1%8C)

</div>

<br/>

さっきの単純化した問題は**巡回セールスマン問題に帰着できる！**

- 全スポットを最も短い時間で訪問する順序を求めるから

## 巡回セールスマン問題を解く

**bitDP**と（競プロ界隈で）呼ばれる手法で解くことができる。

- bit: 2進数のビットが立っているかどうかで集合を表現

    |集合|bitでの表現|
    |--|--|
    |$\{0, 2\}$|`0101` $\rightarrow$ `5`|
    |$\{1\}$|`0010` $\rightarrow$ `2`|
    |$\emptyset$|`0000` $\rightarrow$ `0`|

- DP: 動的計画法（部分問題に分割して解く）

## 巡回セールスマン問題を解く

<div class="text-2xl">

（べつにわからなくても大丈夫です）

次の更新式をすべての集合、すべての頂点について計算する。
$$
dp[S \cup \{v\}][v] = \min_{u \in S} \{ dp[S][u] + c_{u, v} \}
$$

- $S$ : 訪問済みのスポットの集合
- $v$ : 次に訪問するスポット($v \notin S$)
- $c_{u, v}$ : スポット$u$からスポット$v$への移動時間

</br>

$dp[S][v]$は訪問済みスポット$S$、最後に訪問したスポットが$v$であるときの**最小の移動時間であることが保証される。**

求めたい解は、$dp[V][0]$である。（$V$は頂点全体の集合で、スポット$0$に戻ってくるから）

経路は前に訪れた頂点を格納する配列を作り、$prev[V][0] = v$ならつぎは、$prev[V \backslash \{v\}][v]$と辿っていくことにより復元できる

</div>

## 巡回セールスマン問題を解く

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

頂点数を$n$とする。
訪問の仕方を全探索しようとすると、$n!$通りある。
bitDPを使うと、$O(2^n n^2)$で解くことができる。

とは言っても、家庭用のPCでは$n=20$を越えたあたりで**天文学的な時間**がかかるようになる

</div>

<div>

<image src="./bitDP-graph.webp" class="h-2/3"/>

- <span class="text-green-800">**緑**</span> : $\log_2{(x!)}$
- <span class="text-blue-800">**青**</span> : $\log_2{(2^x x^2)}$

</div>
</div>

## 制約やスコアを考慮する

スポット数が増えたり、制約やスコアを考慮すると、bitDPで解くのが難しくなる

### スポット（再掲）

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

## 以降の問題設定

本来やりたかったこと

- 制約を満たすように解を構成
- すべてのスポットを訪問する必要はない
  - 行きたいスポットが多いが、時間が少ない場合もある

## 枝刈りしながら全探索

スポットを足していって、制約違反なら探索打ち切り

<div class="grid grid-flow-col justify-stretch gap-4">
<div>

### アルゴリズム

- 未訪問のスポットを後ろに付け足す
- 制約を満たすか判定する
  - 満たさない場合は枝刈りする
- 出発地に戻ったら、スコアを計算する
  - スコアが最大なら解を更新する

</div>
<div>

### 考察

- 制約が多い場合はかなり有効な方法
- とはいっても全探索なので、スポット数が大きくなると厳しい

</div>
</div>

## 枝刈りしながら全探索

制約が厳しければ、探索する回数を大幅に削減できる

<image src="./edagari.svg" class="h-5/6"/>

## ヒューリスティックとは

**最適ではない**が、**高速にそれなりの解を得る**方法

> ヒューリスティック（英: heuristic、独: Heuristik）または発見的（手法）とは、必ずしも正しい答えを導けるとは限らないが、ある程度のレベルで正解に近い解を得ることができる方法である。発見的手法では、答えの精度が保証されない代わりに、解答に至るまでの時間が短いという特徴がある。

<div class="text-lg flex justify-end">

- [ヒューリスティック - Wikipedia](https://ja.wikipedia.org/wiki/%E3%83%92%E3%83%A5%E3%83%BC%E3%83%AA%E3%82%B9%E3%83%86%E3%82%A3%E3%83%83%E3%82%AF)

</div>

### メタヒューリスティクスの例

<div class="grid grid-flow-col justify-stretch gap-4">

<div>

- **山登り法**
- **焼きなまし法**

</div>
<div>

- 遺伝的アルゴリズム
- ビームサーチ

</div>

</div>

## 今回使ったヒューリスティック

<image src="./heuristic.webp" />

<div class="text-lg flex justify-end mt-2">

- 画像お借りしました ： <https://qiita.com/square1001/items/84604f79f55ff10d99b0>

</div>

## 焼きなまし法について

確率的にスコアが悪くなる解に移るが、その確率は時間とともに下がっていく

<div class="grid grid-flow-col justify-stretch gap-4">
<div>

### アルゴリズム

- 初期解を形成
- 現在の解から近傍解を生成
- 近傍解のスコアが良いなら、近傍解に移動
- 近傍解のスコアが悪いなら、確率的に近傍解に移動

</div>
<div>

### ポイント

- スコアが悪いときの遷移確率は、温度によって変化する
- 温度は時間経過とともに下がっていく

</div>
</div>

## 焼きなまし法の実装

### 初期解の生成

- 到着時刻などの制約を満たす範囲でランダムに生成
- 例: $\{0, 1, 3, 0\}$

## 焼きなまし法の実装

### 遷移

制約違反をするような遷移は行わない。

温度$T$および、遷移確率$p$は次の式で定義する

$$
\begin{align*}
T &= T_s + (T_e - T_s) \frac{t}{t_e} \\
p &= \exp{\left(\frac{s' - s}{T}\right)}
\end{align*}
$$

- $T_s$ : 初期温度、 $T_e$ : 終了温度、 $t$ : 現在の時間、 $t_e$ : 終了時間（3秒）
- $s$ : 現在のスコア、 $s'$ : 遷移先のスコア
  - $s' - s > 0$のとき、$p > 1$となるので、必ず遷移する

## 焼きなまし法の実装

### 近傍解の生成（挿入）

- ランダムな位置にランダムなスポットを挿入
  - 例: $\{0, 1, 3, 0\} \rightarrow \{0, 2, 1, 3, 0\}$

### 近傍解の生成（削除）

- ランダムなスポットを削除
  - 例: $\{0, 1, 3, 0\} \rightarrow \{0, 3, 0\}$

## 焼きなまし法の実装

### 近傍解の生成（交換）

- 解からランダムな2つのスポットを選び、交換する
  - 例: $\{0, 1, 3, 0\} \rightarrow \{0, 3, 1, 0\}$
- 解からランダムなスポットを1つ選び、解に含まれないスポットと交換する
  - 例: $\{0, 1, 3, 0\} \rightarrow \{0, 2, 3, 0\}$

## スコアの比較

<span class="text-blue-800">**sa**</span>: 焼きなまし法、 <span class="text-orange-600">**climb_mt**</span>: 多出発山登り法

一般に焼きなまし法のほうが良い解を得られると言われているが、、、

<div class="grid grid-flow-col justify-stretch gap-4 items-center h-full">

<image src="comp-score-density.webp" class="object-cover" />
<image src="comp-score-box.webp" class="object-cover" />

</div>

## 焼きなましのスコアが伸び悩んだ理由の考察

焼きなましの良さが出なかったから？

### 制約の厳しさ

<div class="grid grid-flow-col justify-stretch gap-6 h-full">
<div>

- 遷移可能な近傍が途中でなくなる？
  - 初期解に強く依存する？
- 多出発山登りは↑の問題を回避できる

</div>
<image src="./ans-set.svg" class="h-5/6" />
</div>

## 焼きなましのスコアが伸び悩んだ理由の考察

改善を試みたが、、、

### 制約違反を許容してみた

- 結論 ： うまくいかなかった
- 理由 ： スポットを訪問すればするほどスコアが上がるから
  - 「24時間休まず観光」みたいな解になっていく

### 制約違反のスポットを1つのみに限定してみた

- 結論 ： うまくいかなかった
- 理由 ： 近傍に制約を満たす解がないような場所に収束することが多いから

## 実際の観光地でやってみよう

<image src="kyoto-search-res.webp" class="w-fit h-[95%] self-center object-cover" />

## 実際の観光地でやってみよう

偶然にも、世界的観光地が身近にあった

### 問題設定

- 京都駅を9:00に出発し、18:00までに戻ってくる
- 移動は徒歩限定 （しんどい、、、）
- スポット間の距離や営業時間はGoogle Maps APIから取得
- 訪問するスポットの候補と予定滞在時間行きたい度（1〜3）は次のスライド

## 実際の観光地でやってみよう

<div class="grid grid-flow-col justify-stretch gap-4">
<div class="text-base">

```csv
# スポット名, 予定滞在時間(分), 行きたい度
伏見稲荷大社, 45, 3
金閣寺, 30, 3
二条城, 30, 3
平安神宮, 15, 1
八坂神社, 15, 1
銀閣寺, 30, 2
京都御所, 15, 1
下鴨神社, 20, 2
上賀茂神社, 20, 2
貴船神社, 30, 3
鞍馬寺, 30, 2
渡月橋, 5, 3
東寺, 30, 2
三十三間堂, 20, 2
八坂庚申堂, 10, 2
安井金比羅宮, 20, 2
南禅寺, 30, 3
龍安寺, 30, 3
仁和寺, 20, 1
北野天満宮, 20, 2
京都水族館, 90, 3
京都タワー, 30, 2
京都国立博物館, 90, 2
京都鉄道博物館, 90, 2
西本願寺, 30, 2
京都大学中央食堂, 45, 100
```

</div>
<div>

- 昼食は行列のできる名店、京都大学中央食堂で
  - 必須なので、行きたい度を100に設定
  - 12:00〜13:00に到着するという制約を課す
- その他スポットでは、営業時間以外の制約は課さない

</div>
</div>

## 実際の観光地でやってみよう

### 結果

<div class="flex justify-center overflow-y-auto text-3xl gap-16">

から | まで | スポット
:--:|:--:|--
\- | 09:00 | 京都駅
09:20 | 09:40 | 三十三間堂
10:05 | 10:35 | 音羽山清水寺
10:44 | 10:54 | 八坂庚申堂
10:58 | 11:18 | 安井金比羅宮
11:27 | 11:42 | 八坂神社
12:23 | 12:53 | 京都大学中央食堂

から | まで | スポット
:--:|:--:|--
13:15 | 13:35 | 下鴨神社
13:51 | 14:06 | 京都御所
14:26 | 14:56 | 錦市場
15:23 | 15:53 | 二条城
16:34 | 17:04 | 西本願寺
17:23 | 17:53 | 京都タワー
17:54 | \- | 京都駅

</div>

---

<!-- _class: narrow -->

<!-- <iframe class="border-none h-full w-full" src="https://ayu0616.github.io/travel-planner/"></iframe> -->
<iframe class="border-none h-full w-full" src="http://localhost:5173/travel-planner"></iframe>

## AHCのすゝめ

### AHCとは

**A**tCoder **H**euristic **C**ontestのこと

- 競技プログラミング
- よりよい解を出すことを目指す（ある値が答えになるというわけではない）
- スコアを改善していく ： その際に、山登り法や焼きなまし法を使うことが多い

### 自分は

- 今学期に入る前ぐらいに始めた
- A: <span class="text-green-700">緑色</span>, H: <span class="text-sky-500">水色</span> （柔道の帯みたいな概念）

<image src="https://img.atcoder.jp/assets/top/img/logo_bk.svg" class="h-48 absolute right-0 top-0 m-16" />

<script src="https://cdn.tailwindcss.com/"></script>
<script src="./tailwind.config.js"></script>
