// ビームサーチしてみよう
#include <bits/stdc++.h>
using namespace std;

#include "../tp-lib.hpp"

int N;
vector<Place> places;
vvi D;  // 地点間の移動時間

int random_int(int l, int r) { return l + rand() % (r - l); }

// これまでのファイルとは異なる状態を定義する
struct State {
    vi arrive_at;      // 到着時間
    vb visited;        // 訪れた場所
    vi path;           // 訪れた場所の順番
    int path_len = 0;  // 訪れた場所の数
    double score = 0;

    State() {
        arrive_at = {0};
        visited.assign(N, false);
        path = {0};
        path_len = 1;
    }

    // 初期解を構築する
    void build_init() {
        arrive_at = {0};
        visited.assign(N, false);
        path = {0};
        vb used(N, false);
        while (true) {
            bool all_used = true;
            for (int i = 1; i < N; i++) {
                if (!used[i]) {
                    all_used = false;
                    break;
                }
            }
            if (all_used) {
                push_back(0);
                break;
            }
            State tmp = *this;
            int p = random_int(1, N);
            if (tmp.visited[p]) {
                used[p] = true;
                continue;
            }
            tmp.push_back(p);
            if (!tmp.is_valid()) {
                used[p] = true;
                continue;
            }
            if (tmp.is_time_over()) {
                push_back(0);
                break;
            } else {
                *this = tmp;
                used = visited;
            }
        }
    }

    // スコアは高いほうが良い
    double calc_score() const {
        double s = 1 - (double)arrive_at.back() / places[0].arrive_before;  // 到着時間が早いほど良い
        rep(i, N) {
            if (visited[i]) s += places[i].priority;
        }
        return s;
    }

    // ゴール判定
    bool is_goal() const {
        for (int i = 0; i < N; i++)
            if (!visited[i]) return false;
        return true;
    }

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
        if (visited[j]) return;
        path.insert(path.begin() + i, j);
        visited[j] = true;
        path_len++;
        calc_arrive_at();
        int _score = score;
        _score += places[j].priority;
        score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
    }

    // 地点iとjを入れ替える
    void swap(int i, int j) {
        bool i_exist = visited[i];
        bool j_exist = visited[j];

        if (i_exist && j_exist) {
            auto i_it = find(all(path), i);
            auto j_it = find(all(path), j);
            iter_swap(i_it, j_it);
            calc_arrive_at();
            int _score = score;
            score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
        } else if (i_exist) {
            auto i_it = find(all(path), i);
            *i_it = j;
            visited[i] = false;
            visited[j] = true;
            calc_arrive_at();
            int _score = score;
            _score -= places[i].priority;
            _score += places[j].priority;
            score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
        } else if (j_exist) {
            auto j_it = find(all(path), j);
            *j_it = i;
            visited[j] = false;
            visited[i] = true;
            calc_arrive_at();
            int _score = score;
            _score -= places[j].priority;
            _score += places[i].priority;
            score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
        }
    }

    bool can_push_back(int i) {
        if (visited[i]) return false;
        int i_arrive_at = arrive_at.back() + places[path.back()].stay_time + D[path.back()][i];
        return places[i].is_visitable(i_arrive_at);
    }

    void push_back(int i) {
        if (visited[i]) return;
        path.push_back(i);
        visited[i] = true;
        path_len++;
        arrive_at.push_back(arrive_at.back() + places[i].stay_time + D[path[path_len - 2]][i]);
        int _score = score;
        _score += places[i].priority;
        score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
    }

    // i番目の地点を削除する
    void erase(int i) {
        if (!(visited[path[i]])) return;
        visited[path[i]] = false;
        int _score = score;
        _score -= places[path[i]].priority;
        path.erase(path.begin() + i);
        path_len--;
        calc_arrive_at();
        score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
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
        visited[back] = false;
        path.pop_back();
        arrive_at.pop_back();
        path_len--;
        int _score = score;
        _score -= places[back].priority;
        score = (double)_score + 1 - (double)arrive_at.back() / places[0].arrive_before;
    }

    bool is_time_over() {
        State tmp = *this;
        tmp.push_back(0);
        return tmp.arrive_at.back() > places[0].arrive_before;
    }
};

bool operator<(const State& s, const State& t) { return s.score < t.score; }
bool operator>(const State& s, const State& t) { return s.score > t.score; }
bool operator==(const State& s, const State& t) { return s.score == t.score; }
bool operator<=(const State& s, const State& t) { return s.score <= t.score; }
bool operator>=(const State& s, const State& t) { return s.score >= t.score; }

int main() {
    Time time = Time();
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

    constexpr int BEAM_WIDTH = 500;

    State s, ans;
    priority_queue<State> states;
    states.emplace(s);
    while (!time.is_over(2000)) {
        priority_queue<State> nexts;
        rep(i, BEAM_WIDTH) {
            if (states.empty()) break;
            State cur = states.top();
            states.pop();
            rep(i, N) {
                State tmp = cur;
                if (tmp.can_push_back(i)) {
                    tmp.push_back(i);
                    nexts.emplace(tmp);
                    if (i == 0 && ans < tmp) ans = tmp;
                }
            }
        }
        states = priority_queue<State>();
        rep(i, BEAM_WIDTH) {
            if (nexts.empty()) break;
            states.emplace(nexts.top()), nexts.pop();
        }
    }

    cout << ans.score << endl;
    cout << ans.path << endl;
}