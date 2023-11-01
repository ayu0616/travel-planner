// 滞在時間も考慮する

#include "../tp-lib.hpp"

struct State : StateBase
{
    ll visited;

    State()
    {
        visited = 0;
    };

    int visited_len() const
    {
        return popcount((unsigned ll)visited);
    }

    double score() const
    {
        return arrive_at / visited_len();
    }

    bool operator<(const State &s) const
    {
        return score() < s.score();
    }

    bool operator>(const State &s) const
    {
        return score() > s.score();
    }
};

int main()
{
    int N;
    cin >> N;
    vector<vector<double>> A(N, vector<double>(N));
    rep(i, N) rep(j, N) cin >> A[i][j];

    vector<Place> places(N);
    rep(i, N)
    {
        places[i].id = i;
        int ab, aa, st;
        cin >> ab >> aa >> st;
        if (ab != -1)
            places[i].arrive_before = ab;
        if (aa != -1)
            places[i].arrive_after = aa;
        places[i].stay_time = st;
    }

    // 初期状態
    State *init = new State();
    init->place = &places[0];
    init->prev = nullptr;
    init->arrive_at = 0;
    init->visited = 0;

    // ゴール判定
    auto is_goal = [&](State *s)
    {
        return s->visited == (1 << N) - 1;
    };

    greater_heap<State *> que;
    que.push(init);

    State *ans = nullptr;
    while (!que.empty())
    {
        State *s = que.top();
        que.pop();
        Place cp = *s->place;
        if (is_goal(s) && (ans == nullptr || s->arrive_at < ans->arrive_at))
            ans = s;
        if (s->arrive_at + cp.stay_time + A[cp.id][0] > places[0].arrive_before)
        {
            auto tmp = new State();
            auto prev = s->prev;
            tmp->place = &places[0];
            tmp->prev = prev;
            tmp->arrive_at = prev->arrive_at + prev->place->stay_time + A[prev->place->id][0];
            tmp->visited = (s->visited ^ (1 << cp.id)) | (1 << 0);
            if (ans == nullptr || tmp->visited_len() > ans->visited_len() || (tmp->visited_len() == ans->visited_len() && tmp->arrive_at < ans->arrive_at))
                ans = tmp;
            continue;
        }

        rep(i, N)
        {
            if (s->visited & (1 << i) || (i == 0 && s->visited_len() != N - 1))
                continue;
            double arrive_at = s->arrive_at + cp.stay_time + A[cp.id][i];
            if (!places[i].is_visitable(arrive_at))
                continue;
            State *next = new State();
            next->place = &places[i];
            next->prev = s;
            next->arrive_at = arrive_at;
            next->visited = s->visited | (1 << i);
            que.push(next);
        }
    }

    if (ans)
    {
        auto visited_places = trace_back(ans);

        cout << ans->arrive_at << endl;
        cout << visited_places << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
}
