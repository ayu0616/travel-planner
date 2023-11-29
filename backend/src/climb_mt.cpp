// 貪欲法で解を構成してから、山登り法で解を改善する
#include <bits/stdc++.h>
using namespace std;

#include "../tp-lib.hpp"

int N;
vector<Place> places;
vvi D;  // 地点間の移動時間

// これまでのファイルとは異なる状態を定義する
struct State {
    vi arrive_at;      // 到着時間
    ll visited = 0;    // 訪れた場所のビット列
    vi path;           // 訪れた場所の順番
    int path_len = 0;  // 訪れた場所の数

    State() {
        arrive_at = {0};
        visited = 0;
        path = {0};
        path_len = 1;
    }

    // スコアは高いほうが良い
    float score() const {
        float s = 1 - (float)arrive_at.back() / places[0].arrive_before;  // 到着時間が早いほど良い
        rep(i, N) {
            if (visited >> i & 1) s += places[i].priority;
        }
        return s;
    }

    // ゴール判定
    bool is_goal() const { return visited == (1 << N) - 1; }

    // 各地点の到着時間を計算する
    void calc_arrive_at() {
        arrive_at = vi(path_len, 0);
        rep(i, path_len - 1) { arrive_at[i + 1] = arrive_at[i] + places[path[i]].stay_time + D[path[i]][path[i + 1]]; }
    }

    // 2地点の訪問順を逆転する
    void reverse(int i, int j) {
        std::reverse(path.begin() + i, path.begin() + j + 1);
        calc_arrive_at();
    }

    // 地点jをi番目に挿入する
    void insert(int i, int j) {
        if (visited >> j & 1) return;
        path.insert(path.begin() + i, j);
        visited |= 1 << j;
        path_len++;
        calc_arrive_at();
    }

    // 地点iとjを入れ替える
    void swap(int i, int j) {
        bool i_exist = visited >> i & 1;
        bool j_exist = visited >> j & 1;

        if (i_exist && j_exist) {
            auto i_it = find(all(path), i);
            auto j_it = find(all(path), j);
            iter_swap(i_it, j_it);
        } else if (i_exist) {
            auto i_it = find(all(path), i);
            *i_it = j;
            visited ^= 1 << i;
            visited |= 1 << j;
        } else if (j_exist) {
            auto j_it = find(all(path), j);
            *j_it = i;
            visited ^= 1 << j;
            visited |= 1 << i;
        }
        if (i_exist || j_exist) {
            calc_arrive_at();
        }
    }

    void push_back(int i) {
        if (visited >> i & 1) return;
        path.push_back(i);
        visited |= 1 << i;
        path_len++;
        calc_arrive_at();
    }

    // i番目の地点を削除する
    void erase(int i) {
        if (!(visited >> i & 1)) return;
        visited ^= 1 << path[i];
        path.erase(path.begin() + i);
        path_len--;
        calc_arrive_at();
    }

    // 実行可能解かどうか判定する
    bool is_valid() const {
        // 到着時間がオーバーしていないか
        for (int i = 1; i < path_len; i++) {
            if (!places[path[i]].is_visitable(arrive_at[i])) return false;
        }

        // 以上の条件をクリアしていれば実行可能解
        return true;
    }

    void pop_back() {
        int back = path.back();
        visited ^= 1 << back;
        path.pop_back();
        arrive_at.pop_back();
        path_len--;
    }

    bool is_time_over() {
        State tmp = *this;
        tmp.push_back(0);
        return tmp.arrive_at.back() > places[0].arrive_before;
    }
};

bool operator<(const State& s, const State& t) { return s.score() < t.score(); }
bool operator>(const State& s, const State& t) { return s.score() > t.score(); }
bool operator==(const State& s, const State& t) { return s.score() == t.score(); }
bool operator<=(const State& s, const State& t) { return s.score() <= t.score(); }
bool operator>=(const State& s, const State& t) { return s.score() >= t.score(); }

int main() {
    time_t start = time(nullptr);
    cin >> N;
    D = vvi(N, vi(N));
    rep(i, N) rep(j, N) cin >> D[i][j];

    places.resize(N);
    rep(i, N) {
        places[i].id = i;
        int ab, aa, st, pr;
        cin >> ab >> aa >> st >> pr;
        if (ab != -1) places[i].arrive_before = ab;
        if (aa != -1) places[i].arrive_after = aa;
        places[i].stay_time = st;
        places[i].priority = pr;
    }

    // 初期状態
    State init;
    init.arrive_at = {0};
    init.visited = 0;
    init.path = {0};
    // while (true) {
    //     priority_queue<State> best, best_but_time_over;
    //     for (int i = 1; i < N; i++) {
    //         if (init.visited >> i & 1) continue;
    //         State tmp = init;
    //         tmp.push_back(i);
    //         if (!tmp.is_valid()) continue;
    //         if (tmp.is_time_over()) {
    //             best_but_time_over.push(tmp);
    //         } else {
    //             best.push(tmp);
    //         }
    //     }
    //     if (best.size()) {
    //         init = best.top();
    //     } else {
    //         init.push_back(0);
    //         break;
    //     }
    // }
    while (true) {
        bool is_time_over = false;
        for (int i = 1; i < N; i++) {
            if (init.visited >> i & 1) continue;
            State tmp = init;
            tmp.push_back(i);
            if (!tmp.is_valid()) continue;
            if (tmp.is_time_over()) {
                init.push_back(0);
                is_time_over = true;
                break;
            } else {
                init = tmp;
            }
        }
        if (is_time_over) break;
    }
    priority_queue<State> que;  // スコアが高い順に取り出す
    que.push(init);

    priority_queue<State> answers;  // 解となる状態を格納する
    answers.push(init);
    while (!que.empty() && time(nullptr) - start < 3) {
        State s = que.top();
        // que.pop();
        priority_queue<State> best;
        for (int i = 1; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                State tmp = s;
                if (!(((tmp.visited >> i) & 1) ^ ((tmp.visited >> j) & 1))) continue;
                tmp.swap(i, j);
                if (!tmp.is_valid()) continue;
                best.push(tmp);
            }
        }
        vector<State> best10;
        rep(i, min(10, (int)best.size())) {
            best10.push_back(best.top());
            best.pop();
        }
        best10.push_back(s);
        for (auto b : best10) {
            best.push(b);
            for (int i = 1; i < N; i++) {
                if (b.visited >> i & 1) continue;
                for (int k = 1; k < b.path_len - 1; k++) {
                    State tmp = b;
                    tmp.insert(k, i);
                    if (!tmp.is_valid()) continue;
                    best.push(tmp);
                }
            }
        }
        rep(i, min(10, (int)best.size())) {
            que.push(best.top());
            answers.push(best.top());
            best.pop();
        }
        cerr << answers.top().score() << endl;
    }

    auto ans = answers.top();
    cout << ans.score() << endl;
    cout << ans.path << endl;
}
