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
            State tmp = *this;
            int cur = tmp.path.back();
            int next = -1;
            pair<int, int> max_score = {0, -1e9};
            for (int i = 1; i < N; i++) {
                if (tmp.visited[i] || used[i]) continue;
                if (max_score < make_pair(places[i].priority, -D[cur][i])) {
                    max_score = {places[i].priority, -D[cur][i]};
                    next = i;
                }
            }
            if (next == -1) {
                push_back(0);
                break;
            }
            tmp.push_back(next);
            used[next] = true;
            if (!tmp.is_valid()) continue;
            used.assign(N, false);
            if (tmp.is_time_over()) {
                push_back(0);
                break;
            } else {
                *this = tmp;
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

    // 実行可能解かどうか判定する（緩和版）
    bool is_valid_relax() const {
        if (arrive_at.back() > places[0].arrive_before) return false;
        int over_cnt = 0;
        // 到着時間がオーバーしていないか
        for (int i = 1; i < path_len; i++) {
            if (!places[path[i]].is_visitable(arrive_at[i])) over_cnt++;
        }
        return over_cnt <= 1;
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

int main(int argc, char* argv[]) {
    double start_temp, end_temp;
    if (argc >= 3) {
        start_temp = stod(argv[1]);
        end_temp = stod(argv[2]);
    } else {
        start_temp = 0.64;
        end_temp = 0.34;
    }

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

    constexpr double TIME_LIMIT = 3000;

    // 解
    State ans, final_ans;
    ans.build_init();
    final_ans = ans;

    auto update_ans = [&](const State& tmp, const double& temperature = 0.00001) {
        double prob = exp((tmp.score - ans.score) / temperature);
        // if(prob > random_double(0, 1) && tmp.is_valid_relax()) {
        //     ans = tmp;
        //     if (final_ans < ans && ans.is_valid()) final_ans = ans;
        // }
        if (tmp.is_valid() && prob > random_double(0, 1)) {
            ans = tmp;
            if (final_ans < ans) final_ans = ans;
        }
    };

    while (!time.is_over(TIME_LIMIT)) {
        double temperature = start_temp + (end_temp - start_temp) * (time.get() / TIME_LIMIT);

        auto del = [&]() {
            if (ans.path_len > 3) {
                State tmp = ans;
                int idx2 = random_int(1, tmp.path_len - 2);
                tmp.erase(idx2);
                update_ans(tmp, temperature);
            }
        };

        auto insert = [&]() {
            State tmp = ans;
            int idx = random_int(1, tmp.path_len - 1);
            int p_not_vis;
            while (p_not_vis = random_int(1, N), tmp.visited[p_not_vis]) {
            }
            tmp.insert(idx, p_not_vis);
            update_ans(tmp, temperature);
        };

        auto swap = [&]() {
            State tmp = ans;
            int p_vis;
            int p_not_vis;
            while (p_vis = random_choice(tmp.path), p_vis == 0) {
            }
            while (p_not_vis = random_int(1, N), tmp.visited[p_not_vis]) {
            }
            tmp.swap(p_vis, p_not_vis);
            update_ans(tmp, temperature);
        };

        del();
        rep(i, 100) {
            insert();
            swap();
        }
    }
    cout << final_ans.score << endl;
    cout << final_ans.path << endl;
}
